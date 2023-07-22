#include "Tests/LiminalTriangle.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

LiminalTriangle::LiminalTriangle()
{
    float positions[16] = {
        100.0f, 100.0f,   0.0f, 0.0f,    // 0
        200.0f, 100.0f,   1.0f, 0.0f,    // 1
        200.0f, 200.0f,   1.0f, 1.0f,    // 2
        100.0f, 200.0f,   0.0f, 1.0f     // 3
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    vao = new VertexArray();
    vbo = new VertexBuffer(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout Layout;
    Layout.Push<float>(2);
    Layout.Push<float>(2);
    vao->AddBuffer(*vbo, Layout);

    ibo = new IndexBuffer(indices, 6);

    int Width, Height;
    URenderer::GetWindowSize(Width, Height);
    
    glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, 0.0f, 1.0f);
    glm::mat4 view = URenderer::GetViewMat();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    glm::mat4 mvp = proj * view * model;

    shader = new Shader("Content/Shaders/liminal.shader");
    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    shader->SetUniformMat4f("u_MVP", mvp);

    texture = new Texture("Content/Textures/triangle.png");
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);
    
    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
    shader->Unbind();
}

void LiminalTriangle::TerminateObject()
{
    Super::TerminateObject();

    delete vao;
    delete vbo;
    delete ibo;
    delete shader;
    delete texture;
}

void LiminalTriangle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    int Width, Height;
    URenderer::GetWindowSize(Width, Height);
    
    glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, 0.0f, 1.0f);
    glm::mat4 view = URenderer::GetViewMat();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-200, 0, 0));

    glm::mat4 mvp = proj * view * model;

    // Binds everything needed to draw
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", mvp);
    vao->Bind();
    ibo->Bind();
        
    // Draws element array
    URenderer::Draw(*vao, *ibo, *shader);
}

bool LiminalTriangle::IsTickable() const
{
    return true;
}
