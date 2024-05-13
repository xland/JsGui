#include <webui.hpp>
#include "JsEnv.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    //auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    //if (result != S_OK) {
    //    return 0;
    //}
    
    JsEnv::Init();
    webui::window myWindow;
    myWindow.set_position(900, 1000);
    myWindow.show("<html><script src=\"webui.js\"></script> Hello World from C++! </html>");
    webui::wait();
    JsEnv::Dispose();
    //CoUninitialize();
    return 0;
}