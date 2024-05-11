#include "JsEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fstream>


static JsEnv* env;
JSContext* ctx;
JSRuntime* rt;

static JSValue js_console_log(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    int i;
    for (i = 0; i < argc; i++) {
        const char* str;
        str = JS_ToCString(ctx, argv[i]);
        if (str) {
            printf("%s", str);
            JS_FreeCString(ctx, str);
        }
    }
    printf("\n");
    return JS_NewInt32(ctx, 123);;
}



JsEnv::JsEnv()
{
    // 初始化JS运行时和上下文
    JSRuntime* rt;
    JSContext* ctx;

    rt = JS_NewRuntime();
    if (!rt) {
        fprintf(stderr, "Failed to create runtime\n");
        return;
    }
    ctx = JS_NewContext(rt);
    if (!ctx) {
        fprintf(stderr, "Failed to create context\n");
        JS_FreeRuntime(rt);
        return;
    }

    // 执行JavaScript代码

    JSValue global_obj, console_obj;
    global_obj = JS_GetGlobalObject(ctx);
    console_obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_console_log, "log", 1));
    JS_SetPropertyStr(ctx, global_obj, "console", console_obj);
    JS_FreeValue(ctx, global_obj);

    const char* script = "console.log(11);";
    JSValue ret = JS_Eval(ctx, script, strlen(script), "<input>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(ret)) {
        fprintf(stderr, "Error evaluating script\n");
    }

    // 清理
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);






    rt = JS_NewRuntime();
    if (!rt) {
        int a = 1;
    }
    ctx = JS_NewContext(rt);
    if (!ctx) {
        //cannot allocate JS context
        int a = 1;
    }
    //JSModuleDef* m = JS_NewCModule(ctx, "sg", &JsEnv::RegModel);
    //if (!m)
    //{
    //    int a = 1;
    //}
    //auto ret = JS_AddModuleExport(ctx, m, "Window");
    LoadIndexJs(ctx);
}

JsEnv::~JsEnv()
{  
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
}

void JsEnv::Init()
{
    env = new JsEnv();
}

JsEnv* JsEnv::Get()
{
    return env;
}


JSContext* JsEnv::GetContext()
{
    return ctx;
}

int JsEnv::RegModel(JSContext* ctx, JSModuleDef* m)
{
    //Window::Register(ctx, m);
    return 0;
}

void JsEnv::LoadIndexJs(JSContext* ctx)
{
    std::ifstream file("main.js");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    JSValue val = JS_Eval(ctx, content.data(), content.length(), "index.js", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(val)) {
        int a = 1;
    }
    JS_FreeValue(ctx, val);
}