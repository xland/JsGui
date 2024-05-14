#pragma once

extern "C" {
#include <quickjs.h>
#include "quickjs-libc.h"
}

constexpr JSCFunctionListEntry MakeJsFunc(const char* name, uint8_t length, JSCFunction* func) {
    return JSCFunctionListEntry{
        .name{name},
        .prop_flags{JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE},
        .def_type{JS_DEF_CFUNC},
        .magic{0},
        .u = {.func = {0, JS_CFUNC_generic, {.generic = func}}}
    };
};
