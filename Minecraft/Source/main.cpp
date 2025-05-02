#include "Statics/Globals.h"
Application* GApp;

#ifndef MINECRAFT_PLATFORM_WINDOWS
    #error Platform not supported
#endif

int main()
{
    UDebugger::Log("Hello World!");

    GApp = new Application;
    return GApp->Setup();
}
