LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := baseframework_static

LOCAL_MODULE_FILENAME := libbaseframework

LOCAL_SRC_FILES := framework/FrameworkDelegate.cpp \
framework/network/socket/DefaultSocket.cpp \
framework/network/socket/GsnClient.cpp \
framework/network/socket/InPacket.cpp \
framework/network/socket/OutPacket.cpp \
framework/network/socket/PacketHeaderAnalyze.cpp \
framework/network/socket/sPackage.cpp \
framework/platform/NativeService.cpp 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..
						   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static

include $(BUILD_STATIC_LIBRARY)
