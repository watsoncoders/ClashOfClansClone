LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := dragonbones_static

LOCAL_MODULE_FILENAME := libdragonbones

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := animation/Animation.cpp \
animation/AnimationState.cpp \
animation/TimelineState.cpp \
animation/WorldClock.cpp \
core/Armature.cpp \
core/Bone.cpp \
core/Object.cpp \
core/Slot.cpp \
events/EventData.cpp \
factories/BaseFactory.cpp \
parsers/BaseDataParser.cpp \
parsers/ConstValues.cpp \
parsers/dbtinyxml2.cpp \
parsers/XMLDataParser.cpp \
renderer/DBCCArmature.cpp \
renderer/DBCCArmatureNode.cpp \
renderer/DBCCFactory.cpp \
renderer/DBCCHelper.cpp \
renderer/DBCCLuaUtils.cpp \
renderer/DBCCSlot.cpp \
renderer/PlistDataParser.cpp\
renderer/DBCCSprite.cpp

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static

LOCAL_CXXFLAGS += -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/. \
                           $(LOCAL_PATH)/..

include $(BUILD_STATIC_LIBRARY)
