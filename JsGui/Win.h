#pragma once
#include <webui.hpp>
extern "C" {
#include <quickjs.h>
}
namespace Win
{
	JSValue Constructor(JSContext* ctx, JSValueConst arg, int argc, JSValueConst* argv);
	void Reg(JSContext* ctx);
	JSValue Close(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv);
	JSValue SetRootFolder(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv);
	JSValue Show(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv);
	JSValue SetSize(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv);
};

