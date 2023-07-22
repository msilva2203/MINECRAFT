#pragma once

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    void BufferData(const unsigned int* data, unsigned int count);

    inline unsigned int GetCount() const { return Count; }

private:
    unsigned int RendererID;
    unsigned int Count;
};
