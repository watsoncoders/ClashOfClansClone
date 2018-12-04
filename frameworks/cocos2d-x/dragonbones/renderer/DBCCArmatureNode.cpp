#include "dbccMacro.h"
#include "DBCCArmatureNode.h"
#include "DBCCSprite.h"
#include "DBCCFactory.h"
#include "DBCCHelper.h"


NAME_SPACE_DRAGON_BONES_BEGIN

DBCCArmatureNode* DBCCArmatureNode::create(DBCCArmature *armature)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    
    if (ret && ret->initWithDBCCArmature(armature, nullptr))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

DBCCArmatureNode* DBCCArmatureNode::createWithWorldClock(DBCCArmature *armature, WorldClock *clock)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    if (!clock)
        clock = WorldClock::getInstance();

    if (ret && ret->initWithDBCCArmature(armature, clock))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool DBCCArmatureNode::initWithDBCCArmature(DBCCArmature *armature, WorldClock *clock)
{
    if (armature != nullptr)
    {
        _armature = armature;
        _armature->setArmatureNode(this);
        _clock = clock;
        if (clock)
        {
            clock->add(this);
        }
        addChild(armature->getCCDisplay());
        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);
		//listener

		auto dispatcher = _armature->getCCEventDispatcher();

		auto f = [this](cocos2d::EventCustom *event)
		{
			if (this->_completeListener) this->_completeListener(this);
		};

		dispatcher->addCustomEventListener(EventData::COMPLETE, f);

        return true;
    }

	return true;
}


DBCCArmatureNode::DBCCArmatureNode()
    :_armature(nullptr)
    ,_clock(nullptr)
	, _completeListener(nullptr)
	, _needPlayAnimation(false)
	, _needSetBaseColor(false)
{
}
DBCCArmatureNode::~DBCCArmatureNode()
{
    if (_clock)
    {
        _clock->remove(this);
        _clock = nullptr;
    }

    if (_armature)
    {
		cocos2d::log("~DBCCArmatureNode: %s", _armature->name.c_str() );
        delete _armature;
        _armature = nullptr;
    }
	DBCCHelper::getInstance()->onRemovedArmatureNode(this);
}
void DBCCArmatureNode::onEnter()
{
	Node::onEnter();
	if (!_clock)
	{
		scheduleUpdate();
	}
}

void DBCCArmatureNode::onExit()
{
	Node::onExit();
	if (!_clock)
	{
		unscheduleUpdate();
	}
}

void DBCCArmatureNode::setBaseColor(int r, int g, int b)
{
	this->_needSetBaseColor = true;
	this->_r = r;
	this->_b = b;
	this->_g = g;
	if (this->_armature)
	{
		updateBaseColor();
	}
}
void DBCCArmatureNode::updateBaseColor()
{
	this->_needSetBaseColor = false;
	const std::vector<Bone*> listBones = _armature->getBones();
	for (auto& object : listBones)
	{
		std::string name = object->name;
		if (name.find("color_", 0) == 0)
		{
			std::vector <Slot*> listSlots = object->getSlots();
			for (auto& slot : listSlots)
			{
				std::vector<std::pair<void*, DisplayType>> displayList = slot->getDisplayList();
				for (size_t i = 0; i < displayList.size(); i++)
				{
					if (displayList[i].second == DisplayType::DT_IMAGE){
						DBCCSprite* display = (DBCCSprite*)displayList[i].first;
						display->setColorByShader(_r, _g, _b);
					}
				}
			}
		}
	}
}
void DBCCArmatureNode::gotoAndPlay(const std::string &animationName, float fadeInTime, float duration, int playTimes){
	this->_animationName = animationName;
	this->_fadeInTime = fadeInTime;
	this->_duration = duration;
	this->_playTimes = playTimes;

	if (_armature)
	{
		this->_needPlayAnimation = false;
		_armature->getAnimation()->gotoAndPlay(animationName, fadeInTime, duration, playTimes);
	}
	else
	{
		this->_needPlayAnimation = true;
	}
}
void DBCCArmatureNode::play()
{
	this->_animationName = "";
	if (_armature)
	{
		this->_needPlayAnimation = false;
		_armature->getAnimation()->play();
	}
	else
	{
		this->_needPlayAnimation = true;
	}
}
cocos2d::Rect DBCCArmatureNode::getBoundingBox() const
{
    auto rect = _armature->getCCBoundingBox();
    return cocos2d::RectApplyTransform(rect, getNodeToParentTransform());
}

cocos2d::Rect DBCCArmatureNode::getInnerBoundingBox() const
{
    return _armature->getCCBoundingBox();
}

void DBCCArmatureNode::update(float dt)
{
    DBASSERT(!_clock, "can not has clock when update!");
    advanceTime(dt);
}

void DBCCArmatureNode::advanceTime(float dt)
{
    retain();
	if (_armature)
		_armature->advanceTime(dt);
    release();
}
void DBCCArmatureNode::setCompleteListener(const CompleteEventListener& listener)
{
	this->_completeListener = listener;
}
void DBCCArmatureNode::loadingDataCallBack(const std::string &armatureName)
{
	DBCCArmature *armature = DBCCFactory::getInstance()->buildArmature(armatureName);
	if (!armature)
	{
		cocos2d::log("Error: loadingDataCallBack: cant load armature %s", armatureName.c_str());
		return;
	}
	this->initWithDBCCArmature(armature, nullptr);
	if (_needPlayAnimation)
	{
		this->_needPlayAnimation = false;
		if (this->_animationName.empty()){
			this->getAnimation()->play();
		}
		else
		{
			this->getAnimation()->gotoAndPlay(this->_animationName, this->_fadeInTime, this->_duration, this->_playTimes);
		}
		
	}

	if (_needSetBaseColor)
	{
		this->updateBaseColor();
	}
	
}

NAME_SPACE_DRAGON_BONES_END
