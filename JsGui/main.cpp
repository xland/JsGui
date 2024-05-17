
extern "C" {
#include <webui.h>
}


//#include "JsEnv.h"


void my_function(webui_event_t* e) {

    if (e->event_type == WEBUI_EVENT_CONNECTED)
        printf("Connected. \n");
    else if (e->event_type == WEBUI_EVENT_DISCONNECTED)
        printf("Disconnected. \n");
    else if (e->event_type == WEBUI_EVENT_MOUSE_CLICK)
        printf("Click. \n");
    else if (e->event_type == WEBUI_EVENT_NAVIGATION)

    // Send back a response to JavaScript
    webui_return_int(e, 123); // As integer
    webui_return_bool(e, true); // As boolean
    webui_return_string(e, "My Response"); // As string
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    //auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    //if (result != S_OK) {
    //    return 0;
    //}
    
    auto winId = webui_new_window();
    //webui_set_position(winId, 300, 300);
    webui_show(winId, "<html><script src=\"webui.js\"></script> Hello World from C++! <button id=\"MyID\">Hello</button> </html>");
    //webui_run(winId, "alert('Fast!');");
    //webui_bind(winId, "MyID", my_function);
    webui_close(winId);
    webui_destroy(winId);

    webui_set_timeout(0);
    webui_wait();


    //JsEnv::Init();    
    //webui::wait();
    //JsEnv::Dispose();
    //CoUninitialize();
    return 0;
}