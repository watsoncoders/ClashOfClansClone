#ifndef DBCC_ARMATURE_NODE_H
#define DBCC_ARMATURE_NODE_H

#include "dbccMacro.h"
#include "DragonBonesHeaders.h"
#include "cocos2d.h"
#include "DBCCSlot.h"
#include "DBCCArmature.h"



NAME_SPACE_DRAGON_BONES_BEGIN

class DBCCArmatureNode;
typedef std::function<void(DBCCArmatureNode* armature)> CompleteEventListener;

class DBCCArmatureNode : public cocos2d::Node, public IAnimatable
{
public:
    virtual DBCCSlot* getCCSlot(const std::string &slotName) const { return _armature->getCCSlot(slotName); };
	virtual cocos2d::Node* getCCDisplay() const { return _armature->getCCDisplay(); };
	virtual cocos2d::EventDispatcher* getCCEventDispatcher() const { return _armature->getCCEventDispatcher(); };
	virtual cocos2d::Rect getBoundingBox() const override;
    virtual cocos2d::Rect getInnerBoundingBox() const;

public:
    // create DBCCArmatureNode without WorldClock
    static DBCCArmatureNode* create(DBCCArmature *armature);
    /**
     * create DDCCArmatureNode with WorldClock
     * @param armature
     * @param clock if null, use WorldClock::getInstance()
     * @return 
     */
    static DBCCArmatureNode* createWithWorldClock(DBCCArmature *armature, WorldClock *clock);
    virtual bool initWithDBCCArmature(DBCCArmature *armature, WorldClock *clock);
    
    DBCCArmatureNode();
    virtual ~DBCCArmatureNode();

	virtual void onEnter() override;
	virtual void onExit() override;

	DBCCArmature* getArmature()  { return _armature; };
	Animation* getAnimation()  { return _armature->getAnimation(); };

	virtual void update(float dt) override;
    virtual void advanceTime(float dt) override;

	void setCompleteListener(const CompleteEventListener& listener);
	void setBaseColor(int r, int g, int b); 
	void gotoAndPlay(const std::string &animationName, float fadeInTime = -1.f, float duration = -1.f, int playTimes = -1);
	void play();
public:
	void loadingDataCallBack(const std::string &armatureName);
private:
	void updateBaseColor();
protected:
    DBCCArmature *_armature;
    WorldClock *_clock;
	CompleteEventListener _completeListener;
	cocos2d::BlendFunc _blend;
	std::string _animationName;
	float _fadeInTime;
	float _duration;
	int _playTimes;
	bool _needPlayAnimation;
	bool _needSetBaseColor;
	int _r;
	int _g;
	int _b;
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(DBCCArmatureNode);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // DBCC_ARMATURE_NODE_H
