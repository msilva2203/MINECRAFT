#pragma once
#include "Entity.h"

#include "Rendering/Renderer.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/Shader.h"

class RotatingCube : public AEntity
{
    typedef AEntity Super;
public:
    RotatingCube();
    virtual void InitObject() override;
    virtual void TerminateObject() override;
    virtual void Tick(float DeltaTime) override;

    void CalculateMVP();

private:
    VertexArray* vao;
    VertexBuffer* vbo;
    IndexBuffer* ibo;
    Shader* shader;
};
