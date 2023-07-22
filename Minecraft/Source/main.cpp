#include "Statics/Globals.h"
Application* GApp;

int main()
{
    GApp = new Application;
    return GApp->Setup();
}
