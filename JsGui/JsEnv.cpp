#include "JsEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "Win.h"


static JsEnv* env;
JSContext* ctx;
JSRuntime* rt;
JsEnv::JsEnv()
{
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
    Win::Reg(ctx);
    //JSModuleDef* m = JS_NewCModule(ctx, "sg", &JsEnv::RegModel);
    //if (!m)
    //{
    //    return;
    //}
    //auto ret = JS_AddModuleExport(ctx, m, "Win");
    LoadIndexJs(ctx);
}

void JsEnv::Dispose()
{
    //Win::Dispose(ctx);
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
        //error
    }
    JS_FreeValue(ctx, val);
    js_free(ctx, buf);
}

int JsEnv::RegModel(JSContext* ctx, JSModuleDef* m)
{
    Win::Reg(ctx);
    return 0;
}