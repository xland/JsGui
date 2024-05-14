#include <webui.hpp>
#include "JsEnv.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    //auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    //if (result != S_OK) {
    //    return 0;
    //}
    
    JsEnv::Init();    
    webui::wait();
    JsEnv::Dispose();
    //CoUninitialize();
    return 0;
}