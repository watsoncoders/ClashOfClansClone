#include "jsb_cocos2dx_baseframework_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "BaseFramework.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_fr_sPackage_class;
JSObject *jsb_fr_sPackage_prototype;

bool js_cocos2dx_baseframework_sPackage_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    fr::sPackage* cobj = new (std::nothrow) fr::sPackage();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<fr::sPackage> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "fr::sPackage");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_fr_sPackage_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (sPackage)", obj);
}
void js_register_cocos2dx_baseframework_sPackage(JSContext *cx, JS::HandleObject global) {
    jsb_fr_sPackage_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_fr_sPackage_class->name = "sPackage";
    jsb_fr_sPackage_class->addProperty = JS_PropertyStub;
    jsb_fr_sPackage_class->delProperty = JS_DeletePropertyStub;
    jsb_fr_sPackage_class->getProperty = JS_PropertyStub;
    jsb_fr_sPackage_class->setProperty = JS_StrictPropertyStub;
    jsb_fr_sPackage_class->enumerate = JS_EnumerateStub;
    jsb_fr_sPackage_class->resolve = JS_ResolveStub;
    jsb_fr_sPackage_class->convert = JS_ConvertStub;
    jsb_fr_sPackage_class->finalize = js_fr_sPackage_finalize;
    jsb_fr_sPackage_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_fr_sPackage_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_fr_sPackage_class,
        js_cocos2dx_baseframework_sPackage_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "sPackage", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<fr::sPackage> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_fr_sPackage_class;
        p->proto = jsb_fr_sPackage_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_fr_InPacket_class;
JSObject *jsb_fr_InPacket_prototype;

bool js_cocos2dx_baseframework_InPacket_getDouble(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getDouble : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDouble();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getDouble : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getCmdId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getCmdId : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCmdId();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getCmdId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getByte(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getByte : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getByte();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getByte : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getError(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getError : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getError();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getError : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getLong(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getLong : Invalid Native Object");
    if (argc == 0) {
        long long ret = cobj->getLong();
        jsval jsret = JSVAL_NULL;
        jsret = long_long_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getLong : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getBool(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getBool : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getBool();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getBool : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getInt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getInt : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getInt();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getInt : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_init : Invalid Native Object");
    if (argc == 1) {
        fr::sPackage* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (fr::sPackage*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_InPacket_init : Error processing arguments");
        cobj->init(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getControllerId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getControllerId : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getControllerId();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getControllerId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getUnsignedShort(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getUnsignedShort : Invalid Native Object");
    if (argc == 0) {
        unsigned short ret = cobj->getUnsignedShort();
        jsval jsret = JSVAL_NULL;
        jsret = ushort_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getUnsignedShort : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getShort(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getShort : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getShort();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getShort : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getCharArray(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getCharArray : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_InPacket_getCharArray : Error processing arguments");
        char* ret = cobj->getCharArray(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getCharArray : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_getBytes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::InPacket* cobj = (fr::InPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_InPacket_getBytes : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_InPacket_getBytes : Error processing arguments");
        char* ret = cobj->getBytes(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_InPacket_getBytes : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_InPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    fr::InPacket* cobj = new (std::nothrow) fr::InPacket();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<fr::InPacket> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "fr::InPacket");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}static bool js_cocos2dx_baseframework_InPacket_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    fr::InPacket *nobj = new (std::nothrow) fr::InPacket();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "fr::InPacket");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

void js_fr_InPacket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (InPacket)", obj);
}
    
void js_register_cocos2dx_baseframework_InPacket(JSContext *cx, JS::HandleObject global) {
    jsb_fr_InPacket_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_fr_InPacket_class->name = "InPacket";
    jsb_fr_InPacket_class->addProperty = JS_PropertyStub;
    jsb_fr_InPacket_class->delProperty = JS_DeletePropertyStub;
    jsb_fr_InPacket_class->getProperty = JS_PropertyStub;
    jsb_fr_InPacket_class->setProperty = JS_StrictPropertyStub;
    jsb_fr_InPacket_class->enumerate = JS_EnumerateStub;
    jsb_fr_InPacket_class->resolve = JS_ResolveStub;
    jsb_fr_InPacket_class->convert = JS_ConvertStub;
    jsb_fr_InPacket_class->finalize = js_fr_InPacket_finalize;
    jsb_fr_InPacket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getDouble", js_cocos2dx_baseframework_InPacket_getDouble, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCmdId", js_cocos2dx_baseframework_InPacket_getCmdId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getByte", js_cocos2dx_baseframework_InPacket_getByte, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getError", js_cocos2dx_baseframework_InPacket_getError, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLong", js_cocos2dx_baseframework_InPacket_getLong, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBool", js_cocos2dx_baseframework_InPacket_getBool, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInt", js_cocos2dx_baseframework_InPacket_getInt, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_baseframework_InPacket_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getControllerId", js_cocos2dx_baseframework_InPacket_getControllerId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_baseframework_InPacket_getString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUnsignedShort", js_cocos2dx_baseframework_InPacket_getUnsignedShort, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getShort", js_cocos2dx_baseframework_InPacket_getShort, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCharArray", js_cocos2dx_baseframework_InPacket_getCharArray, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBytes", js_cocos2dx_baseframework_InPacket_getBytes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_baseframework_InPacket_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_fr_InPacket_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_fr_InPacket_class,
        js_cocos2dx_baseframework_InPacket_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "InPacket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<fr::InPacket> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_fr_InPacket_class;
        p->proto = jsb_fr_InPacket_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
    anonEvaluate(cx, global, "(function () { fr.InPacket.extend = cc.Class.extend; })()");
}

JSClass  *jsb_fr_OutPacket_class;
JSObject *jsb_fr_OutPacket_prototype;

bool js_cocos2dx_baseframework_OutPacket_reset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_reset : Invalid Native Object");
    if (argc == 0) {
        cobj->reset();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_reset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putInt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putInt : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putInt : Error processing arguments");
        fr::OutPacket* ret = cobj->putInt(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putInt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_setCmdId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_setCmdId : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_setCmdId : Error processing arguments");
        cobj->setCmdId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_setCmdId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_packHeader(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_packHeader : Invalid Native Object");
    if (argc == 0) {
        cobj->packHeader();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_packHeader : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_setControllerId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_setControllerId : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_setControllerId : Error processing arguments");
        cobj->setControllerId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_setControllerId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putUnsignedShort(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putUnsignedShort : Invalid Native Object");
    if (argc == 1) {
        unsigned short arg0;
        ok &= jsval_to_ushort(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putUnsignedShort : Error processing arguments");
        fr::OutPacket* ret = cobj->putUnsignedShort(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putUnsignedShort : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putShort(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putShort : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putShort : Error processing arguments");
        fr::OutPacket* ret = cobj->putShort(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putShort : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putString : Error processing arguments");
        fr::OutPacket* ret = cobj->putString(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_initData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_initData : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_initData : Error processing arguments");
        cobj->initData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_initData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putBytes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putBytes : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putBytes : Error processing arguments");
        fr::OutPacket* ret = cobj->putBytes(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putBytes : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putLong(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putLong : Invalid Native Object");
    if (argc == 1) {
        long long arg0;
        ok &= jsval_to_long_long(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putLong : Error processing arguments");
        fr::OutPacket* ret = cobj->putLong(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putLong : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_updateSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_updateSize : Invalid Native Object");
    if (argc == 0) {
        cobj->updateSize();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_updateSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_getData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_getData : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_getData : Error processing arguments");
        char* ret = cobj->getData(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_getData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putByteArray(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putByteArray : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putByteArray : Error processing arguments");
        fr::OutPacket* ret = cobj->putByteArray(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putByteArray : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_putByte(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_putByte : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_putByte : Error processing arguments");
        fr::OutPacket* ret = cobj->putByte(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::OutPacket>(cx, (fr::OutPacket*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_putByte : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_updateUnsignedShortAtPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::OutPacket* cobj = (fr::OutPacket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_OutPacket_updateUnsignedShortAtPos : Invalid Native Object");
    if (argc == 2) {
        unsigned short arg0;
        int arg1;
        ok &= jsval_to_ushort(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_OutPacket_updateUnsignedShortAtPos : Error processing arguments");
        cobj->updateUnsignedShortAtPos(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_OutPacket_updateUnsignedShortAtPos : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_baseframework_OutPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    fr::OutPacket* cobj = new (std::nothrow) fr::OutPacket();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<fr::OutPacket> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "fr::OutPacket");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}static bool js_cocos2dx_baseframework_OutPacket_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    fr::OutPacket *nobj = new (std::nothrow) fr::OutPacket();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "fr::OutPacket");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

void js_fr_OutPacket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (OutPacket)", obj);
}
    
void js_register_cocos2dx_baseframework_OutPacket(JSContext *cx, JS::HandleObject global) {
    jsb_fr_OutPacket_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_fr_OutPacket_class->name = "OutPacket";
    jsb_fr_OutPacket_class->addProperty = JS_PropertyStub;
    jsb_fr_OutPacket_class->delProperty = JS_DeletePropertyStub;
    jsb_fr_OutPacket_class->getProperty = JS_PropertyStub;
    jsb_fr_OutPacket_class->setProperty = JS_StrictPropertyStub;
    jsb_fr_OutPacket_class->enumerate = JS_EnumerateStub;
    jsb_fr_OutPacket_class->resolve = JS_ResolveStub;
    jsb_fr_OutPacket_class->convert = JS_ConvertStub;
    jsb_fr_OutPacket_class->finalize = js_fr_OutPacket_finalize;
    jsb_fr_OutPacket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("reset", js_cocos2dx_baseframework_OutPacket_reset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putInt", js_cocos2dx_baseframework_OutPacket_putInt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCmdId", js_cocos2dx_baseframework_OutPacket_setCmdId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("packHeader", js_cocos2dx_baseframework_OutPacket_packHeader, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setControllerId", js_cocos2dx_baseframework_OutPacket_setControllerId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putUnsignedShort", js_cocos2dx_baseframework_OutPacket_putUnsignedShort, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putShort", js_cocos2dx_baseframework_OutPacket_putShort, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putString", js_cocos2dx_baseframework_OutPacket_putString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initData", js_cocos2dx_baseframework_OutPacket_initData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putBytes", js_cocos2dx_baseframework_OutPacket_putBytes, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putLong", js_cocos2dx_baseframework_OutPacket_putLong, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateSize", js_cocos2dx_baseframework_OutPacket_updateSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getData", js_cocos2dx_baseframework_OutPacket_getData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putByteArray", js_cocos2dx_baseframework_OutPacket_putByteArray, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putByte", js_cocos2dx_baseframework_OutPacket_putByte, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateUnsignedShortAtPos", js_cocos2dx_baseframework_OutPacket_updateUnsignedShortAtPos, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_baseframework_OutPacket_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_fr_OutPacket_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_fr_OutPacket_class,
        js_cocos2dx_baseframework_OutPacket_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "OutPacket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<fr::OutPacket> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_fr_OutPacket_class;
        p->proto = jsb_fr_OutPacket_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
    anonEvaluate(cx, global, "(function () { fr.OutPacket.extend = cc.Class.extend; })()");
}

JSClass  *jsb_fr_GsnClient_class;
JSObject *jsb_fr_GsnClient_prototype;

bool js_cocos2dx_baseframework_GsnClient_onSubThreadStarted(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_onSubThreadStarted : Invalid Native Object");
    if (argc == 0) {
        cobj->onSubThreadStarted();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_onSubThreadStarted : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_onSubThreadEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_onSubThreadEnded : Invalid Native Object");
    if (argc == 0) {
        cobj->onSubThreadEnded();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_onSubThreadEnded : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_setTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_setTimeoutForRead : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_setTimeoutForRead : Error processing arguments");
        cobj->setTimeoutForRead(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_setTimeoutForRead : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_disconnect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_disconnect : Invalid Native Object");
    if (argc == 0) {
        cobj->disconnect();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_disconnect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_setReceiveDataListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_setReceiveDataListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (int, fr::sPackage *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](int larg0, fr::sPackage* larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            do {
		            if (larg1) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<fr::sPackage>(cx, (fr::sPackage*)larg1);
		                largv[1] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[1] = JSVAL_NULL;
		            }
		        } while (0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(2, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_setReceiveDataListener : Error processing arguments");
        cobj->setReceiveDataListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_setReceiveDataListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_isDoConnection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_isDoConnection : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDoConnection();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_isDoConnection : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_initThread(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_initThread : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->initThread();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_initThread : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_setTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_setTimeoutForConnect : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_setTimeoutForConnect : Error processing arguments");
        cobj->setTimeoutForConnect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_setTimeoutForConnect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_createSocket(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_createSocket : Invalid Native Object");
    if (argc == 0) {
        cobj->createSocket();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_createSocket : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_onSubThreadLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_onSubThreadLoop : Invalid Native Object");
    if (argc == 0) {
        cobj->onSubThreadLoop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_onSubThreadLoop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_getTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_getTimeoutForRead : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getTimeoutForRead();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_getTimeoutForRead : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_setFinishConnectListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_setFinishConnectListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (bool)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](bool larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            largv[0] = BOOLEAN_TO_JSVAL(larg0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_setFinishConnectListener : Error processing arguments");
        cobj->setFinishConnectListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_setFinishConnectListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_onUIThreadReceiveMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_onUIThreadReceiveMessage : Invalid Native Object");
    if (argc == 1) {
        fr::sPackage* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (fr::sPackage*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_onUIThreadReceiveMessage : Error processing arguments");
        cobj->onUIThreadReceiveMessage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_onUIThreadReceiveMessage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_setDisconnectListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_setDisconnectListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void ()> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_setDisconnectListener : Error processing arguments");
        cobj->setDisconnectListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_setDisconnectListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_setListener : Invalid Native Object");
    if (argc == 1) {
        fr::ClientListener* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (fr::ClientListener*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_setListener : Error processing arguments");
        cobj->setListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_setListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_getTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_getTimeoutForConnect : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getTimeoutForConnect();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_getTimeoutForConnect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_connect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_connect : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_connect : Error processing arguments");
        cobj->connect(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_connect : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_reconnect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_reconnect : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->reconnect();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_reconnect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_clearQueue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_clearQueue : Invalid Native Object");
    if (argc == 0) {
        cobj->clearQueue();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_clearQueue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_send(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    fr::GsnClient* cobj = (fr::GsnClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_baseframework_GsnClient_send : Invalid Native Object");
    if (argc == 1) {
        fr::OutPacket* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (fr::OutPacket*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_baseframework_GsnClient_send : Error processing arguments");
        cobj->send(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_send : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_baseframework_GsnClient_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        fr::GsnClient::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_baseframework_GsnClient_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        fr::GsnClient* ret = fr::GsnClient::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<fr::GsnClient>(cx, (fr::GsnClient*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_baseframework_GsnClient_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        fr::GsnClient* ret = fr::GsnClient::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<fr::GsnClient>(cx, (fr::GsnClient*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_baseframework_GsnClient_getInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_baseframework_GsnClient_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    fr::GsnClient* cobj = new (std::nothrow) fr::GsnClient();
    TypeTest<fr::GsnClient> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "fr::GsnClient");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_fr_GsnClient_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GsnClient)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        fr::GsnClient *nobj = static_cast<fr::GsnClient *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}
void js_register_cocos2dx_baseframework_GsnClient(JSContext *cx, JS::HandleObject global) {
    jsb_fr_GsnClient_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_fr_GsnClient_class->name = "GsnClient";
    jsb_fr_GsnClient_class->addProperty = JS_PropertyStub;
    jsb_fr_GsnClient_class->delProperty = JS_DeletePropertyStub;
    jsb_fr_GsnClient_class->getProperty = JS_PropertyStub;
    jsb_fr_GsnClient_class->setProperty = JS_StrictPropertyStub;
    jsb_fr_GsnClient_class->enumerate = JS_EnumerateStub;
    jsb_fr_GsnClient_class->resolve = JS_ResolveStub;
    jsb_fr_GsnClient_class->convert = JS_ConvertStub;
    jsb_fr_GsnClient_class->finalize = js_fr_GsnClient_finalize;
    jsb_fr_GsnClient_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("onSubThreadStarted", js_cocos2dx_baseframework_GsnClient_onSubThreadStarted, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onSubThreadEnded", js_cocos2dx_baseframework_GsnClient_onSubThreadEnded, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeoutForRead", js_cocos2dx_baseframework_GsnClient_setTimeoutForRead, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("disconnect", js_cocos2dx_baseframework_GsnClient_disconnect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setReceiveDataListener", js_cocos2dx_baseframework_GsnClient_setReceiveDataListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDoConnection", js_cocos2dx_baseframework_GsnClient_isDoConnection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initThread", js_cocos2dx_baseframework_GsnClient_initThread, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeoutForConnect", js_cocos2dx_baseframework_GsnClient_setTimeoutForConnect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createSocket", js_cocos2dx_baseframework_GsnClient_createSocket, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onSubThreadLoop", js_cocos2dx_baseframework_GsnClient_onSubThreadLoop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeoutForRead", js_cocos2dx_baseframework_GsnClient_getTimeoutForRead, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFinishConnectListener", js_cocos2dx_baseframework_GsnClient_setFinishConnectListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onUIThreadReceiveMessage", js_cocos2dx_baseframework_GsnClient_onUIThreadReceiveMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDisconnectListener", js_cocos2dx_baseframework_GsnClient_setDisconnectListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setListener", js_cocos2dx_baseframework_GsnClient_setListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeoutForConnect", js_cocos2dx_baseframework_GsnClient_getTimeoutForConnect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("connect", js_cocos2dx_baseframework_GsnClient_connect, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reconnect", js_cocos2dx_baseframework_GsnClient_reconnect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearQueue", js_cocos2dx_baseframework_GsnClient_clearQueue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("send", js_cocos2dx_baseframework_GsnClient_send, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_baseframework_GsnClient_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_cocos2dx_baseframework_GsnClient_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_baseframework_GsnClient_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_fr_GsnClient_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_fr_GsnClient_class,
        js_cocos2dx_baseframework_GsnClient_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GsnClient", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<fr::GsnClient> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_fr_GsnClient_class;
        p->proto = jsb_fr_GsnClient_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_fr_NativeService_class;
JSObject *jsb_fr_NativeService_prototype;

bool js_cocos2dx_baseframework_NativeService_getFolderUpdateAssets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = fr::NativeService::getFolderUpdateAssets();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_baseframework_NativeService_getFolderUpdateAssets : wrong number of arguments");
    return false;
}

bool js_cocos2dx_baseframework_NativeService_applicationDidFinishLaunching(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        fr::NativeService::applicationDidFinishLaunching();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_baseframework_NativeService_applicationDidFinishLaunching : wrong number of arguments");
    return false;
}


void js_fr_NativeService_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (NativeService)", obj);
}
void js_register_cocos2dx_baseframework_NativeService(JSContext *cx, JS::HandleObject global) {
    jsb_fr_NativeService_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_fr_NativeService_class->name = "NativeService";
    jsb_fr_NativeService_class->addProperty = JS_PropertyStub;
    jsb_fr_NativeService_class->delProperty = JS_DeletePropertyStub;
    jsb_fr_NativeService_class->getProperty = JS_PropertyStub;
    jsb_fr_NativeService_class->setProperty = JS_StrictPropertyStub;
    jsb_fr_NativeService_class->enumerate = JS_EnumerateStub;
    jsb_fr_NativeService_class->resolve = JS_ResolveStub;
    jsb_fr_NativeService_class->convert = JS_ConvertStub;
    jsb_fr_NativeService_class->finalize = js_fr_NativeService_finalize;
    jsb_fr_NativeService_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getFolderUpdateAssets", js_cocos2dx_baseframework_NativeService_getFolderUpdateAssets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applicationDidFinishLaunching", js_cocos2dx_baseframework_NativeService_applicationDidFinishLaunching, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_fr_NativeService_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_fr_NativeService_class,
        dummy_constructor<fr::NativeService>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NativeService", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<fr::NativeService> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_fr_NativeService_class;
        p->proto = jsb_fr_NativeService_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_baseframework(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "fr", &ns);

    js_register_cocos2dx_baseframework_GsnClient(cx, ns);
    js_register_cocos2dx_baseframework_InPacket(cx, ns);
    js_register_cocos2dx_baseframework_NativeService(cx, ns);
    js_register_cocos2dx_baseframework_sPackage(cx, ns);
    js_register_cocos2dx_baseframework_OutPacket(cx, ns);
}

