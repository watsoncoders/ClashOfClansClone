#ifndef DBCC_HELPER_H
#define DBCC_HELPER_H

#include "DragonBonesHeaders.h"
#include "DBCCRenderHeaders.h"
#include "cocos2d.h"

#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>
#include <unordered_map>
#include <functional>

NAME_SPACE_DRAGON_BONES_BEGIN
class DBCCHelper : public cocos2d::Ref
{
private:
	static DBCCHelper *_instance;

public:
	static DBCCHelper* getInstance();
	static void destroyInstance();
	static std::string getImagePathFromAtlasPath(const std::string& atlasPath);
	DBCCHelper();
	virtual ~DBCCHelper();

	virtual DBCCArmatureNode* buildAsyncArmatureNode(const std::string &dragonBonesFilePath, const std::string &textureAtlasFile, const std::string &armatureName, const std::string &name = "");
	void onRemovedArmatureNode(DBCCArmatureNode* armatureNode);

protected:
	struct AsyncStruct;
	struct AnimationStruct;

	std::thread* _loadingThread;

	AsyncStruct *_curAsyncStruct;
	std::deque<AsyncStruct*> _asyncStructQueue;
	std::deque<AsyncStruct*> _requestQueue;
	std::deque<AsyncStruct*> _responseQueue;

	std::mutex _requestMutex;
	std::mutex _responseMutex;

	std::condition_variable _sleepCondition;

	bool _needQuit;
	int _asyncRefCount;
private:
	void loadData();
	void loadDataAsyncCallBack(float dt);
	bool removeArmatureNode(DBCCArmatureNode* armatureNode, AsyncStruct* data);
};
NAME_SPACE_DRAGON_BONES_END

#endif  // DBCC_HELPER_H