#include "JsEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "Win.h"
#include "Util.h"


static JsEnv* env;
JSContext* ctx;
JSRuntime* rt;

static JSValue js_console_log(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    for (int i = 0; i < argc; i++) {
        const char* str = JS_ToCString(ctx, argv[i]);
        if (str) {
            printf("%s", str);
            JS_FreeCString(ctx, str);
        }
    }
    printf("\n");
    return MakeVal(0, JS_TAG_UNDEFINED);
}

static JSContext* JS_NewCustomContext(JSRuntime* rt)
{
    JSContext* ctx = JS_NewContext(rt);
    if (!ctx)
        return NULL;
    return ctx;
}

JsEnv::JsEnv()
{
    rt = JS_NewRuntime();
    if (!rt) {
        fprintf(stderr, "Failed to create runtime\n");
        return;
    }
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(rt);
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    ctx = JS_NewCustomContext(rt);
    if (!ctx) {
        fprintf(stderr, "Failed to create context\n");
        JS_FreeRuntime(rt);
        return;
    }

    js_init_module_std(ctx, "std");
    js_std_add_helpers(ctx, 0, nullptr);
    js_init_module_os(ctx, "os");


    JSValue global_obj = JS_GetGlobalObject(ctx);
    JSValue consoleObj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, consoleObj, "log", JS_NewCFunction(ctx, js_console_log, "log", 1));
    JS_SetPropertyStr(ctx, global_obj, "console", consoleObj);
    JS_FreeValue(ctx, global_obj);

    Win::Reg(ctx);
    LoadIndexJs(ctx);
    js_std_loop(ctx);
}

void JsEnv::Dispose()
{
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    delete env;
}

JsEnv::~JsEnv()
{  
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

void JsEnv::LoadIndexJs(JSContext* ctx)
{
    uint8_t* buf;
    size_t buf_len;
    buf = js_load_file(ctx, &buf_len, "main.js");
    if (!buf) {
        int a = 1;
        //load js error
    }
    JSValue val;
    char* buf1 = reinterpret_cast<char*>(const_cast<uint8_t*>(buf));
    val = JS_Eval(ctx, buf1, buf_len, "main.js", JS_EVAL_TYPE_MODULE);
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        return;
    }
    JS_FreeValue(ctx, val);
    js_free(ctx, buf);
}

int JsEnv::RegModel(JSContext* ctx, JSModuleDef* m)
{
    Win::Reg(ctx);
    return 0;
}