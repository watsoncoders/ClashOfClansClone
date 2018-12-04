#include "DBCCHelper.h"
#include "DBCCFactory.h"
#include "DBCCTextureAtlas.h"
#include "DBCCSlot.h"
#include "DBCCEventDispatcher.h"
#include "DBCCArmature.h"
#include "PlistDataParser.h"

NAME_SPACE_DRAGON_BONES_BEGIN
DBCCHelper* DBCCHelper::_instance = nullptr;

DBCCHelper* DBCCHelper::getInstance()
{
	if (!_instance)
	{
		_instance = new DBCCHelper();
	}
	return _instance;
}

void DBCCHelper::destroyInstance()
{
	if (_instance)
	{
		CC_SAFE_DELETE(_instance);
	}
}

DBCCHelper::DBCCHelper() :_loadingThread(nullptr)
, _needQuit(false)
, _asyncRefCount(0)
, _curAsyncStruct(nullptr)
{
}
DBCCHelper::~DBCCHelper() {}

struct DBCCHelper::AnimationStruct
{
public:
	AnimationStruct(const std::string& arn,
		DBCCArmatureNode* armn) :
		armatureName(arn), node(armn)
	{
	}
	std::string armatureName;
	DBCCArmatureNode* node;
};
struct DBCCHelper::AsyncStruct
{
public:
	AsyncStruct(const std::string& dp, const std::string& taf, const std::string& arn, const std::string& n,
		DBCCArmatureNode* armn) :
		dragonBonesFilePath(dp), textureAtlasFile(taf), name(n), loadSuccess(false) {
		listAnimation.push_back(AnimationStruct(arn, armn));
	}

	std::string dragonBonesFilePath;
	std::string textureAtlasFile;
	std::string name;
	cocos2d::Image image;
	std::vector<AnimationStruct> listAnimation;
	bool loadSuccess;
};
std::string DBCCHelper::getImagePathFromAtlasPath(const std::string& atlasPath)
{
	std::string file_png = "";
	size_t pos = atlasPath.find_last_of(".");
	if (pos != std::string::npos)
	{
		file_png = atlasPath.substr(0, pos);
		file_png = file_png + ".png";
	}
	return file_png;
}
DBCCArmatureNode* DBCCHelper::buildAsyncArmatureNode(const std::string &dragonBonesFilePath, const std::string &textureAtlasFile, const std::string &armatureName, const std::string &name)
{
	cocos2d::log("buildAsyncArmatureNode: %s, %s", armatureName.c_str(), name.c_str());
	std::string key = name.empty() ? armatureName : name;

	DBCCArmatureNode* node = DBCCArmatureNode::create(nullptr);
	//if exist
	ITextureAtlas *existTextureAtlas = DBCCFactory::getInstance()->getTextureAtlas(key);
	if (existTextureAtlas)
	{
		node->loadingDataCallBack(armatureName);
		return node;
	}
	// lazy init
	if (_loadingThread == nullptr)
	{
		// create a new thread to load images
		_loadingThread = new std::thread(&DBCCHelper::loadData, this);
		_needQuit = false;
	}

	if (0 == _asyncRefCount)
	{
		cocos2d::Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(DBCCHelper::loadDataAsyncCallBack), this, 0, false);
	}

	++_asyncRefCount;

	bool isExistTextureInQueue = false;
	_requestMutex.lock();
	for (size_t i = 0; i < _requestQueue.size(); i++)
	{
		if (textureAtlasFile.compare(_requestQueue.at(i)->textureAtlasFile) == 0)
		{
			isExistTextureInQueue = true;
			_requestQueue.at(i)->listAnimation.push_back(AnimationStruct(armatureName, node));
		}
	}
	_requestMutex.unlock();
	if (!isExistTextureInQueue)
	{
		if (_curAsyncStruct)
		{
			if (textureAtlasFile.compare(_curAsyncStruct->textureAtlasFile) == 0)
			{
				isExistTextureInQueue = true;
				_curAsyncStruct->listAnimation.push_back(AnimationStruct(armatureName, node));
			}
		}
	}
	
	if (!isExistTextureInQueue)
	{
		_responseMutex.lock();
		for (size_t i = 0; i < _responseQueue.size(); i++)
		{
			if (textureAtlasFile.compare(_responseQueue.at(i)->textureAtlasFile) == 0)
			{
				isExistTextureInQueue = true;
				_responseQueue.at(i)->listAnimation.push_back(AnimationStruct(armatureName, node));
			}
		}
		_responseMutex.unlock();
	}
	if (!isExistTextureInQueue){
		// generate async struct
		AsyncStruct *data = new (std::nothrow) AsyncStruct(dragonBonesFilePath, textureAtlasFile, armatureName,
			key, node);
		// add async struct into queue
		_requestMutex.lock();
		_requestQueue.push_back(data);
		_requestMutex.unlock();

		_sleepCondition.notify_one();
	}
	

	return node;
}
void DBCCHelper::loadData()
{
	std::mutex signalMutex;
	std::unique_lock<std::mutex> signal(signalMutex);
	while (!_needQuit)
	{
		// pop an AsyncStruct from request queue
		_requestMutex.lock();
		if (_requestQueue.empty())
		{
			_curAsyncStruct = nullptr;
		}
		else
		{
			_curAsyncStruct = _requestQueue.front();
			_requestQueue.pop_front();
		}
		_requestMutex.unlock();

		if (nullptr == _curAsyncStruct) {
			_sleepCondition.wait(signal);
			continue;
		}
		//Dragon bone data
		DBCCFactory::getInstance()->loadDragonBonesData(_curAsyncStruct->dragonBonesFilePath, _curAsyncStruct->name);
		//parse image path
		std::string file_png = getImagePathFromAtlasPath(_curAsyncStruct->textureAtlasFile);
		_curAsyncStruct->loadSuccess = _curAsyncStruct->image.initWithImageFileThreadSafe(file_png);

		// push the asyncStruct to response queue
		_responseMutex.lock();
		_responseQueue.push_back(_curAsyncStruct);
		_responseMutex.unlock();
	}
}
void DBCCHelper::loadDataAsyncCallBack(float dt)
{
	cocos2d::Texture2D *texture = nullptr;
	AsyncStruct *asyncStruct = nullptr;
	while (true)
	{
		// pop an AsyncStruct from response queue
		_responseMutex.lock();
		if (_responseQueue.empty())
		{
			asyncStruct = nullptr;
		}
		else
		{
			asyncStruct = _responseQueue.front();
			_responseQueue.pop_front();
		}
		_responseMutex.unlock();

		if (nullptr == asyncStruct) {
			break;
		}
		std::string pngFile = DBCCHelper::getImagePathFromAtlasPath(asyncStruct->textureAtlasFile);
		texture = cocos2d::TextureCache::getInstance()->addTextureFromImage(pngFile, &asyncStruct->image, asyncStruct->loadSuccess);
		DBCCFactory::getInstance()->loadTextureAtlas(asyncStruct->textureAtlasFile, asyncStruct->name);
		// call callback function
		for (size_t i = 0; i < asyncStruct->listAnimation.size(); i++)
		{
			AnimationStruct ani = asyncStruct->listAnimation[i];
			if (ani.node)
			{
				ani.node->loadingDataCallBack(ani.armatureName);
			}
		}

		// release the asyncStruct
		delete asyncStruct;
		--_asyncRefCount;
	}

	if (0 == _asyncRefCount)
	{
		cocos2d::Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(DBCCHelper::loadDataAsyncCallBack), this);
	}

}

void DBCCHelper::onRemovedArmatureNode(DBCCArmatureNode* armatureNode)
{
	
	_requestMutex.lock();
	for (size_t i = 0; i < _requestQueue.size(); i++)
	{
		if (removeArmatureNode(armatureNode, _requestQueue.at(i)))
		{
			_requestMutex.unlock();
			return;
		}
	}
	_requestMutex.unlock();

	if (_curAsyncStruct)
	{
		if (removeArmatureNode(armatureNode, _curAsyncStruct))
		{
			return;
		}
	}

		_responseMutex.lock();
		for (size_t i = 0; i < _responseQueue.size(); i++)
		{
			if (removeArmatureNode(armatureNode, _responseQueue.at(i)))
			{
				_responseMutex.unlock();
				return;
			}
		}
		_responseMutex.unlock();
	

}

bool DBCCHelper::removeArmatureNode(DBCCArmatureNode* armatureNode, AsyncStruct* data)
{
	cocos2d::log("removeArmatureNode");
	for (size_t i = 0; i < data->listAnimation.size(); i++)
	{
		if (data->listAnimation[i].node == armatureNode)
		{
			data->listAnimation[i].node = nullptr;
			cocos2d::log("removeArmatureNode: true");
			return true;
		}
	}
	return false;
}
NAME_SPACE_DRAGON_BONES_END
