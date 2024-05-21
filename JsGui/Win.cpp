#include "Win.h"
#include "Util.h"
#include <vector>
#include "cutils.h"
#include "JsEnv.h"

namespace Win {
static JSValue ctroInstance;
static JSValue protoInstance;
static JSClassID id{ 0 };
std::vector<size_t> winIds;
static JSClassDef js_win_class = {
	.class_name{"Win"}, // 类名
	.finalizer{[](JSRuntime* rt, JSValue val) {
		auto winId = *(size_t*)JS_GetOpaque(val, id);
		//webui_destroy(winId);
		//winIds.erase(std::remove(winIds.begin(), winIds.end(), winId), winIds.end());
		//todo js_free_rt已经帮我释放了资源，所以不能再delete win了
		//如果win持有其它指针，得在这里写delete释放
		//js_free_rt(rt, win);
		//JS_FreeValue(JsEnv::GetContext(), val);
	}}
};

JSValue Close(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	webui_close(winId);
	winIds.erase(std::remove(winIds.begin(), winIds.end(), winId), winIds.end());
	return JS_NewBool(ctx, true);
}

JSValue SetRootFolder(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		webui_set_root_folder(winId, str);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue Show(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		webui_show(winId, str);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue SetSize(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	unsigned int w, h;
	if (JS_ToUint32(ctx, &w, argv[0])){
		return MakeVal(0, JS_TAG_EXCEPTION);
	}
	if (JS_ToUint32(ctx, &h, argv[1])) {
		return MakeVal(0, JS_TAG_EXCEPTION);
	}
	webui_set_size(winId, w,h);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue Constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, id);
	auto winId = webui_new_window();
	winIds.push_back(winId);
	JS_SetOpaque(obj, (void*)&winIds.back());
	return obj;
}

void Reg(JSContext* ctx)
{
	auto rt = JS_GetRuntime(ctx);
	JS_NewClassID(rt,&id);
	JS_NewClass(rt, id, &js_win_class);
	protoInstance = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, protoInstance, "show", JS_NewCFunction(ctx, Show, "show", 1));
	JS_SetPropertyStr(ctx, protoInstance, "setSize", JS_NewCFunction(ctx, SetSize, "setSize", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setRootFolder", JS_NewCFunction(ctx, SetRootFolder, "setRootFolder", 1));
	JS_SetPropertyStr(ctx, protoInstance, "close", JS_NewCFunction(ctx, Close, "close", 0));
	//JS_SetPropertyFunctionList(ctx, protoInstance, funcs, countof(funcs));
	ctroInstance = JS_NewCFunction2(ctx, &Win::Constructor, js_win_class.class_name, 0, JS_CFUNC_constructor,0);	
	JS_SetConstructor(ctx, ctroInstance, protoInstance);
	JS_SetClassProto(ctx, id, protoInstance);

	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, js_win_class.class_name, ctroInstance);
	JS_FreeValue(ctx, global);
}
}
