#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Framework/Camera.h"
#include "Framework/Debugger.h"

#include "Rendering/VertexArray.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"

#define glCall(x) URenderer::glClearError();\
    x;\
    ASSERT(URenderer::glLogCall(#x, __FILE__, __LINE__))

enum class EDisplayMode
{
    FULLSCREEN = 0,
    WINDOWED_FULLSCREEN = 1,
    WINDOWED = 2
};

struct FVideoMode
{
    int Width, Height, xPos, yPos;
};


class URenderer : public UObject
{
    typedef UObject Super;
public:
    URenderer();
    ~URenderer();
    static URenderer* GetRenderer();

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

    int CreateWindow(const EDisplayMode DisplayMode);
    void SetCamera(UCamera* Camera) { CurrentCamera = Camera; }
    
    static glm::mat4 GetViewMat();
    static glm::mat4 GetProjMat();
    
public:
    static int Init(const EDisplayMode DisplayMode);
    static int ShouldTerminate();
    static void EnableBlending();
    static void SwapBuffers();
    static void PollEvents();
    static void SetSwapInterval(int interval);
    static void SetDisplayMode(const EDisplayMode DisplayMode);

public:
    static void Clear();
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

public:
    static void GetWindowSize(int& Width, int& Height);
    static GLFWwindow* GetWindow();

public:
    static void WindowSizeCallback(GLFWwindow* window, int width, int height);

public:
    static void glClearError();
    static bool glLogCall(const char* function, const char* filename, int line);

private:
    GLFWwindow* Window;
    UCamera* CurrentCamera;

    EDisplayMode CurrentDisplayMode;
    FVideoMode CurrentVideoMode;
    
};
