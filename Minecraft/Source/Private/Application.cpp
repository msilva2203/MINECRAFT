#include "Application.h"

#include "Framework/TimerManager.h"
#include "Rendering/Renderer.h"
#include "Framework/World.h"
#include "Statics/GameplayStatics.h"
#include "Statics/Globals.h"


Application::Application() :
    bRunning(false),
    CurrentWorld(nullptr)
{
}

Application::~Application()
{
}

int Application::Setup()
{
    // Initializes the renderer
    if (URenderer::Init(EDisplayMode::WINDOWED) == -1) return -1;
    URenderer::SetSwapInterval(0);
    
    UDebugger::Log((const char*)glGetString(GL_VERSION));

    // Start running the application
    Run();
    
    return 0;
}


void Application::Run()
{
    OpenWorld<UWorld>();
    SetRunning(true);
    
    while (IsRunning())
    {
        // Clears the renderer
        glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
        URenderer::Clear();

        // Rendering goes here...
        GetWorld()->Update((float)glfwGetTime());

        // Rendering ends here...
        URenderer::SwapBuffers();
        URenderer::PollEvents();
    }

    // Terminates the current world and the objects created in it
    GetWorld()->TerminateObject();
    
    // Terminates Global objects
    UDebugger::GetDebugger()->TerminateObject();
    URenderer::GetRenderer()->TerminateObject();
}

//

bool Application::IsRunning() const
{
    return bRunning && !URenderer::ShouldTerminate();
}

void Application::SetRunning(const bool bNewValue)
{
    bRunning = bNewValue;
}

UWorld* Application::GetWorld()
{
    return CurrentWorld;
}
