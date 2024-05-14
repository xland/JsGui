#include "Win.h"
#include "Util.h"
#include <vector>

namespace Win {
static JSValue ctroInstance;
static JSValue protoInstance;
static JSClassID id{ 0 };
std::vector<size_t> winIds;
static JSClassDef js_win_class = {
	.class_name{"Win"}, // 类名
	.finalizer{[](JSRuntime* rt, JSValue val) {
		auto winId = *(size_t*)JS_GetOpaque(val, id);

		//todo js_free_rt已经帮我释放了资源，所以不能再delete win了
		//如果win持有其它指针，得在这里写delete释放
		//js_free_rt(rt, win);
		//JS_FreeValue(JsEnv::GetContext(), val);
	}}
};


JSValue Constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, id);
	auto winId = webui_new_window();
	webui_set_position(winId, 300, 300);
	webui_show(winId, "<html><script src=\"webui.js\"></script> Hello World from C++! </html>");
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
	//JS_SetPropertyFunctionList(ctx, protoInstance, funcs, countof(funcs));
	ctroInstance = JS_NewCFunction2(ctx, &Win::Constructor, js_win_class.class_name, 0, JS_CFUNC_constructor,0);	
	JS_SetConstructor(ctx, ctroInstance, protoInstance);
	JS_SetClassProto(ctx, id, protoInstance);

	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, js_win_class.class_name, ctroInstance);
	JS_FreeValue(ctx, global);
}
}
