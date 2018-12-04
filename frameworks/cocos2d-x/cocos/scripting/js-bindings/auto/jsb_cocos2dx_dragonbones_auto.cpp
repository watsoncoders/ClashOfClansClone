#include "jsb_cocos2dx_dragonbones_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "DragonBonesHeaders.h"
#include "DragonBones_binding.h"

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
JSClass  *jsb_dragonBones_DragonBonesData_class;
JSObject *jsb_dragonBones_DragonBonesData_prototype;

bool js_cocos2dx_dragonbones_DragonBonesData_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DragonBonesData* cobj = (dragonBones::DragonBonesData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DragonBonesData_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DragonBonesData_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DragonBonesData_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DragonBonesData* cobj = (dragonBones::DragonBonesData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DragonBonesData_getArmatureData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DragonBonesData_getArmatureData : Error processing arguments");
        dragonBones::ArmatureData* ret = cobj->getArmatureData(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::ArmatureData>(cx, (dragonBones::ArmatureData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DragonBonesData_getArmatureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DragonBonesData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DragonBonesData* cobj = new (std::nothrow) dragonBones::DragonBonesData();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DragonBonesData> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DragonBonesData");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_DragonBonesData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DragonBonesData)", obj);
}
void js_register_cocos2dx_dragonbones_DragonBonesData(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DragonBonesData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DragonBonesData_class->name = "DragonBonesData";
    jsb_dragonBones_DragonBonesData_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DragonBonesData_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DragonBonesData_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DragonBonesData_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DragonBonesData_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DragonBonesData_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DragonBonesData_class->convert = JS_ConvertStub;
    jsb_dragonBones_DragonBonesData_class->finalize = js_dragonBones_DragonBonesData_finalize;
    jsb_dragonBones_DragonBonesData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("dispose", js_cocos2dx_dragonbones_DragonBonesData_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureData", js_cocos2dx_dragonbones_DragonBonesData_getArmatureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_DragonBonesData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_DragonBonesData_class,
        js_cocos2dx_dragonbones_DragonBonesData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DragonBonesData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DragonBonesData> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DragonBonesData_class;
        p->proto = jsb_dragonBones_DragonBonesData_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_ITextureAtlas_class;
JSObject *jsb_dragonBones_ITextureAtlas_prototype;

bool js_cocos2dx_dragonbones_ITextureAtlas_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::ITextureAtlas* cobj = (dragonBones::ITextureAtlas *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_ITextureAtlas_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_ITextureAtlas_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_dragonBones_ITextureAtlas_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ITextureAtlas)", obj);
}
void js_register_cocos2dx_dragonbones_ITextureAtlas(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_ITextureAtlas_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_ITextureAtlas_class->name = "ITextureAtlas";
    jsb_dragonBones_ITextureAtlas_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_ITextureAtlas_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_ITextureAtlas_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_ITextureAtlas_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_ITextureAtlas_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_ITextureAtlas_class->resolve = JS_ResolveStub;
    jsb_dragonBones_ITextureAtlas_class->convert = JS_ConvertStub;
    jsb_dragonBones_ITextureAtlas_class->finalize = js_dragonBones_ITextureAtlas_finalize;
    jsb_dragonBones_ITextureAtlas_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("dispose", js_cocos2dx_dragonbones_ITextureAtlas_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_ITextureAtlas_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_ITextureAtlas_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ITextureAtlas", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::ITextureAtlas> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_ITextureAtlas_class;
        p->proto = jsb_dragonBones_ITextureAtlas_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_IAnimatable_class;
JSObject *jsb_dragonBones_IAnimatable_prototype;

bool js_cocos2dx_dragonbones_IAnimatable_advanceTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::IAnimatable* cobj = (dragonBones::IAnimatable *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_IAnimatable_advanceTime : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_IAnimatable_advanceTime : Error processing arguments");
        cobj->advanceTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_IAnimatable_advanceTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_IAnimatable_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::IAnimatable* cobj = new (std::nothrow) dragonBones::IAnimatable();
    TypeTest<dragonBones::IAnimatable> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::IAnimatable");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_IAnimatable_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (IAnimatable)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        dragonBones::IAnimatable *nobj = static_cast<dragonBones::IAnimatable *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}
void js_register_cocos2dx_dragonbones_IAnimatable(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_IAnimatable_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_IAnimatable_class->name = "IAnimatable";
    jsb_dragonBones_IAnimatable_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_IAnimatable_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_IAnimatable_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_IAnimatable_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_IAnimatable_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_IAnimatable_class->resolve = JS_ResolveStub;
    jsb_dragonBones_IAnimatable_class->convert = JS_ConvertStub;
    jsb_dragonBones_IAnimatable_class->finalize = js_dragonBones_IAnimatable_finalize;
    jsb_dragonBones_IAnimatable_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("advanceTime", js_cocos2dx_dragonbones_IAnimatable_advanceTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_IAnimatable_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_IAnimatable_class,
        js_cocos2dx_dragonbones_IAnimatable_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "IAnimatable", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::IAnimatable> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_IAnimatable_class;
        p->proto = jsb_dragonBones_IAnimatable_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_Object_class;
JSObject *jsb_dragonBones_Object_prototype;

bool js_cocos2dx_dragonbones_Object_getParent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Object* cobj = (dragonBones::Object *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Object_getParent : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Bone* ret = cobj->getParent();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Bone>(cx, (dragonBones::Bone*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Object_getParent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Object_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Object* cobj = (dragonBones::Object *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Object_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Object_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Object_getArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Object* cobj = (dragonBones::Object *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Object_getArmature : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Armature* ret = cobj->getArmature();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Armature>(cx, (dragonBones::Armature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Object_getArmature : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Object_getVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Object* cobj = (dragonBones::Object *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Object_getVisible : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getVisible();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Object_getVisible : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Object_setVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Object* cobj = (dragonBones::Object *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Object_setVisible : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Object_setVisible : Error processing arguments");
        cobj->setVisible(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Object_setVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Object_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::Object* cobj = new (std::nothrow) dragonBones::Object();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::Object> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::Object");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_Object_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Object)", obj);
}
void js_register_cocos2dx_dragonbones_Object(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_Object_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_Object_class->name = "Object";
    jsb_dragonBones_Object_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_Object_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_Object_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_Object_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_Object_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_Object_class->resolve = JS_ResolveStub;
    jsb_dragonBones_Object_class->convert = JS_ConvertStub;
    jsb_dragonBones_Object_class->finalize = js_dragonBones_Object_finalize;
    jsb_dragonBones_Object_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getParent", js_cocos2dx_dragonbones_Object_getParent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispose", js_cocos2dx_dragonbones_Object_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmature", js_cocos2dx_dragonbones_Object_getArmature, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVisible", js_cocos2dx_dragonbones_Object_getVisible, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVisible", js_cocos2dx_dragonbones_Object_setVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_Object_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_Object_class,
        js_cocos2dx_dragonbones_Object_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Object", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::Object> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_Object_class;
        p->proto = jsb_dragonBones_Object_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_AnimationState_class;
JSObject *jsb_dragonBones_AnimationState_prototype;

bool js_cocos2dx_dragonbones_AnimationState_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setCurrentTime : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setCurrentTime : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setCurrentTime(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_setTimeScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setTimeScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setTimeScale : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setTimeScale(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setTimeScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_setAdditiveBlending(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setAdditiveBlending : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setAdditiveBlending : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setAdditiveBlending(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setAdditiveBlending : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getClip(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getClip : Invalid Native Object");
    if (argc == 0) {
        const dragonBones::AnimationData* ret = cobj->getClip();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationData>(cx, (dragonBones::AnimationData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getClip : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_setPlayTimes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setPlayTimes : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setPlayTimes : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setPlayTimes(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setPlayTimes : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_removeMixingTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_removeMixingTransform : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_removeMixingTransform : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->removeMixingTransform(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_removeMixingTransform : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->removeMixingTransform(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_removeMixingTransform : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getGroup : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getGroup();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getGroup : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getCurrentPlayTimes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getCurrentPlayTimes : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCurrentPlayTimes();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getCurrentPlayTimes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_removeAllMixingTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_removeAllMixingTransform : Invalid Native Object");
    if (argc == 0) {
        dragonBones::AnimationState* ret = cobj->removeAllMixingTransform();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_removeAllMixingTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_addMixingTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_addMixingTransform : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_addMixingTransform : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->addMixingTransform(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_addMixingTransform : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->addMixingTransform(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_addMixingTransform : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getCurrentTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCurrentTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setAutoFadeOut(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        bool arg0;
        double arg1;
        arg0 = JS::ToBoolean(args.get(0));
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setAutoFadeOut(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getTotalTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getTotalTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTotalTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getTotalTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getLayer : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getLayer();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getLayer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getPlayTimes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getPlayTimes : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getPlayTimes();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getPlayTimes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_play : Invalid Native Object");
    if (argc == 0) {
        dragonBones::AnimationState* ret = cobj->play();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_play : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_fadeOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_fadeOut : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_fadeOut : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->fadeOut(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_fadeOut : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_stop : Invalid Native Object");
    if (argc == 0) {
        dragonBones::AnimationState* ret = cobj->stop();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getCurrentWeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getCurrentWeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCurrentWeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getCurrentWeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getIsComplete(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getIsComplete : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsComplete();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getIsComplete : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getTimeScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getTimeScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTimeScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getTimeScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_setFrameTween(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setFrameTween : Invalid Native Object");
    if (argc == 2) {
        bool arg0;
        bool arg1;
        arg0 = JS::ToBoolean(args.get(0));
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setFrameTween : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setFrameTween(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setFrameTween : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_setWeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_setWeight : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_setWeight : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->setWeight(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_setWeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getMixingTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getMixingTransform : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_AnimationState_getMixingTransform : Error processing arguments");
        bool ret = cobj->getMixingTransform(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getMixingTransform : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_getIsPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::AnimationState* cobj = (dragonBones::AnimationState *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_AnimationState_getIsPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsPlaying();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_AnimationState_getIsPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_AnimationState_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::AnimationState* cobj = new (std::nothrow) dragonBones::AnimationState();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::AnimationState> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::AnimationState");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_AnimationState_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AnimationState)", obj);
}
void js_register_cocos2dx_dragonbones_AnimationState(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_AnimationState_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_AnimationState_class->name = "AnimationState";
    jsb_dragonBones_AnimationState_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_AnimationState_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_AnimationState_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_AnimationState_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_AnimationState_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_AnimationState_class->resolve = JS_ResolveStub;
    jsb_dragonBones_AnimationState_class->convert = JS_ConvertStub;
    jsb_dragonBones_AnimationState_class->finalize = js_dragonBones_AnimationState_finalize;
    jsb_dragonBones_AnimationState_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setCurrentTime", js_cocos2dx_dragonbones_AnimationState_setCurrentTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeScale", js_cocos2dx_dragonbones_AnimationState_setTimeScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAdditiveBlending", js_cocos2dx_dragonbones_AnimationState_setAdditiveBlending, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getClip", js_cocos2dx_dragonbones_AnimationState_getClip, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlayTimes", js_cocos2dx_dragonbones_AnimationState_setPlayTimes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeMixingTransform", js_cocos2dx_dragonbones_AnimationState_removeMixingTransform, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGroup", js_cocos2dx_dragonbones_AnimationState_getGroup, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentPlayTimes", js_cocos2dx_dragonbones_AnimationState_getCurrentPlayTimes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllMixingTransform", js_cocos2dx_dragonbones_AnimationState_removeAllMixingTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addMixingTransform", js_cocos2dx_dragonbones_AnimationState_addMixingTransform, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTime", js_cocos2dx_dragonbones_AnimationState_getCurrentTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAutoFadeOut", js_cocos2dx_dragonbones_AnimationState_setAutoFadeOut, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTotalTime", js_cocos2dx_dragonbones_AnimationState_getTotalTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLayer", js_cocos2dx_dragonbones_AnimationState_getLayer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlayTimes", js_cocos2dx_dragonbones_AnimationState_getPlayTimes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_dragonbones_AnimationState_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("fadeOut", js_cocos2dx_dragonbones_AnimationState_fadeOut, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_dragonbones_AnimationState_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentWeight", js_cocos2dx_dragonbones_AnimationState_getCurrentWeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsComplete", js_cocos2dx_dragonbones_AnimationState_getIsComplete, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeScale", js_cocos2dx_dragonbones_AnimationState_getTimeScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFrameTween", js_cocos2dx_dragonbones_AnimationState_setFrameTween, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setWeight", js_cocos2dx_dragonbones_AnimationState_setWeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMixingTransform", js_cocos2dx_dragonbones_AnimationState_getMixingTransform, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsPlaying", js_cocos2dx_dragonbones_AnimationState_getIsPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_AnimationState_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_AnimationState_class,
        js_cocos2dx_dragonbones_AnimationState_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AnimationState", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::AnimationState> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_AnimationState_class;
        p->proto = jsb_dragonBones_AnimationState_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_Animation_class;
JSObject *jsb_dragonBones_Animation_prototype;

bool js_cocos2dx_dragonbones_Animation_getAnimationList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getAnimationList : Invalid Native Object");
    if (argc == 0) {
        const std::vector<std::string>& ret = cobj->getAnimationList();
        jsval jsret = JSVAL_NULL;
        jsret = std_vector_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getAnimationList : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_setTimeScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_setTimeScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_setTimeScale : Error processing arguments");
        cobj->setTimeScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_setTimeScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_play : Invalid Native Object");
    if (argc == 0) {
        cobj->play();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_play : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_hasAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_hasAnimation : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_hasAnimation : Error processing arguments");
        bool ret = cobj->hasAnimation(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_hasAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_getLastAnimationState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getLastAnimationState : Invalid Native Object");
    if (argc == 0) {
        dragonBones::AnimationState* ret = cobj->getLastAnimationState();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getLastAnimationState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        double arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 5) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        int arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2, arg3, arg4);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 6) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        int arg4;
        std::string arg5;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        ok &= jsval_to_std_string(cx, args.get(5), &arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2, arg3, arg4, arg5);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 7) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        int arg4;
        std::string arg5;
        dragonBones::Animation::AnimationFadeOutMode arg6;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        ok &= jsval_to_std_string(cx, args.get(5), &arg5);
        ok &= jsval_to_int32(cx, args.get(6), (int32_t *)&arg6);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 8) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        int arg4;
        std::string arg5;
        dragonBones::Animation::AnimationFadeOutMode arg6;
        bool arg7;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        ok &= jsval_to_std_string(cx, args.get(5), &arg5);
        ok &= jsval_to_int32(cx, args.get(6), (int32_t *)&arg6);
        arg7 = JS::ToBoolean(args.get(7));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 9) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        int arg4;
        std::string arg5;
        dragonBones::Animation::AnimationFadeOutMode arg6;
        bool arg7;
        bool arg8;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        ok &= jsval_to_std_string(cx, args.get(5), &arg5);
        ok &= jsval_to_int32(cx, args.get(6), (int32_t *)&arg6);
        arg7 = JS::ToBoolean(args.get(7));
        arg8 = JS::ToBoolean(args.get(8));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndPlay(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_gotoAndPlay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getState : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_getState : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->getState(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_getState : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->getState(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_getIsComplete(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getIsComplete : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsComplete();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getIsComplete : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_advanceTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_advanceTime : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_advanceTime : Error processing arguments");
        cobj->advanceTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_advanceTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_getCurrentAnimationName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getCurrentAnimationName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getCurrentAnimationName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getCurrentAnimationName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_getIsPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getIsPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsPlaying();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getIsPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_gotoAndStop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        double arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 5) {
        std::string arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1, arg2, arg3, arg4);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 6) {
        std::string arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        int arg5;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1, arg2, arg3, arg4, arg5);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 7) {
        std::string arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        int arg5;
        std::string arg6;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
        ok &= jsval_to_std_string(cx, args.get(6), &arg6);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 8) {
        std::string arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        int arg5;
        std::string arg6;
        dragonBones::Animation::AnimationFadeOutMode arg7;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
        ok &= jsval_to_std_string(cx, args.get(6), &arg6);
        ok &= jsval_to_int32(cx, args.get(7), (int32_t *)&arg7);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Animation_gotoAndStop : Error processing arguments");
        dragonBones::AnimationState* ret = cobj->gotoAndStop(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::AnimationState>(cx, (dragonBones::AnimationState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_gotoAndStop : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_getTimeScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Animation* cobj = (dragonBones::Animation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Animation_getTimeScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTimeScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Animation_getTimeScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Animation_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::Animation* cobj = new (std::nothrow) dragonBones::Animation();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::Animation> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::Animation");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_Animation_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Animation)", obj);
}
void js_register_cocos2dx_dragonbones_Animation(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_Animation_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_Animation_class->name = "Animation";
    jsb_dragonBones_Animation_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_Animation_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_Animation_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_Animation_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_Animation_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_Animation_class->resolve = JS_ResolveStub;
    jsb_dragonBones_Animation_class->convert = JS_ConvertStub;
    jsb_dragonBones_Animation_class->finalize = js_dragonBones_Animation_finalize;
    jsb_dragonBones_Animation_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAnimationList", js_cocos2dx_dragonbones_Animation_getAnimationList, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeScale", js_cocos2dx_dragonbones_Animation_setTimeScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_dragonbones_Animation_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_cocos2dx_dragonbones_Animation_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispose", js_cocos2dx_dragonbones_Animation_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_dragonbones_Animation_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasAnimation", js_cocos2dx_dragonbones_Animation_hasAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLastAnimationState", js_cocos2dx_dragonbones_Animation_getLastAnimationState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPlay", js_cocos2dx_dragonbones_Animation_gotoAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_cocos2dx_dragonbones_Animation_getState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsComplete", js_cocos2dx_dragonbones_Animation_getIsComplete, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("advanceTime", js_cocos2dx_dragonbones_Animation_advanceTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentAnimationName", js_cocos2dx_dragonbones_Animation_getCurrentAnimationName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsPlaying", js_cocos2dx_dragonbones_Animation_getIsPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndStop", js_cocos2dx_dragonbones_Animation_gotoAndStop, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeScale", js_cocos2dx_dragonbones_Animation_getTimeScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_Animation_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_Animation_class,
        js_cocos2dx_dragonbones_Animation_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Animation", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::Animation> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_Animation_class;
        p->proto = jsb_dragonBones_Animation_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_Armature_class;
JSObject *jsb_dragonBones_Armature_prototype;

bool js_cocos2dx_dragonbones_Armature_getBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getBone : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_getBone : Error processing arguments");
        dragonBones::Bone* ret = cobj->getBone(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Bone>(cx, (dragonBones::Bone*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getSlot : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_getSlot : Error processing arguments");
        dragonBones::Slot* ret = cobj->getSlot(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Slot>(cx, (dragonBones::Slot*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getSlot : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_setInheritAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_setInheritAnimation : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_setInheritAnimation : Error processing arguments");
        cobj->setInheritAnimation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_setInheritAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_replaceSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_replaceSlot : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        dragonBones::Slot* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (dragonBones::Slot*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_replaceSlot : Error processing arguments");
        cobj->replaceSlot(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_replaceSlot : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_removeBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::Armature* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_removeBone : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            dragonBones::Bone* ret = cobj->removeBone(arg0);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Bone>(cx, (dragonBones::Bone*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            dragonBones::Bone* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (dragonBones::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->removeBone(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_removeBone : wrong number of arguments");
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getDisplay : Invalid Native Object");
    if (argc == 0) {
        void* ret = cobj->getDisplay();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_addSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_addSlot : Invalid Native Object");
    if (argc == 2) {
        dragonBones::Slot* arg0;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::Slot*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_addSlot : Error processing arguments");
        cobj->addSlot(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_addSlot : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_invalidUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::Armature* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_invalidUpdate : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->invalidUpdate(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->invalidUpdate();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_invalidUpdate : wrong number of arguments");
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getBoneByDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getBoneByDisplay : Invalid Native Object");
    if (argc == 1) {
        const void* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_getBoneByDisplay : Error processing arguments");
        dragonBones::Bone* ret = cobj->getBoneByDisplay(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Bone>(cx, (dragonBones::Bone*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getBoneByDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_removeSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::Armature* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_removeSlot : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            dragonBones::Slot* ret = cobj->removeSlot(arg0);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Slot>(cx, (dragonBones::Slot*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            dragonBones::Slot* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (dragonBones::Slot*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->removeSlot(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_removeSlot : wrong number of arguments");
    return false;
}
bool js_cocos2dx_dragonbones_Armature_isInheritAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_isInheritAnimation : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isInheritAnimation();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_isInheritAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_addBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::Armature* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_addBone : Invalid Native Object");
    do {
        if (argc == 2) {
            dragonBones::Bone* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (dragonBones::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cobj->addBone(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            dragonBones::Bone* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (dragonBones::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->addBone(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_addBone : wrong number of arguments");
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getArmatureData : Invalid Native Object");
    if (argc == 0) {
        const dragonBones::ArmatureData* ret = cobj->getArmatureData();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::ArmatureData>(cx, (dragonBones::ArmatureData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getArmatureData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getAnimation : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Animation* ret = cobj->getAnimation();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Animation>(cx, (dragonBones::Animation*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_sortSlotsByZOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_sortSlotsByZOrder : Invalid Native Object");
    if (argc == 0) {
        cobj->sortSlotsByZOrder();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_sortSlotsByZOrder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getSlotByDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getSlotByDisplay : Invalid Native Object");
    if (argc == 1) {
        const void* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_getSlotByDisplay : Error processing arguments");
        dragonBones::Slot* ret = cobj->getSlotByDisplay(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Slot>(cx, (dragonBones::Slot*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getSlotByDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_getEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Armature* cobj = (dragonBones::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Armature_getEventDispatcher : Invalid Native Object");
    if (argc == 0) {
        dragonBones::IEventDispatcher* ret = cobj->getEventDispatcher();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::IEventDispatcher>(cx, (dragonBones::IEventDispatcher*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Armature_getEventDispatcher : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Armature_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::ArmatureData* arg0;
    dragonBones::Animation* arg1;
    dragonBones::IEventDispatcher* arg2;
    void* arg3;
    do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::ArmatureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
    do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (dragonBones::Animation*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
    do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (dragonBones::IEventDispatcher*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
    #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Armature_constructor : Error processing arguments");
    dragonBones::Armature* cobj = new (std::nothrow) dragonBones::Armature(arg0, arg1, arg2, arg3);
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::Armature> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::Armature");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_dragonBones_IAnimatable_prototype;

void js_dragonBones_Armature_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Armature)", obj);
}
void js_register_cocos2dx_dragonbones_Armature(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_Armature_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_Armature_class->name = "Armature";
    jsb_dragonBones_Armature_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_Armature_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_Armature_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_Armature_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_Armature_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_Armature_class->resolve = JS_ResolveStub;
    jsb_dragonBones_Armature_class->convert = JS_ConvertStub;
    jsb_dragonBones_Armature_class->finalize = js_dragonBones_Armature_finalize;
    jsb_dragonBones_Armature_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBone", js_cocos2dx_dragonbones_Armature_getBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlot", js_cocos2dx_dragonbones_Armature_getSlot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispose", js_cocos2dx_dragonbones_Armature_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInheritAnimation", js_cocos2dx_dragonbones_Armature_setInheritAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("replaceSlot", js_cocos2dx_dragonbones_Armature_replaceSlot, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeBone", js_cocos2dx_dragonbones_Armature_removeBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplay", js_cocos2dx_dragonbones_Armature_getDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addSlot", js_cocos2dx_dragonbones_Armature_addSlot, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("invalidUpdate", js_cocos2dx_dragonbones_Armature_invalidUpdate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneByDisplay", js_cocos2dx_dragonbones_Armature_getBoneByDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeSlot", js_cocos2dx_dragonbones_Armature_removeSlot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isInheritAnimation", js_cocos2dx_dragonbones_Armature_isInheritAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addBone", js_cocos2dx_dragonbones_Armature_addBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureData", js_cocos2dx_dragonbones_Armature_getArmatureData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimation", js_cocos2dx_dragonbones_Armature_getAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sortSlotsByZOrder", js_cocos2dx_dragonbones_Armature_sortSlotsByZOrder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlotByDisplay", js_cocos2dx_dragonbones_Armature_getSlotByDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEventDispatcher", js_cocos2dx_dragonbones_Armature_getEventDispatcher, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_Armature_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_dragonBones_IAnimatable_prototype),
        jsb_dragonBones_Armature_class,
        js_cocos2dx_dragonbones_Armature_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Armature", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::Armature> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_Armature_class;
        p->proto = jsb_dragonBones_Armature_prototype;
        p->parentProto = jsb_dragonBones_IAnimatable_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_Bone_class;
JSObject *jsb_dragonBones_Bone_prototype;

bool js_cocos2dx_dragonbones_Bone_addChild(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Bone* cobj = (dragonBones::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Bone_addChild : Invalid Native Object");
    if (argc == 1) {
        dragonBones::Object* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::Object*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Bone_addChild : Error processing arguments");
        cobj->addChild(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Bone_addChild : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Bone_getSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Bone* cobj = (dragonBones::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Bone_getSlot : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Slot* ret = cobj->getSlot();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Slot>(cx, (dragonBones::Slot*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Bone_getSlot : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Bone_contains(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Bone* cobj = (dragonBones::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Bone_contains : Invalid Native Object");
    if (argc == 1) {
        const dragonBones::Object* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (const dragonBones::Object*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Bone_contains : Error processing arguments");
        bool ret = cobj->contains(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Bone_contains : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Bone_removeChild(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Bone* cobj = (dragonBones::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Bone_removeChild : Invalid Native Object");
    if (argc == 1) {
        dragonBones::Object* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::Object*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_Bone_removeChild : Error processing arguments");
        cobj->removeChild(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Bone_removeChild : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_Bone_invalidUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::Bone* cobj = (dragonBones::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_Bone_invalidUpdate : Invalid Native Object");
    if (argc == 0) {
        cobj->invalidUpdate();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_Bone_invalidUpdate : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_Bone_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::Bone* cobj = new (std::nothrow) dragonBones::Bone();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::Bone> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::Bone");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_dragonBones_Object_prototype;

void js_dragonBones_Bone_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Bone)", obj);
}
void js_register_cocos2dx_dragonbones_Bone(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_Bone_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_Bone_class->name = "Bone";
    jsb_dragonBones_Bone_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_Bone_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_Bone_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_Bone_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_Bone_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_Bone_class->resolve = JS_ResolveStub;
    jsb_dragonBones_Bone_class->convert = JS_ConvertStub;
    jsb_dragonBones_Bone_class->finalize = js_dragonBones_Bone_finalize;
    jsb_dragonBones_Bone_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("addChild", js_cocos2dx_dragonbones_Bone_addChild, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlot", js_cocos2dx_dragonbones_Bone_getSlot, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("contains", js_cocos2dx_dragonbones_Bone_contains, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeChild", js_cocos2dx_dragonbones_Bone_removeChild, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("invalidUpdate", js_cocos2dx_dragonbones_Bone_invalidUpdate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_Bone_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_dragonBones_Object_prototype),
        jsb_dragonBones_Bone_class,
        js_cocos2dx_dragonbones_Bone_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Bone", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::Bone> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_Bone_class;
        p->proto = jsb_dragonBones_Bone_prototype;
        p->parentProto = jsb_dragonBones_Object_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_BaseFactory_class;
JSObject *jsb_dragonBones_BaseFactory_prototype;

bool js_cocos2dx_dragonbones_BaseFactory_buildArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::BaseFactory* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_buildArmature : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            dragonBones::Armature* ret = cobj->buildArmature(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Armature>(cx, (dragonBones::Armature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            dragonBones::Armature* ret = cobj->buildArmature(arg0);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Armature>(cx, (dragonBones::Armature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 5) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            std::string arg3;
            ok &= jsval_to_std_string(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            std::string arg4;
            ok &= jsval_to_std_string(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            dragonBones::Armature* ret = cobj->buildArmature(arg0, arg1, arg2, arg3, arg4);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Armature>(cx, (dragonBones::Armature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_buildArmature : wrong number of arguments");
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData : Error processing arguments");
        cobj->removeDragonBonesData(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData : Error processing arguments");
        cobj->removeDragonBonesData(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas : Invalid Native Object");
    if (argc == 1) {
        dragonBones::ITextureAtlas* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::ITextureAtlas*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas : Error processing arguments");
        cobj->addTextureAtlas(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        dragonBones::ITextureAtlas* arg0;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::ITextureAtlas*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas : Error processing arguments");
        cobj->addTextureAtlas(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData : Invalid Native Object");
    if (argc == 1) {
        dragonBones::DragonBonesData* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DragonBonesData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData : Error processing arguments");
        cobj->addDragonBonesData(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        dragonBones::DragonBonesData* arg0;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DragonBonesData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData : Error processing arguments");
        cobj->addDragonBonesData(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_dispose : Error processing arguments");
        cobj->dispose(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_getTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getTextureAtlas : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getTextureAtlas : Error processing arguments");
        dragonBones::ITextureAtlas* ret = cobj->getTextureAtlas(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::ITextureAtlas>(cx, (dragonBones::ITextureAtlas*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_getTextureAtlas : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay : Error processing arguments");
        void* ret = cobj->getTextureDisplay(arg0);
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay : Error processing arguments");
        void* ret = cobj->getTextureDisplay(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        const dragonBones::DisplayData* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (const dragonBones::DisplayData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay : Error processing arguments");
        void* ret = cobj->getTextureDisplay(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas : Error processing arguments");
        cobj->removeTextureAtlas(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas : Error processing arguments");
        cobj->removeTextureAtlas(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_getDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::BaseFactory* cobj = (dragonBones::BaseFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getDragonBonesData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_BaseFactory_getDragonBonesData : Error processing arguments");
        dragonBones::DragonBonesData* ret = cobj->getDragonBonesData(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DragonBonesData>(cx, (dragonBones::DragonBonesData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_BaseFactory_getDragonBonesData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_BaseFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::BaseFactory* cobj = new (std::nothrow) dragonBones::BaseFactory();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::BaseFactory> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::BaseFactory");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_BaseFactory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (BaseFactory)", obj);
}
void js_register_cocos2dx_dragonbones_BaseFactory(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_BaseFactory_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_BaseFactory_class->name = "BaseFactory";
    jsb_dragonBones_BaseFactory_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_BaseFactory_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_BaseFactory_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_BaseFactory_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_BaseFactory_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_BaseFactory_class->resolve = JS_ResolveStub;
    jsb_dragonBones_BaseFactory_class->convert = JS_ConvertStub;
    jsb_dragonBones_BaseFactory_class->finalize = js_dragonBones_BaseFactory_finalize;
    jsb_dragonBones_BaseFactory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("buildArmature", js_cocos2dx_dragonbones_BaseFactory_buildArmature, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeDragonBonesData", js_cocos2dx_dragonbones_BaseFactory_removeDragonBonesData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addTextureAtlas", js_cocos2dx_dragonbones_BaseFactory_addTextureAtlas, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDragonBonesData", js_cocos2dx_dragonbones_BaseFactory_addDragonBonesData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispose", js_cocos2dx_dragonbones_BaseFactory_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextureAtlas", js_cocos2dx_dragonbones_BaseFactory_getTextureAtlas, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextureDisplay", js_cocos2dx_dragonbones_BaseFactory_getTextureDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeTextureAtlas", js_cocos2dx_dragonbones_BaseFactory_removeTextureAtlas, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDragonBonesData", js_cocos2dx_dragonbones_BaseFactory_getDragonBonesData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_BaseFactory_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_BaseFactory_class,
        js_cocos2dx_dragonbones_BaseFactory_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "BaseFactory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::BaseFactory> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_BaseFactory_class;
        p->proto = jsb_dragonBones_BaseFactory_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCSlot_class;
JSObject *jsb_dragonBones_DBCCSlot_prototype;

bool js_cocos2dx_dragonbones_DBCCSlot_dispose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCSlot* cobj = (dragonBones::DBCCSlot *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_dispose : Invalid Native Object");
    if (argc == 0) {
        cobj->dispose();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSlot_dispose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCSlot_getGlobalPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCSlot* cobj = (dragonBones::DBCCSlot *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_getGlobalPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getGlobalPosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSlot_getGlobalPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCSlot_getCCChildArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCSlot* cobj = (dragonBones::DBCCSlot *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_getCCChildArmature : Invalid Native Object");
    if (argc == 0) {
        dragonBones::DBCCArmature* ret = cobj->getCCChildArmature();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmature>(cx, (dragonBones::DBCCArmature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSlot_getCCChildArmature : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCSlot_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCSlot* cobj = (dragonBones::DBCCSlot *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_getCCDisplay : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getCCDisplay();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSlot_getCCDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCSlot* cobj = (dragonBones::DBCCSlot *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage : Error processing arguments");
        cobj->setDisplayImage(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Node* arg0;
        bool arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage : Error processing arguments");
        cobj->setDisplayImage(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCSlot_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::SlotData* arg0;
    do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::SlotData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCSlot_constructor : Error processing arguments");
    dragonBones::DBCCSlot* cobj = new (std::nothrow) dragonBones::DBCCSlot(arg0);
    TypeTest<dragonBones::DBCCSlot> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCSlot");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_DBCCSlot_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCSlot)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        dragonBones::DBCCSlot *nobj = static_cast<dragonBones::DBCCSlot *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}
void js_register_cocos2dx_dragonbones_DBCCSlot(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCSlot_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCSlot_class->name = "DBCCSlot";
    jsb_dragonBones_DBCCSlot_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCSlot_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCSlot_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCSlot_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCSlot_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCSlot_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCSlot_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCSlot_class->finalize = js_dragonBones_DBCCSlot_finalize;
    jsb_dragonBones_DBCCSlot_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("dispose", js_cocos2dx_dragonbones_DBCCSlot_dispose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGlobalPosition", js_cocos2dx_dragonbones_DBCCSlot_getGlobalPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCChildArmature", js_cocos2dx_dragonbones_DBCCSlot_getCCChildArmature, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCDisplay", js_cocos2dx_dragonbones_DBCCSlot_getCCDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDisplayImage", js_cocos2dx_dragonbones_DBCCSlot_setDisplayImage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_DBCCSlot_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_DBCCSlot_class,
        js_cocos2dx_dragonbones_DBCCSlot_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCSlot", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCSlot> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCSlot_class;
        p->proto = jsb_dragonBones_DBCCSlot_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCArmature_class;
JSObject *jsb_dragonBones_DBCCArmature_prototype;

bool js_cocos2dx_dragonbones_DBCCArmature_getCCBoundingBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmature* cobj = (dragonBones::DBCCArmature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_getCCBoundingBox : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getCCBoundingBox();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmature_getCCBoundingBox : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmature_getCCEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmature* cobj = (dragonBones::DBCCArmature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_getCCEventDispatcher : Invalid Native Object");
    if (argc == 0) {
        cocos2d::EventDispatcher* ret = cobj->getCCEventDispatcher();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EventDispatcher>(cx, (cocos2d::EventDispatcher*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmature_getCCEventDispatcher : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmature_getArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmature* cobj = (dragonBones::DBCCArmature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_getArmatureNode : Invalid Native Object");
    if (argc == 0) {
        dragonBones::DBCCArmatureNode* ret = cobj->getArmatureNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmature_getArmatureNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmature_setArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmature* cobj = (dragonBones::DBCCArmature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_setArmatureNode : Invalid Native Object");
    if (argc == 1) {
        dragonBones::DBCCArmatureNode* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmatureNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_setArmatureNode : Error processing arguments");
        cobj->setArmatureNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmature_setArmatureNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmature_getCCSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmature* cobj = (dragonBones::DBCCArmature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_getCCSlot : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_getCCSlot : Error processing arguments");
        dragonBones::DBCCSlot* ret = cobj->getCCSlot(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCSlot>(cx, (dragonBones::DBCCSlot*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmature_getCCSlot : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmature_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmature* cobj = (dragonBones::DBCCArmature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_getCCDisplay : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getCCDisplay();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmature_getCCDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmature_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::ArmatureData* arg0;
    dragonBones::Animation* arg1;
    dragonBones::IEventDispatcher* arg2;
    cocos2d::Node* arg3;
    do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::ArmatureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
    do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (dragonBones::Animation*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
    do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (dragonBones::IEventDispatcher*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
    do {
            if (args.get(3).isNull()) { arg3 = nullptr; break; }
            if (!args.get(3).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(3).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg3 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
        } while (0);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmature_constructor : Error processing arguments");
    dragonBones::DBCCArmature* cobj = new (std::nothrow) dragonBones::DBCCArmature(arg0, arg1, arg2, arg3);
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCArmature> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCArmature");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_dragonBones_Armature_prototype;

void js_dragonBones_DBCCArmature_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCArmature)", obj);
}
void js_register_cocos2dx_dragonbones_DBCCArmature(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCArmature_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCArmature_class->name = "DBCCArmature";
    jsb_dragonBones_DBCCArmature_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmature_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCArmature_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmature_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCArmature_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCArmature_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCArmature_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCArmature_class->finalize = js_dragonBones_DBCCArmature_finalize;
    jsb_dragonBones_DBCCArmature_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getCCBoundingBox", js_cocos2dx_dragonbones_DBCCArmature_getCCBoundingBox, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCEventDispatcher", js_cocos2dx_dragonbones_DBCCArmature_getCCEventDispatcher, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureNode", js_cocos2dx_dragonbones_DBCCArmature_getArmatureNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setArmatureNode", js_cocos2dx_dragonbones_DBCCArmature_setArmatureNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCSlot", js_cocos2dx_dragonbones_DBCCArmature_getCCSlot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCDisplay", js_cocos2dx_dragonbones_DBCCArmature_getCCDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_dragonBones_DBCCArmature_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_dragonBones_Armature_prototype),
        jsb_dragonBones_DBCCArmature_class,
        js_cocos2dx_dragonbones_DBCCArmature_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCArmature", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCArmature> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCArmature_class;
        p->proto = jsb_dragonBones_DBCCArmature_prototype;
        p->parentProto = jsb_dragonBones_Armature_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCArmatureNode_class;
JSObject *jsb_dragonBones_DBCCArmatureNode_prototype;

bool js_cocos2dx_dragonbones_DBCCArmatureNode_getAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getAnimation : Invalid Native Object");
    if (argc == 0) {
        dragonBones::Animation* ret = cobj->getAnimation();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::Animation>(cx, (dragonBones::Animation*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_getAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_setBaseColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_setBaseColor : Invalid Native Object");
    if (argc == 3) {
        int arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_setBaseColor : Error processing arguments");
        cobj->setBaseColor(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_setBaseColor : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getCCEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCEventDispatcher : Invalid Native Object");
    if (argc == 0) {
        cocos2d::EventDispatcher* ret = cobj->getCCEventDispatcher();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EventDispatcher>(cx, (cocos2d::EventDispatcher*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCEventDispatcher : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_play : Invalid Native Object");
    if (argc == 0) {
        cobj->play();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_play : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getArmature : Invalid Native Object");
    if (argc == 0) {
        dragonBones::DBCCArmature* ret = cobj->getArmature();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmature>(cx, (dragonBones::DBCCArmature*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_getArmature : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay : Error processing arguments");
        cobj->gotoAndPlay(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay : Error processing arguments");
        cobj->gotoAndPlay(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        double arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay : Error processing arguments");
        cobj->gotoAndPlay(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        double arg1;
        double arg2;
        int arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay : Error processing arguments");
        cobj->gotoAndPlay(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getCCSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCSlot : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCSlot : Error processing arguments");
        dragonBones::DBCCSlot* ret = cobj->getCCSlot(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCSlot>(cx, (dragonBones::DBCCSlot*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCSlot : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getInnerBoundingBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getInnerBoundingBox : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getInnerBoundingBox();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_getInnerBoundingBox : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_setCompleteListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_setCompleteListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (dragonBones::DBCCArmatureNode *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](dragonBones::DBCCArmatureNode* larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_setCompleteListener : Error processing arguments");
        cobj->setCompleteListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_setCompleteListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_loadingDataCallBack(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_loadingDataCallBack : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_loadingDataCallBack : Error processing arguments");
        cobj->loadingDataCallBack(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_loadingDataCallBack : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_advanceTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_advanceTime : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_advanceTime : Error processing arguments");
        cobj->advanceTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_advanceTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_initWithDBCCArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_initWithDBCCArmature : Invalid Native Object");
    if (argc == 2) {
        dragonBones::DBCCArmature* arg0;
        dragonBones::WorldClock* arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (dragonBones::WorldClock*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_initWithDBCCArmature : Error processing arguments");
        bool ret = cobj->initWithDBCCArmature(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_initWithDBCCArmature : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCDisplay : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getCCDisplay();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_getCCDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCArmatureNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::DBCCArmature* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_create : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = dragonBones::DBCCArmatureNode::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCArmatureNode_createWithWorldClock(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        dragonBones::DBCCArmature* arg0;
        dragonBones::WorldClock* arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (dragonBones::WorldClock*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCArmatureNode_createWithWorldClock : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = dragonBones::DBCCArmatureNode::createWithWorldClock(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCArmatureNode_createWithWorldClock : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCArmatureNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCArmatureNode* cobj = new (std::nothrow) dragonBones::DBCCArmatureNode();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCArmatureNode> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCArmatureNode");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Node_prototype;

void js_dragonBones_DBCCArmatureNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCArmatureNode)", obj);
}
void js_register_cocos2dx_dragonbones_DBCCArmatureNode(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCArmatureNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCArmatureNode_class->name = "DBCCArmatureNode";
    jsb_dragonBones_DBCCArmatureNode_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCArmatureNode_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCArmatureNode_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCArmatureNode_class->finalize = js_dragonBones_DBCCArmatureNode_finalize;
    jsb_dragonBones_DBCCArmatureNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAnimation", js_cocos2dx_dragonbones_DBCCArmatureNode_getAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBaseColor", js_cocos2dx_dragonbones_DBCCArmatureNode_setBaseColor, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCEventDispatcher", js_cocos2dx_dragonbones_DBCCArmatureNode_getCCEventDispatcher, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_dragonbones_DBCCArmatureNode_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmature", js_cocos2dx_dragonbones_DBCCArmatureNode_getArmature, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPlay", js_cocos2dx_dragonbones_DBCCArmatureNode_gotoAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCSlot", js_cocos2dx_dragonbones_DBCCArmatureNode_getCCSlot, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInnerBoundingBox", js_cocos2dx_dragonbones_DBCCArmatureNode_getInnerBoundingBox, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCompleteListener", js_cocos2dx_dragonbones_DBCCArmatureNode_setCompleteListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadingDataCallBack", js_cocos2dx_dragonbones_DBCCArmatureNode_loadingDataCallBack, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("advanceTime", js_cocos2dx_dragonbones_DBCCArmatureNode_advanceTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDBCCArmature", js_cocos2dx_dragonbones_DBCCArmatureNode_initWithDBCCArmature, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCDisplay", js_cocos2dx_dragonbones_DBCCArmatureNode_getCCDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_dragonbones_DBCCArmatureNode_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithWorldClock", js_cocos2dx_dragonbones_DBCCArmatureNode_createWithWorldClock, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCArmatureNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_dragonBones_DBCCArmatureNode_class,
        js_cocos2dx_dragonbones_DBCCArmatureNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCArmatureNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCArmatureNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCArmatureNode_class;
        p->proto = jsb_dragonBones_DBCCArmatureNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCSprite_class;
JSObject *jsb_dragonBones_DBCCSprite_prototype;

bool js_cocos2dx_dragonbones_DBCCSprite_setColorByShader(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCSprite* cobj = (dragonBones::DBCCSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCSprite_setColorByShader : Invalid Native Object");
    if (argc == 3) {
        int arg0;
        int arg1;
        int arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCSprite_setColorByShader : Error processing arguments");
        cobj->setColorByShader(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSprite_setColorByShader : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCSprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::SpriteFrame* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCSprite_createWithSpriteFrame : Error processing arguments");
        dragonBones::DBCCSprite* ret = dragonBones::DBCCSprite::createWithSpriteFrame(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCSprite>(cx, (dragonBones::DBCCSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCSprite_createWithSpriteFrame : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCSprite* cobj = new (std::nothrow) dragonBones::DBCCSprite();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCSprite> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCSprite");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_dragonBones_DBCCSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCSprite)", obj);
}
void js_register_cocos2dx_dragonbones_DBCCSprite(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCSprite_class->name = "DBCCSprite";
    jsb_dragonBones_DBCCSprite_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCSprite_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCSprite_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCSprite_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCSprite_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCSprite_class->finalize = js_dragonBones_DBCCSprite_finalize;
    jsb_dragonBones_DBCCSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setColorByShader", js_cocos2dx_dragonbones_DBCCSprite_setColorByShader, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithSpriteFrame", js_cocos2dx_dragonbones_DBCCSprite_createWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_dragonBones_DBCCSprite_class,
        js_cocos2dx_dragonbones_DBCCSprite_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCSprite_class;
        p->proto = jsb_dragonBones_DBCCSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCFactory_class;
JSObject *jsb_dragonBones_DBCCFactory_prototype;

bool js_cocos2dx_dragonbones_DBCCFactory_buildArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::DBCCFactory* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_buildArmatureNode : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            dragonBones::DBCCArmatureNode* ret = cobj->buildArmatureNode(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            dragonBones::DBCCArmatureNode* ret = cobj->buildArmatureNode(arg0);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 5) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            std::string arg3;
            ok &= jsval_to_std_string(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            std::string arg4;
            ok &= jsval_to_std_string(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            dragonBones::DBCCArmatureNode* ret = cobj->buildArmatureNode(arg0, arg1, arg2, arg3, arg4);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_buildArmatureNode : wrong number of arguments");
    return false;
}
bool js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones : Error processing arguments");
        bool ret = cobj->hasDragonBones(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones : Error processing arguments");
        bool ret = cobj->hasDragonBones(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones : Error processing arguments");
        bool ret = cobj->hasDragonBones(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas : Error processing arguments");
        dragonBones::ITextureAtlas* ret = cobj->loadTextureAtlas(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::ITextureAtlas>(cx, (dragonBones::ITextureAtlas*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas : Error processing arguments");
        dragonBones::ITextureAtlas* ret = cobj->loadTextureAtlas(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::ITextureAtlas>(cx, (dragonBones::ITextureAtlas*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture : Invalid Native Object");
    if (argc == 0) {
        cobj->refreshAllTextureAtlasTexture();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCFactory_refreshTextureAtlasTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_refreshTextureAtlasTexture : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_refreshTextureAtlasTexture : Error processing arguments");
        cobj->refreshTextureAtlasTexture(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_refreshTextureAtlasTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCFactory* cobj = (dragonBones::DBCCFactory *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData : Error processing arguments");
        dragonBones::DragonBonesData* ret = cobj->loadDragonBonesData(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DragonBonesData>(cx, (dragonBones::DragonBonesData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData : Error processing arguments");
        dragonBones::DragonBonesData* ret = cobj->loadDragonBonesData(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DragonBonesData>(cx, (dragonBones::DragonBonesData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCFactory_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::DBCCFactory::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::DBCCFactory* ret = dragonBones::DBCCFactory::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCFactory>(cx, (dragonBones::DBCCFactory*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCFactory_getInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCFactory* cobj = new (std::nothrow) dragonBones::DBCCFactory();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCFactory> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCFactory");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_dragonBones_BaseFactory_prototype;

void js_dragonBones_DBCCFactory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCFactory)", obj);
}
void js_register_cocos2dx_dragonbones_DBCCFactory(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCFactory_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCFactory_class->name = "DBCCFactory";
    jsb_dragonBones_DBCCFactory_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCFactory_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCFactory_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCFactory_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCFactory_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCFactory_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCFactory_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCFactory_class->finalize = js_dragonBones_DBCCFactory_finalize;
    jsb_dragonBones_DBCCFactory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("buildArmatureNode", js_cocos2dx_dragonbones_DBCCFactory_buildArmatureNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasDragonBones", js_cocos2dx_dragonbones_DBCCFactory_hasDragonBones, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureAtlas", js_cocos2dx_dragonbones_DBCCFactory_loadTextureAtlas, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("refreshAllTextureAtlasTexture", js_cocos2dx_dragonbones_DBCCFactory_refreshAllTextureAtlasTexture, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("refreshTextureAtlasTexture", js_cocos2dx_dragonbones_DBCCFactory_refreshTextureAtlasTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadDragonBonesData", js_cocos2dx_dragonbones_DBCCFactory_loadDragonBonesData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_dragonbones_DBCCFactory_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_dragonbones_DBCCFactory_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCFactory_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_dragonBones_BaseFactory_prototype),
        jsb_dragonBones_DBCCFactory_class,
        js_cocos2dx_dragonbones_DBCCFactory_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCFactory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCFactory> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCFactory_class;
        p->proto = jsb_dragonBones_DBCCFactory_prototype;
        p->parentProto = jsb_dragonBones_BaseFactory_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_dragonBones_DBCCHelper_class;
JSObject *jsb_dragonBones_DBCCHelper_prototype;

bool js_cocos2dx_dragonbones_DBCCHelper_onRemovedArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCHelper* cobj = (dragonBones::DBCCHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCHelper_onRemovedArmatureNode : Invalid Native Object");
    if (argc == 1) {
        dragonBones::DBCCArmatureNode* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmatureNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCHelper_onRemovedArmatureNode : Error processing arguments");
        cobj->onRemovedArmatureNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCHelper_onRemovedArmatureNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCHelper* cobj = (dragonBones::DBCCHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = cobj->buildAsyncArmatureNode(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = cobj->buildAsyncArmatureNode(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_dragonbones_DBCCHelper_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::DBCCHelper::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCHelper_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCHelper_getImagePathFromAtlasPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_dragonbones_DBCCHelper_getImagePathFromAtlasPath : Error processing arguments");
        std::string ret = dragonBones::DBCCHelper::getImagePathFromAtlasPath(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCHelper_getImagePathFromAtlasPath : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCHelper_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        dragonBones::DBCCHelper* ret = dragonBones::DBCCHelper::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCHelper>(cx, (dragonBones::DBCCHelper*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_dragonbones_DBCCHelper_getInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_dragonbones_DBCCHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCHelper* cobj = new (std::nothrow) dragonBones::DBCCHelper();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<dragonBones::DBCCHelper> t;
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
    AddNamedObjectRoot(cx, &p->obj, "dragonBones::DBCCHelper");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_dragonBones_DBCCHelper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCHelper)", obj);
}
void js_register_cocos2dx_dragonbones_DBCCHelper(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCHelper_class->name = "DBCCHelper";
    jsb_dragonBones_DBCCHelper_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCHelper_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCHelper_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCHelper_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCHelper_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCHelper_class->finalize = js_dragonBones_DBCCHelper_finalize;
    jsb_dragonBones_DBCCHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("onRemovedArmatureNode", js_cocos2dx_dragonbones_DBCCHelper_onRemovedArmatureNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("buildAsyncArmatureNode", js_cocos2dx_dragonbones_DBCCHelper_buildAsyncArmatureNode, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_dragonbones_DBCCHelper_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getImagePathFromAtlasPath", js_cocos2dx_dragonbones_DBCCHelper_getImagePathFromAtlasPath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_dragonbones_DBCCHelper_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_dragonBones_DBCCHelper_class,
        js_cocos2dx_dragonbones_DBCCHelper_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCHelper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCHelper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCHelper_class;
        p->proto = jsb_dragonBones_DBCCHelper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_dragonbones(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "db", &ns);

    js_register_cocos2dx_dragonbones_DBCCSprite(cx, ns);
    js_register_cocos2dx_dragonbones_BaseFactory(cx, ns);
    js_register_cocos2dx_dragonbones_ITextureAtlas(cx, ns);
    js_register_cocos2dx_dragonbones_IAnimatable(cx, ns);
    js_register_cocos2dx_dragonbones_Object(cx, ns);
    js_register_cocos2dx_dragonbones_AnimationState(cx, ns);
    js_register_cocos2dx_dragonbones_DBCCFactory(cx, ns);
    js_register_cocos2dx_dragonbones_DBCCHelper(cx, ns);
    js_register_cocos2dx_dragonbones_Animation(cx, ns);
    js_register_cocos2dx_dragonbones_DBCCSlot(cx, ns);
    js_register_cocos2dx_dragonbones_DragonBonesData(cx, ns);
    js_register_cocos2dx_dragonbones_DBCCArmatureNode(cx, ns);
    js_register_cocos2dx_dragonbones_Armature(cx, ns);
    js_register_cocos2dx_dragonbones_Bone(cx, ns);
    js_register_cocos2dx_dragonbones_DBCCArmature(cx, ns);
}

