/**
 * @module cocos2dx_dragonbones
 */
var db = db || {};

/**
 * @class DragonBonesData
 */
db.DragonBonesData = {

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method getArmatureData
 * @param {String} arg0
 * @return {dragonBones.ArmatureData}
 */
getArmatureData : function (
str 
)
{
    return dragonBones.ArmatureData;
},

/**
 * @method DragonBonesData
 * @constructor
 */
DragonBonesData : function (
)
{
},

};

/**
 * @class ITextureAtlas
 */
db.ITextureAtlas = {

/**
 * @method dispose
 */
dispose : function (
)
{
},

};

/**
 * @class IAnimatable
 */
db.IAnimatable = {

/**
 * @method advanceTime
 * @param {float} arg0
 */
advanceTime : function (
float 
)
{
},

/**
 * @method IAnimatable
 * @constructor
 */
IAnimatable : function (
)
{
},

};

/**
 * @class Object
 */
db.Object = {

/**
 * @method getParent
 * @return {dragonBones.Bone}
 */
getParent : function (
)
{
    return dragonBones.Bone;
},

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method getArmature
 * @return {dragonBones.Armature}
 */
getArmature : function (
)
{
    return dragonBones.Armature;
},

/**
 * @method getVisible
 * @return {bool}
 */
getVisible : function (
)
{
    return false;
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method Object
 * @constructor
 */
Object : function (
)
{
},

};

/**
 * @class AnimationState
 */
db.AnimationState = {

/**
 * @method setCurrentTime
 * @param {float} arg0
 * @return {dragonBones.AnimationState}
 */
setCurrentTime : function (
float 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method setTimeScale
 * @param {float} arg0
 * @return {dragonBones.AnimationState}
 */
setTimeScale : function (
float 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method setAdditiveBlending
 * @param {bool} arg0
 * @return {dragonBones.AnimationState}
 */
setAdditiveBlending : function (
bool 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getClip
 * @return {dragonBones.AnimationData}
 */
getClip : function (
)
{
    return dragonBones.AnimationData;
},

/**
 * @method setPlayTimes
 * @param {int} arg0
 * @return {dragonBones.AnimationState}
 */
setPlayTimes : function (
int 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method removeMixingTransform
 * @param {String} arg0
 * @param {bool} arg1
 * @return {dragonBones.AnimationState}
 */
removeMixingTransform : function (
str, 
bool 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getGroup
 * @return {String}
 */
getGroup : function (
)
{
    return ;
},

/**
 * @method getCurrentPlayTimes
 * @return {int}
 */
getCurrentPlayTimes : function (
)
{
    return 0;
},

/**
 * @method removeAllMixingTransform
 * @return {dragonBones.AnimationState}
 */
removeAllMixingTransform : function (
)
{
    return dragonBones.AnimationState;
},

/**
 * @method addMixingTransform
 * @param {String} arg0
 * @param {bool} arg1
 * @return {dragonBones.AnimationState}
 */
addMixingTransform : function (
str, 
bool 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getCurrentTime
 * @return {float}
 */
getCurrentTime : function (
)
{
    return 0;
},

/**
 * @method setAutoFadeOut
 * @param {bool} arg0
 * @param {float} arg1
 * @return {dragonBones.AnimationState}
 */
setAutoFadeOut : function (
bool, 
float 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getTotalTime
 * @return {float}
 */
getTotalTime : function (
)
{
    return 0;
},

/**
 * @method getLayer
 * @return {int}
 */
getLayer : function (
)
{
    return 0;
},

/**
 * @method getPlayTimes
 * @return {int}
 */
getPlayTimes : function (
)
{
    return 0;
},

/**
 * @method play
 * @return {dragonBones.AnimationState}
 */
play : function (
)
{
    return dragonBones.AnimationState;
},

/**
 * @method fadeOut
 * @param {float} arg0
 * @param {bool} arg1
 * @return {dragonBones.AnimationState}
 */
fadeOut : function (
float, 
bool 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method stop
 * @return {dragonBones.AnimationState}
 */
stop : function (
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getCurrentWeight
 * @return {float}
 */
getCurrentWeight : function (
)
{
    return 0;
},

/**
 * @method getIsComplete
 * @return {bool}
 */
getIsComplete : function (
)
{
    return false;
},

/**
 * @method getTimeScale
 * @return {float}
 */
getTimeScale : function (
)
{
    return 0;
},

/**
 * @method setFrameTween
 * @param {bool} arg0
 * @param {bool} arg1
 * @return {dragonBones.AnimationState}
 */
setFrameTween : function (
bool, 
bool 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method setWeight
 * @param {float} arg0
 * @return {dragonBones.AnimationState}
 */
setWeight : function (
float 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getMixingTransform
 * @param {String} arg0
 * @return {bool}
 */
getMixingTransform : function (
str 
)
{
    return false;
},

/**
 * @method getIsPlaying
 * @return {bool}
 */
getIsPlaying : function (
)
{
    return false;
},

/**
 * @method AnimationState
 * @constructor
 */
AnimationState : function (
)
{
},

};

/**
 * @class Animation
 */
db.Animation = {

/**
 * @method getAnimationList
 * @return {Array}
 */
getAnimationList : function (
)
{
    return new Array();
},

/**
 * @method setTimeScale
 * @param {float} arg0
 */
setTimeScale : function (
float 
)
{
},

/**
 * @method stop
 */
stop : function (
)
{
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method play
 */
play : function (
)
{
},

/**
 * @method hasAnimation
 * @param {String} arg0
 * @return {bool}
 */
hasAnimation : function (
str 
)
{
    return false;
},

/**
 * @method getLastAnimationState
 * @return {dragonBones.AnimationState}
 */
getLastAnimationState : function (
)
{
    return dragonBones.AnimationState;
},

/**
 * @method gotoAndPlay
 * @param {String} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @param {int} arg4
 * @param {String} arg5
 * @param {dragonBones.Animation.AnimationFadeOutMode} arg6
 * @param {bool} arg7
 * @param {bool} arg8
 * @return {dragonBones.AnimationState}
 */
gotoAndPlay : function (
str, 
float, 
float, 
int, 
int, 
str, 
animationfadeoutmode, 
bool, 
bool 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getState
 * @param {String} arg0
 * @param {int} arg1
 * @return {dragonBones.AnimationState}
 */
getState : function (
str, 
int 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getIsComplete
 * @return {bool}
 */
getIsComplete : function (
)
{
    return false;
},

/**
 * @method advanceTime
 * @param {float} arg0
 */
advanceTime : function (
float 
)
{
},

/**
 * @method getCurrentAnimationName
 * @return {String}
 */
getCurrentAnimationName : function (
)
{
    return ;
},

/**
 * @method getIsPlaying
 * @return {bool}
 */
getIsPlaying : function (
)
{
    return false;
},

/**
 * @method gotoAndStop
 * @param {String} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {float} arg3
 * @param {float} arg4
 * @param {int} arg5
 * @param {String} arg6
 * @param {dragonBones.Animation.AnimationFadeOutMode} arg7
 * @return {dragonBones.AnimationState}
 */
gotoAndStop : function (
str, 
float, 
float, 
float, 
float, 
int, 
str, 
animationfadeoutmode 
)
{
    return dragonBones.AnimationState;
},

/**
 * @method getTimeScale
 * @return {float}
 */
getTimeScale : function (
)
{
    return 0;
},

/**
 * @method Animation
 * @constructor
 */
Animation : function (
)
{
},

};

/**
 * @class Armature
 */
db.Armature = {

/**
 * @method getBone
 * @param {String} arg0
 * @return {dragonBones.Bone}
 */
getBone : function (
str 
)
{
    return dragonBones.Bone;
},

/**
 * @method getSlot
 * @param {String} arg0
 * @return {dragonBones.Slot}
 */
getSlot : function (
str 
)
{
    return dragonBones.Slot;
},

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method setInheritAnimation
 * @param {bool} arg0
 */
setInheritAnimation : function (
bool 
)
{
},

/**
 * @method replaceSlot
 * @param {String} arg0
 * @param {String} arg1
 * @param {dragonBones.Slot} arg2
 */
replaceSlot : function (
str, 
str, 
slot 
)
{
},

/**
 * @method removeBone
* @param {String|dragonBones.Bone} str
* @return {dragonBones.Bone}
*/
removeBone : function(
bone 
)
{
},

/**
 * @method getDisplay
 * @return {}
 */
getDisplay : function (
)
{
    return ;
},

/**
 * @method addSlot
 * @param {dragonBones.Slot} arg0
 * @param {String} arg1
 */
addSlot : function (
slot, 
str 
)
{
},

/**
 * @method invalidUpdate
* @param {String} str
*/
invalidUpdate : function(
str 
)
{
},

/**
 * @method getBoneByDisplay
 * @param {} arg0
 * @return {dragonBones.Bone}
 */
getBoneByDisplay : function (
 
)
{
    return dragonBones.Bone;
},

/**
 * @method removeSlot
* @param {String|dragonBones.Slot} str
* @return {dragonBones.Slot}
*/
removeSlot : function(
slot 
)
{
},

/**
 * @method isInheritAnimation
 * @return {bool}
 */
isInheritAnimation : function (
)
{
    return false;
},

/**
 * @method addBone
* @param {dragonBones.Bone|dragonBones.Bone} bone
* @param {String} str
*/
addBone : function(
bone,
str 
)
{
},

/**
 * @method getArmatureData
 * @return {dragonBones.ArmatureData}
 */
getArmatureData : function (
)
{
    return dragonBones.ArmatureData;
},

/**
 * @method getAnimation
 * @return {dragonBones.Animation}
 */
getAnimation : function (
)
{
    return dragonBones.Animation;
},

/**
 * @method sortSlotsByZOrder
 */
sortSlotsByZOrder : function (
)
{
},

/**
 * @method getSlotByDisplay
 * @param {} arg0
 * @return {dragonBones.Slot}
 */
getSlotByDisplay : function (
 
)
{
    return dragonBones.Slot;
},

/**
 * @method getEventDispatcher
 * @return {dragonBones.IEventDispatcher}
 */
getEventDispatcher : function (
)
{
    return dragonBones.IEventDispatcher;
},

/**
 * @method Armature
 * @constructor
 * @param {dragonBones.ArmatureData} arg0
 * @param {dragonBones.Animation} arg1
 * @param {dragonBones.IEventDispatcher} arg2
 * @param {} arg3
 */
Armature : function (
armaturedata, 
animation, 
ieventdispatcher
 
)
{
},

};

/**
 * @class Bone
 */
db.Bone = {

/**
 * @method addChild
 * @param {dragonBones.Object} arg0
 */
addChild : function (
object 
)
{
},

/**
 * @method getSlot
 * @return {dragonBones.Slot}
 */
getSlot : function (
)
{
    return dragonBones.Slot;
},

/**
 * @method contains
 * @param {dragonBones.Object} arg0
 * @return {bool}
 */
contains : function (
object 
)
{
    return false;
},

/**
 * @method removeChild
 * @param {dragonBones.Object} arg0
 */
removeChild : function (
object 
)
{
},

/**
 * @method invalidUpdate
 */
invalidUpdate : function (
)
{
},

/**
 * @method Bone
 * @constructor
 */
Bone : function (
)
{
},

};

/**
 * @class BaseFactory
 */
db.BaseFactory = {

/**
 * @method buildArmature
* @param {String|String|String} str
* @param {String|String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @return {dragonBones.Armature|dragonBones.Armature|dragonBones.Armature}
*/
buildArmature : function(
str,
str,
str,
str,
str 
)
{
    return dragonBones.Armature;
},

/**
 * @method removeDragonBonesData
 * @param {String} arg0
 * @param {bool} arg1
 */
removeDragonBonesData : function (
str, 
bool 
)
{
},

/**
 * @method addTextureAtlas
 * @param {dragonBones.ITextureAtlas} arg0
 * @param {String} arg1
 */
addTextureAtlas : function (
itextureatlas, 
str 
)
{
},

/**
 * @method addDragonBonesData
 * @param {dragonBones.DragonBonesData} arg0
 * @param {String} arg1
 */
addDragonBonesData : function (
dragonbonesdata, 
str 
)
{
},

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method getTextureAtlas
 * @param {String} arg0
 * @return {dragonBones.ITextureAtlas}
 */
getTextureAtlas : function (
str 
)
{
    return dragonBones.ITextureAtlas;
},

/**
 * @method getTextureDisplay
 * @param {String} arg0
 * @param {String} arg1
 * @param {dragonBones.DisplayData} arg2
 * @return {}
 */
getTextureDisplay : function (
str, 
str, 
displaydata 
)
{
    return ;
},

/**
 * @method removeTextureAtlas
 * @param {String} arg0
 * @param {bool} arg1
 */
removeTextureAtlas : function (
str, 
bool 
)
{
},

/**
 * @method getDragonBonesData
 * @param {String} arg0
 * @return {dragonBones.DragonBonesData}
 */
getDragonBonesData : function (
str 
)
{
    return dragonBones.DragonBonesData;
},

/**
 * @method BaseFactory
 * @constructor
 */
BaseFactory : function (
)
{
},

};

/**
 * @class DBCCSlot
 */
db.DBCCSlot = {

/**
 * @method dispose
 */
dispose : function (
)
{
},

/**
 * @method getGlobalPosition
 * @return {vec2_object}
 */
getGlobalPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method getCCChildArmature
 * @return {dragonBones.DBCCArmature}
 */
getCCChildArmature : function (
)
{
    return dragonBones.DBCCArmature;
},

/**
 * @method getCCDisplay
 * @return {cc.Node}
 */
getCCDisplay : function (
)
{
    return cc.Node;
},

/**
 * @method setDisplayImage
 * @param {cc.Node} arg0
 * @param {bool} arg1
 */
setDisplayImage : function (
node, 
bool 
)
{
},

/**
 * @method DBCCSlot
 * @constructor
 * @param {dragonBones.SlotData} arg0
 */
DBCCSlot : function (
slotdata 
)
{
},

};

/**
 * @class DBCCArmature
 */
db.DBCCArmature = {

/**
 * @method getCCBoundingBox
 * @return {rect_object}
 */
getCCBoundingBox : function (
)
{
    return cc.Rect;
},

/**
 * @method getCCEventDispatcher
 * @return {cc.EventDispatcher}
 */
getCCEventDispatcher : function (
)
{
    return cc.EventDispatcher;
},

/**
 * @method getArmatureNode
 * @return {dragonBones.DBCCArmatureNode}
 */
getArmatureNode : function (
)
{
    return dragonBones.DBCCArmatureNode;
},

/**
 * @method setArmatureNode
 * @param {dragonBones.DBCCArmatureNode} arg0
 */
setArmatureNode : function (
dbccarmaturenode 
)
{
},

/**
 * @method getCCSlot
 * @param {String} arg0
 * @return {dragonBones.DBCCSlot}
 */
getCCSlot : function (
str 
)
{
    return dragonBones.DBCCSlot;
},

/**
 * @method getCCDisplay
 * @return {cc.Node}
 */
getCCDisplay : function (
)
{
    return cc.Node;
},

/**
 * @method DBCCArmature
 * @constructor
 * @param {dragonBones.ArmatureData} arg0
 * @param {dragonBones.Animation} arg1
 * @param {dragonBones.IEventDispatcher} arg2
 * @param {cc.Node} arg3
 */
DBCCArmature : function (
armaturedata, 
animation, 
ieventdispatcher, 
node 
)
{
},

};

/**
 * @class DBCCArmatureNode
 */
db.DBCCArmatureNode = {

/**
 * @method draw
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
draw : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method setBaseColor
 * @param {int} arg0
 * @param {int} arg1
 * @param {int} arg2
 */
setBaseColor : function (
int, 
int, 
int 
)
{
},

/**
 * @method getCCEventDispatcher
 * @return {cc.EventDispatcher}
 */
getCCEventDispatcher : function (
)
{
    return cc.EventDispatcher;
},

/**
 * @method setEnableBlend
 * @param {bool} arg0
 */
setEnableBlend : function (
bool 
)
{
},

/**
 * @method getAnimation
 * @return {dragonBones.Animation}
 */
getAnimation : function (
)
{
    return dragonBones.Animation;
},

/**
 * @method getArmature
 * @return {dragonBones.DBCCArmature}
 */
getArmature : function (
)
{
    return dragonBones.DBCCArmature;
},

/**
 * @method getCCSlot
 * @param {String} arg0
 * @return {dragonBones.DBCCSlot}
 */
getCCSlot : function (
str 
)
{
    return dragonBones.DBCCSlot;
},

/**
 * @method getInnerBoundingBox
 * @return {rect_object}
 */
getInnerBoundingBox : function (
)
{
    return cc.Rect;
},

/**
 * @method setCompleteListener
 * @param {function} arg0
 */
setCompleteListener : function (
func 
)
{
},

/**
 * @method loadingDataCallBack
 * @param {String} arg0
 * @param {String} arg1
 * @param {int} arg2
 */
loadingDataCallBack : function (
str, 
str, 
int 
)
{
},

/**
 * @method advanceTime
 * @param {float} arg0
 */
advanceTime : function (
float 
)
{
},

/**
 * @method initWithDBCCArmature
 * @param {dragonBones.DBCCArmature} arg0
 * @param {dragonBones.WorldClock} arg1
 * @return {bool}
 */
initWithDBCCArmature : function (
dbccarmature, 
worldclock 
)
{
    return false;
},

/**
 * @method getCCDisplay
 * @return {cc.Node}
 */
getCCDisplay : function (
)
{
    return cc.Node;
},

/**
 * @method create
 * @param {dragonBones.DBCCArmature} arg0
 * @return {dragonBones.DBCCArmatureNode}
 */
create : function (
dbccarmature 
)
{
    return dragonBones.DBCCArmatureNode;
},

/**
 * @method createWithWorldClock
 * @param {dragonBones.DBCCArmature} arg0
 * @param {dragonBones.WorldClock} arg1
 * @return {dragonBones.DBCCArmatureNode}
 */
createWithWorldClock : function (
dbccarmature, 
worldclock 
)
{
    return null;
},

/**
 * @method DBCCArmatureNode
 * @constructor
 */
DBCCArmatureNode : function (
)
{
},

};

/**
 * @class DBCCSprite
 */
db.DBCCSprite = {

/**
 * @method setColorByShader
 * @param {int} arg0
 * @param {int} arg1
 * @param {int} arg2
 */
setColorByShader : function (
int, 
int, 
int 
)
{
},

/**
 * @method createWithSpriteFrame
 * @param {cc.SpriteFrame} arg0
 * @return {dragonBones.DBCCSprite}
 */
createWithSpriteFrame : function (
spriteframe 
)
{
    return dragonBones.DBCCSprite;
},

/**
 * @method DBCCSprite
 * @constructor
 */
DBCCSprite : function (
)
{
},

};

/**
 * @class DBCCFactory
 */
db.DBCCFactory = {

/**
 * @method buildArmatureNode
* @param {String|String|String} str
* @param {String|String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @return {dragonBones.DBCCArmatureNode|dragonBones.DBCCArmatureNode|dragonBones.DBCCArmatureNode}
*/
buildArmatureNode : function(
str,
str,
str,
str,
str 
)
{
    return dragonBones.DBCCArmatureNode;
},

/**
 * @method hasDragonBones
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @return {bool}
 */
hasDragonBones : function (
str, 
str, 
str 
)
{
    return false;
},

/**
 * @method loadTextureAtlas
 * @param {String} arg0
 * @param {String} arg1
 * @return {dragonBones.ITextureAtlas}
 */
loadTextureAtlas : function (
str, 
str 
)
{
    return dragonBones.ITextureAtlas;
},

/**
 * @method refreshAllTextureAtlasTexture
 */
refreshAllTextureAtlasTexture : function (
)
{
},

/**
 * @method refreshTextureAtlasTexture
 * @param {String} arg0
 */
refreshTextureAtlasTexture : function (
str 
)
{
},

/**
 * @method loadDragonBonesData
 * @param {String} arg0
 * @param {String} arg1
 * @return {dragonBones.DragonBonesData}
 */
loadDragonBonesData : function (
str, 
str 
)
{
    return dragonBones.DragonBonesData;
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {dragonBones.DBCCFactory}
 */
getInstance : function (
)
{
    return dragonBones.DBCCFactory;
},

/**
 * @method DBCCFactory
 * @constructor
 */
DBCCFactory : function (
)
{
},

};
