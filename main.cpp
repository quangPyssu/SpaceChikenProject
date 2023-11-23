#include "App.h"

int WinMain()
{
   	App* app=new App;

    app->Run();

    delete app;

    return 0;
}
