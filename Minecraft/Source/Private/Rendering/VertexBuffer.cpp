#include "Rendering/VertexBuffer.h"

#include "Rendering/Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) :
    RendererID(0)
{
    glCall(glGenBuffers(1, &RendererID))
    glCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID))
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
}

VertexBuffer::~VertexBuffer()
{
    glCall(glDeleteBuffers(1, &RendererID))
}

void VertexBuffer::Bind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID))
}

void VertexBuffer::Unbind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
}

void VertexBuffer::BufferData(const void* data, unsigned int size)
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID))
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
}
