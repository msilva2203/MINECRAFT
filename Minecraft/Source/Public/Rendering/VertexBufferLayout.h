#pragma once

#include "Framework/Debugger.h"
#include "GL/glew.h"

#include <vector>


struct VertexBufferElement
{
    unsigned int Type;
    unsigned int Count;
    unsigned char Normalized;
    unsigned char IsInteger;

    static unsigned int GetSizeOfType(unsigned int Type)
    {
        switch (Type)
        {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false)
        return 0;
    }
};

class VertexBufferLayout
{
public:
    template <typename T>
    void Push(unsigned int Count)
    {
        ASSERT(false);
    }

    template <>
    void Push<float>(unsigned int Count)
    {
        Elements.push_back({ GL_FLOAT, Count, GL_FALSE , GL_FALSE });
        Stride += Count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template <>
    void Push<unsigned int>(unsigned int Count)
    {
        Elements.push_back({ GL_UNSIGNED_INT, Count, GL_FALSE , GL_TRUE });
        Stride += Count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template <>
    void Push<unsigned char>(unsigned int Count)
    {
        Elements.push_back({ GL_UNSIGNED_BYTE, Count, GL_TRUE, GL_TRUE });
        Stride += Count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement>& GetElements() const { return Elements; }
    inline unsigned int GetStride() const { return Stride; }
    
private:
    std::vector<VertexBufferElement> Elements;
    unsigned int Stride;
};