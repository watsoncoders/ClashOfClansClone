#include "base/ccConfig.h"
#ifndef __cocos2dx_baseframework_h__
#define __cocos2dx_baseframework_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_fr_sPackage_class;
extern JSObject *jsb_fr_sPackage_prototype;

bool js_cocos2dx_baseframework_sPackage_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_baseframework_sPackage_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_baseframework_sPackage(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_baseframework(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_baseframework_sPackage_sPackage(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_fr_InPacket_class;
extern JSObject *jsb_fr_InPacket_prototype;

bool js_cocos2dx_baseframework_InPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_baseframework_InPacket_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_baseframework_InPacket(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_baseframework(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_baseframework_InPacket_getDouble(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getCmdId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getByte(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getError(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getLong(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getBool(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getInt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getControllerId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getUnsignedShort(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getShort(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getCharArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_getBytes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_InPacket_InPacket(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_fr_OutPacket_class;
extern JSObject *jsb_fr_OutPacket_prototype;

bool js_cocos2dx_baseframework_OutPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_baseframework_OutPacket_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_baseframework_OutPacket(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_baseframework(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_baseframework_OutPacket_reset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putInt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_setCmdId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_packHeader(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_setControllerId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putUnsignedShort(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putShort(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_initData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putBytes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putLong(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_updateSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_getData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putByteArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_putByte(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_updateUnsignedShortAtPos(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_OutPacket_OutPacket(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_fr_GsnClient_class;
extern JSObject *jsb_fr_GsnClient_prototype;

bool js_cocos2dx_baseframework_GsnClient_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_baseframework_GsnClient_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_baseframework_GsnClient(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_baseframework(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_baseframework_GsnClient_onSubThreadStarted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_onSubThreadEnded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_setTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_disconnect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_setReceiveDataListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_isDoConnection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_initThread(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_setTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_createSocket(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_onSubThreadLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_getTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_setFinishConnectListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_onUIThreadReceiveMessage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_setDisconnectListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_setListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_getTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_connect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_reconnect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_clearQueue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_send(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_GsnClient_GsnClient(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_fr_NativeService_class;
extern JSObject *jsb_fr_NativeService_prototype;

bool js_cocos2dx_baseframework_NativeService_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_baseframework_NativeService_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_baseframework_NativeService(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_baseframework(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_baseframework_NativeService_getFolderUpdateAssets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_baseframework_NativeService_applicationDidFinishLaunching(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_baseframework_h__
