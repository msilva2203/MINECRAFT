#include "Tests/PartyTriangle.h"

#include "Statics/Globals.h"
#include "GLFW/glfw3.h"


PartyTriangle::PartyTriangle() :
    red(0.0f),
    inc(1.0f)
{
    float positions[8] = {
        100.0f, 100.0f,
        200.0f, 100.0f,
        200.0f, 200.0f,
        100.0f, 200.0f
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    vao = new VertexArray();
    vbo = new VertexBuffer(positions, 2 * 6 * sizeof(float));
    VertexBufferLayout Layout;
    Layout.Push<float>(2);
    vao->AddBuffer(*vbo, Layout);

    ibo = new IndexBuffer(indices, 6);

    int Width, Height;
    URenderer::GetWindowSize(Width, Height);
    
    glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, 0.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-200, 0, 0));

    glm::mat4 mvp = proj * view * model;

    shader = new Shader("Content/Shaders/main.shader");
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", mvp);
    
    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
    shader->Unbind();
}

void PartyTriangle::TerminateObject()
{
    Super::TerminateObject();
    
    delete vao;
    delete vbo;
    delete ibo;
    delete shader;
}


void PartyTriangle::Tick(float DeltaTime)
{
    if (red < 0.0f) inc =  1.0f;
    if (red > 1.0f) inc = -1.0f;
    red += inc * DeltaTime;

    int Width, Height;
    URenderer::GetWindowSize(Width, Height);
    
    glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, 0.0f, 1.0f);
    glm::mat4 view = URenderer::GetViewMat();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-200, 0, 0));

    glm::mat4 mvp = proj * view * model;
    
    // Binds everything needed to draw
    shader->Bind();
    shader->SetUniform4f("u_Color", red, red/2.0f, 0.6f, 1.0f);
    shader->SetUniformMat4f("u_MVP", mvp);
    vao->Bind();
    ibo->Bind();
        
    // Draws element array
    URenderer::Draw(*vao, *ibo, *shader);
}

bool PartyTriangle::IsTickable() const
{
    return true;
}