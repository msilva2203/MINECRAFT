#pragma once
#include "Object.h"

#include "Rendering/Renderer.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

class LiminalTriangle : public UObject
{
    typedef UObject Super;
    
public:
    LiminalTriangle();
    virtual void TerminateObject() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

private:
    VertexArray* vao;
    VertexBuffer* vbo;
    IndexBuffer* ibo;
    Shader* shader;
    Texture* texture;
};