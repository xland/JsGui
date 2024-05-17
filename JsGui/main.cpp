
extern "C" {
#include <webui.h>
}


//#include "JsEnv.h"


void my_function(webui_event_t* e) {
    webui_close(e->window);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    //auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    //if (result != S_OK) {
    //    return 0;
    //}
    
    auto winId = webui_new_window();
    //webui_set_position(winId, 300, 300);
    webui_show_browser(winId, "<html><script src=\"webui.js\"></script> Hello World from C++! <button id=\"MyID\">Hello</button> </html>", webui_browsers::Edge);
    //webui_run(winId, "alert('Fast!');");
    webui_bind(winId, "MyID", my_function);


    webui_set_timeout(3000);
    webui_wait();



    //JsEnv::Init();    
    //webui::wait();
    //JsEnv::Dispose();
    //CoUninitialize();
    return 0;
}