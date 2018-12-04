#ifndef DBCCSprite_h__
#define DBCCSprite_h__

#include "DragonBonesHeaders.h"
#include "cocos2d.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class DBCCSprite:
	public cocos2d::Sprite
{
public:
	DBCCSprite();
	~DBCCSprite();
	static DBCCSprite* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
public:
	void setColorByShader(int r, int g, int b);
private:
	cocos2d::GLProgramState* _glprogramstate;
};


NAME_SPACE_DRAGON_BONES_END
#endif // DBCCSprite_h__
