#pragma once
#include <webui.hpp>
extern "C" {
#include <quickjs.h>
}
namespace Win
{
	JSValue Constructor(JSContext* ctx, JSValueConst arg, int argc, JSValueConst* argv);
	void Reg(JSContext* ctx);
};

