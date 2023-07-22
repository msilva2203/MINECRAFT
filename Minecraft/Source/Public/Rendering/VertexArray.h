#pragma once

#include "Rendering/VertexBufferLayout.h"
#include "Rendering/VertexBuffer.h"


class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& Layout);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int RendererID;
};