#include "base/ccConfig.h"
#ifndef __cocos2dx_dragonbones_h__
#define __cocos2dx_dragonbones_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_dragonBones_DragonBonesData_class;
extern JSObject *jsb_dragonBones_DragonBonesData_prototype;

bool js_cocos2dx_dragonbones_DragonBonesData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DragonBonesData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DragonBonesData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DragonBonesData_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DragonBonesData_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DragonBonesData_DragonBonesData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_ITextureAtlas_class;
extern JSObject *jsb_dragonBones_ITextureAtlas_prototype;

bool js_cocos2dx_dragonbones_ITextureAtlas_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_ITextureAtlas_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_ITextureAtlas(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_ITextureAtlas_dispose(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_IAnimatable_class;
extern JSObject *jsb_dragonBones_IAnimatable_prototype;

bool js_cocos2dx_dragonbones_IAnimatable_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_IAnimatable_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_IAnimatable(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_IAnimatable_advanceTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_IAnimatable_IAnimatable(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_Object_class;
extern JSObject *jsb_dragonBones_Object_prototype;

bool js_cocos2dx_dragonbones_Object_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_Object_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_Object(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_Object_getParent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Object_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Object_getArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Object_getVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Object_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Object_Object(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_AnimationState_class;
extern JSObject *jsb_dragonBones_AnimationState_prototype;

bool js_cocos2dx_dragonbones_AnimationState_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_AnimationState_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_AnimationState(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_AnimationState_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_setTimeScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_setAdditiveBlending(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getClip(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_setPlayTimes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_removeMixingTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getCurrentPlayTimes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_removeAllMixingTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_addMixingTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getTotalTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getLayer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getPlayTimes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_fadeOut(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getCurrentWeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getIsComplete(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getTimeScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_setFrameTween(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_setWeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getMixingTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_getIsPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_AnimationState_AnimationState(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_Animation_class;
extern JSObject *jsb_dragonBones_Animation_prototype;

bool js_cocos2dx_dragonbones_Animation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_Animation_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_Animation(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_Animation_getAnimationList(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_setTimeScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_hasAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_getLastAnimationState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_getIsComplete(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_advanceTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_getCurrentAnimationName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_getIsPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_gotoAndStop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_getTimeScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Animation_Animation(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_Armature_class;
extern JSObject *jsb_dragonBones_Armature_prototype;

bool js_cocos2dx_dragonbones_Armature_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_Armature_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_Armature(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_Armature_getBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_setInheritAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_replaceSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_removeBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_addSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_invalidUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getBoneByDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_removeSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_isInheritAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_addBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_sortSlotsByZOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getSlotByDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_getEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Armature_Armature(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_Bone_class;
extern JSObject *jsb_dragonBones_Bone_prototype;

bool js_cocos2dx_dragonbones_Bone_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_Bone_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_Bone(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_Bone_addChild(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Bone_getSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Bone_contains(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Bone_removeChild(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Bone_invalidUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_Bone_Bone(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_BaseFactory_class;
extern JSObject *jsb_dragonBones_BaseFactory_prototype;

bool js_cocos2dx_dragonbones_BaseFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_BaseFactory_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_BaseFactory(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_BaseFactory_buildArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_getTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_getDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_BaseFactory_BaseFactory(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCSlot_class;
extern JSObject *jsb_dragonBones_DBCCSlot_prototype;

bool js_cocos2dx_dragonbones_DBCCSlot_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DBCCSlot_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DBCCSlot(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DBCCSlot_dispose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSlot_getGlobalPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSlot_getCCChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSlot_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSlot_DBCCSlot(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCArmature_class;
extern JSObject *jsb_dragonBones_DBCCArmature_prototype;

bool js_cocos2dx_dragonbones_DBCCArmature_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DBCCArmature_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DBCCArmature(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DBCCArmature_getCCBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmature_getCCEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmature_getArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmature_setArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmature_getCCSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmature_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmature_DBCCArmature(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCArmatureNode_class;
extern JSObject *jsb_dragonBones_DBCCArmatureNode_prototype;

bool js_cocos2dx_dragonbones_DBCCArmatureNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DBCCArmatureNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DBCCArmatureNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_setBaseColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getCCEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getCCSlot(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getInnerBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_setCompleteListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_loadingDataCallBack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_advanceTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_initWithDBCCArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_createWithWorldClock(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCArmatureNode_DBCCArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCSprite_class;
extern JSObject *jsb_dragonBones_DBCCSprite_prototype;

bool js_cocos2dx_dragonbones_DBCCSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DBCCSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DBCCSprite(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DBCCSprite_setColorByShader(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCSprite_DBCCSprite(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCFactory_class;
extern JSObject *jsb_dragonBones_DBCCFactory_prototype;

bool js_cocos2dx_dragonbones_DBCCFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DBCCFactory_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DBCCFactory(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DBCCFactory_buildArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_refreshTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCFactory_DBCCFactory(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_dragonBones_DBCCHelper_class;
extern JSObject *jsb_dragonBones_DBCCHelper_prototype;

bool js_cocos2dx_dragonbones_DBCCHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_dragonbones_DBCCHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_dragonbones_DBCCHelper(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_dragonbones_DBCCHelper_onRemovedArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCHelper_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCHelper_getImagePathFromAtlasPath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCHelper_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_dragonbones_DBCCHelper_DBCCHelper(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_dragonbones_h__
