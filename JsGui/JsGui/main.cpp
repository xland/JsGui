#include "webui.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    //auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    //if (result != S_OK) {
    //    return 0;
    //}
    webui::window myWindow;
    myWindow.show("<html><script src=\"webui.js\"></script> Hello World from C++! </html>");
    webui::wait();
    //CoUninitialize();
    return 0;
}