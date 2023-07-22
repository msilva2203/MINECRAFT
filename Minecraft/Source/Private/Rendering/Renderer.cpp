#include "Rendering/Renderer.h"

#include "Statics/Globals.h"
#include "Framework/Input.h"

#include <sstream>

URenderer* GRenderer;


URenderer::URenderer()
{
    CurrentVideoMode.Width = 1280;
    CurrentVideoMode.Height = 720;
    CurrentVideoMode.Width = 0;
    CurrentVideoMode.Width = 0;
}

URenderer::~URenderer()
{
    glfwTerminate();
}

URenderer* URenderer::GetRenderer()
{
    if (!IsValid(GRenderer))
        GRenderer = new URenderer;
    return GRenderer;
}

void URenderer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool URenderer::IsTickable() const
{
    return Super::IsTickable();
}

int URenderer::CreateWindow(const EDisplayMode DisplayMode)
{
    if (GetWindow())
        glfwDestroyWindow(GetWindow());
    
    CurrentDisplayMode = DisplayMode;
    GLFWmonitor* monitor = NULL;

    switch (DisplayMode)
    {
    case EDisplayMode::FULLSCREEN:
        {
            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            CurrentVideoMode.Width = mode->width;
            CurrentVideoMode.Height = mode->height;
            break;
        }
    case EDisplayMode::WINDOWED:
        {
            CurrentVideoMode.Width = 1280;
            CurrentVideoMode.Height = 720;
            break;
        }
    case EDisplayMode::WINDOWED_FULLSCREEN:
        {
            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            CurrentVideoMode.Width = mode->width;
            CurrentVideoMode.Height = mode->height;
            break;
        }
    }

    Window = glfwCreateWindow(CurrentVideoMode.Width, CurrentVideoMode.Height, "MINECRAFT", monitor, NULL);
    if (!Window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    URenderer::EnableBlending();

    // Rendering Callbacks
    glfwSetWindowSizeCallback(GetWindow(), URenderer::WindowSizeCallback);
    
    // Input Callbacks
    glfwSetKeyCallback(GetWindow(), UInput::KeyCallback);
    glfwSetCursorPosCallback(GetWindow(), UInput::MouseCallback);
    
    return 0;
}

glm::mat4 URenderer::GetViewMat()
{
    glm::mat4 view(1.0f);
    
    if (URenderer* Renderer = URenderer::GetRenderer())
    {
        if (IsValid(Renderer->CurrentCamera))
        {
            glm::vec3 Rotation = Renderer->CurrentCamera->GetCameraRotation();
            
            //view = glm::translate(view, Renderer->CurrentCamera->GetCameraLocation());
            //
            //glm::mat4 rotatex = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), {1.0, 0.0, 0.0});
            //glm::mat4 rotatey = glm::rotate(rotatex, glm::radians(Rotation.y), {0.0, 1.0, 0.0});
            //glm::mat4 rotate = glm::rotate(rotatey, glm::radians(Rotation.z), {0.0, 0.0, 1.0});
            //view = view * rotate;

            glm::vec3 position = Renderer->CurrentCamera->GetCameraLocation();
            glm::vec3 forward = Renderer->CurrentCamera->GetCameraForwardVector();
            glm::vec3 up = Renderer->CurrentCamera->GetCameraUpVector();
            
            view = glm::lookAt(position, position + forward ,up);
        }
    }
    
    return view;
}

glm::mat4 URenderer::GetProjMat()
{
    glm::mat4 proj(1.0f);

    if (URenderer* Renderer = URenderer::GetRenderer())
    {
        UCamera* Camera = Renderer->CurrentCamera;
        assert(Camera);
        if (IsValid(Camera))
        {
            int Width, Height;
            URenderer::GetWindowSize(Width, Height);
            
            float FOV = Camera->GetFOV();
            float aspect = (float)Width / (float)Height;
            proj = glm::perspective(glm::radians(FOV), aspect, 0.1f, 1000.0f);
        }
    }
    return proj;
}

int URenderer::Init(const EDisplayMode DisplayMode)
{
    if (glfwInit() == -1) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    return URenderer::GetRenderer()->CreateWindow(DisplayMode);
}

int URenderer::ShouldTerminate()
{
    return glfwWindowShouldClose(GetWindow());
}

void URenderer::EnableBlending()
{
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    glCall(glEnable(GL_BLEND))
    glCall(glEnable(GL_DEPTH_TEST))
}

void URenderer::SwapBuffers()
{
    glfwSwapBuffers(GetWindow());
}

void URenderer::PollEvents()
{
    glfwPollEvents();
}

void URenderer::SetSwapInterval(int interval)
{
    glfwSwapInterval(interval);
}

void URenderer::SetDisplayMode(const EDisplayMode DisplayMode)
{
    if  (GRenderer->CurrentDisplayMode != DisplayMode)
        GRenderer->CreateWindow(DisplayMode);
}

void URenderer::Clear()
{
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
}

void URenderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr))
}

void URenderer::GetWindowSize(int& Width, int& Height)
{
    glfwGetWindowSize(GRenderer->GetWindow() , &Width, &Height);
}

GLFWwindow* URenderer::GetWindow()
{
    return GRenderer->Window;
}

void URenderer::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    GRenderer->CurrentVideoMode.Width = width;
    GRenderer->CurrentVideoMode.Height = height;
}


void URenderer::glClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool URenderer::glLogCall(const char* function, const char* filename, int line)
{
    if (GLenum error = glGetError())
    {
        std::stringstream message;
        message << "OpenGL (error " << (int)error << ") " << filename << " (line " << line << "): " << function;
        UDebugger::Log(message.str(), ERROR);
        return false;
    }
    return true;
}

