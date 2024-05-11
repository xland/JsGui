#pragma once

extern "C" {
#include <quickjs.h>
}

class JsEnv
{
public:
	static void Init();
	static JsEnv* Get();
	static JSContext* GetContext();
	static int RegModel(JSContext* ctx, JSModuleDef* m);
	~JsEnv();
	static void LoadIndexJs(JSContext* ctx);

private:
	JsEnv();
};

