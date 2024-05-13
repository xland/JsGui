#pragma once
extern "C" {
#include <quickjs.h>
}
class Win
{
public:
	~Win();
	static JSValue Constructor(JSContext* ctx, JSValueConst arg, int argc, JSValueConst* argv);
	static void Reg(JSContext* ctx);
	static void Dispose(JSContext* ctx);
private:
	Win();
};

