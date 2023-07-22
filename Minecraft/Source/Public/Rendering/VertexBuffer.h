#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void BufferData(const void* data, unsigned int size);

private:
    unsigned int RendererID;
};
