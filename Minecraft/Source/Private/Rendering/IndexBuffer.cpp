#include "Rendering/IndexBuffer.h"

#include "Rendering/Renderer.h"
#include "Framework/Debugger.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :
    RendererID(0),
    Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint))
    
    glCall(glGenBuffers(1, &RendererID))
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID))
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW))
}

IndexBuffer::~IndexBuffer()
{
    glCall(glDeleteBuffers(1, &RendererID))
}

void IndexBuffer::Bind() const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID))
}

void IndexBuffer::Unbind() const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

void IndexBuffer::BufferData(const unsigned* data, unsigned count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint))

    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID))
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW))

    Count = count;
}
