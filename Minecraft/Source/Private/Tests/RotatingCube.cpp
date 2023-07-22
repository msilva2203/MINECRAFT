#include "Tests/RotatingCube.h"

#include "glm/gtx/quaternion.hpp"
#include "Statics/GameplayStatics.h"
#include "Framework/TimerManager.h"
#include "Statics/Globals.h"

static TimerHandle handle;
static TimerHandle handle1;

static void Print()
{
    std::stringstream message;
    message << (UGameplayStatics::GetWorldTimerManager(GApp)->TimeRemaining(handle));
    UDebugger::Log(message.str());
}

static void Function()
{
    std::stringstream message;
    message << "Handle is " << (UGameplayStatics::GetWorldTimerManager(GApp)->IsTimerActive(handle) ? "valid!" : "invalid!");
    //UDebugger::Log(message.str());
}

RotatingCube::RotatingCube()
{
    float positions[48] = {
        -0.5f,  -0.5f,  -0.5f,      0.583f,  0.771f,  0.014f,
         0.5f,  -0.5f,  -0.5f,      0.609f,  0.115f,  0.436f,
         0.5f,   0.5f,  -0.5f,      0.327f,  0.483f,  0.844f,
        -0.5f,   0.5f,  -0.5f,      0.822f,  0.569f,  0.201f,
         0.5f,  -0.5f,   0.5f,      0.435f,  0.602f,  0.223f,
         0.5f,   0.5f,   0.5f,      0.310f,  0.747f,  0.185f,
        -0.5f,  -0.5f,   0.5f,      0.597f,  0.770f,  0.761f,
        -0.5f,   0.5f,   0.5f,      0.559f,  0.436f,  0.730f
    };

    unsigned int indices[36] = {
        0, 1, 2,
        2, 3, 0,
        1, 4, 5,
        5, 2, 1,
        4, 6, 7,
        7, 5, 4,
        6, 0, 3,
        3, 7, 6,
        0, 1, 4,
        4, 6, 0,
        3, 2, 5,
        5, 7, 3
    };

    glm::vec3 NewLocation(0.0f, 0.0f, 0.0f);
    glm::vec3 NewRotation(50.0f, 50.0f, 50.0f);
    glm::vec3 NewScale(20.0f, 20.0f, 20.0f);
    SetEntityLocation(NewLocation);
    SetEntityRotation(NewRotation);
    SetEntityScale(NewScale);
    
    vao = new VertexArray;
    vbo = new VertexBuffer(positions, 3 * 8 * sizeof(float) * 2);
    VertexBufferLayout Layout;
    Layout.Push<float>(3);
    Layout.Push<float>(3);
    vao->AddBuffer(*vbo, Layout);
    
    ibo = new IndexBuffer(indices, 3 * 6 * 2);
    
    shader = new Shader("Content/Shaders/cube.shader");
    shader->Bind();
    shader->SetUniform4f("u_ColorMultiplier", 1.0, 1.0, 1.0, 1.0);
    CalculateMVP();

    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
    shader->Unbind();
}

void RotatingCube::InitObject()
{
    Super::InitObject();
    
    GetWorldTimerManager()->SetTimer(handle, Function, 10.0f, true, "Test Timer 0", true);
    GetWorldTimerManager()->SetTimer(handle1, Print, 0.1f, true, "Time Remaining Timer");
}

void RotatingCube::TerminateObject()
{
    Super::TerminateObject();

    delete vao;
    delete vbo;
    delete ibo;
    delete shader;
}

void RotatingCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    glm::vec3 Rotation = GetEntityRotation();
    glm::vec3 Scale = GetEntityScale();
    Rotation.x += 20.0 * DeltaTime;
    Rotation.y += 10.0 * DeltaTime;
    Rotation.z += 5.0 * DeltaTime;
    Rotation.x += 20.0 * DeltaTime;
    Rotation.y += 10.0 * DeltaTime;
    Rotation.z += 5.0 * DeltaTime;
    SetEntityRotation(Rotation);
    SetEntityScale(Scale);

    // Binds everything needed to draw
    shader->Bind();
    CalculateMVP();
    vao->Bind();
    ibo->Bind();
        
    // Draws element array
    URenderer::Draw(*vao, *ibo, *shader);
}

void RotatingCube::CalculateMVP()
{
    glm::mat4 proj = URenderer::GetProjMat();
    glm::mat4 view = URenderer::GetViewMat();

    glm::mat4 rotatex = glm::rotate(glm::mat4(1.0f), glm::radians(GetEntityRotation().x), {1.0f, 0.0f, 0.0f});
    glm::mat4 rotatey = glm::rotate(rotatex, glm::radians(GetEntityRotation().y), {0.0f, 1.0f, 0.0f});
    glm::mat4 rotation = glm::rotate(rotatey, glm::radians(GetEntityRotation().z), {0.0f, 0.0f, 1.0f});
    
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), GetEntityLocation());
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), GetEntityScale());
    glm::mat4 model = translation * rotation * scale;

    glm::mat4 mvp = proj * view * model;

    shader->SetUniformMat4f("u_MVP", mvp);
}
