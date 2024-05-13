#include "Win.h"
#include "JsEnv.h"


static JSValue ctroInstance;
static JSValue protoInstance;
static JSClassID id{ 0 };
static JSClassDef js_win_class = {
	.class_name{"Win"}, // 类名
	.finalizer{[](JSRuntime* rt, JSValue val) {
		Win* win = (Win*)JS_GetOpaque(val, id);
		delete win;
		//todo js_free_rt已经帮我释放了资源，所以不能再delete win了
		//如果win持有其它指针，得在这里写delete释放
		//js_free_rt(rt, win);
		//JS_FreeValue(JsEnv::GetContext(), val);
	}},
	.gc_mark{nullptr},
};

Win::Win()
{
}
Win::~Win()
{
}

JSValue Win::Constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, id);
	if (JS_IsException(obj))
	{
		return obj;
	}
	auto p = new Win();
	JS_SetOpaque(obj, p);
	return obj;
}

void Win::Reg(JSContext* ctx)
{
	auto rt = JS_GetRuntime(ctx);
	JS_NewClassID(rt,&id);
	JS_NewClass(rt, id, &js_win_class);
	protoInstance = JS_NewObject(ctx);
	ctroInstance = JS_NewCFunction2(ctx, &Win::Constructor, js_win_class.class_name, 0, JS_CFUNC_constructor,0);	
	JS_SetConstructor(ctx, ctroInstance, protoInstance);
	JS_SetClassProto(ctx, id, protoInstance);

	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, js_win_class.class_name, ctroInstance);
	JS_FreeValue(ctx, global);
}

void Win::Dispose(JSContext* ctx)
{
	JS_FreeValue(ctx, protoInstance);
	JS_FreeValue(ctx, ctroInstance);
}


