#include "Rendering/VertexArray.h"

#include "Rendering/Renderer.h"

VertexArray::VertexArray()
{
    glCall(glGenVertexArrays(1, &RendererID))
}

VertexArray::~VertexArray()
{
    glCall(glDeleteVertexArrays(1, &RendererID))
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& Layout)
{
    this->Bind();
    
    vb.Bind();
    const auto& Elements = Layout.GetElements();
    unsigned int offset = 0;
    
    for (unsigned int i = 0; i < Elements.size(); i++)
    {
        const auto& Element = Elements[i];
        
        glCall(glEnableVertexAttribArray(i))
        
        if (Element.IsInteger == GL_TRUE)
        {
            glVertexAttribIPointer(i, Element.Count, Element.Type, Layout.GetStride(), (const void*)offset);
        }
        else
        {
            glVertexAttribPointer(i, Element.Count, Element.Type, Element.Normalized, Layout.GetStride(), (const void*)offset);
        }

        offset += Element.Count * VertexBufferElement::GetSizeOfType(Element.Type);
    }
}

void VertexArray::Bind() const
{
    glCall(glBindVertexArray(RendererID))
}

void VertexArray::Unbind() const
{
    glCall(glBindVertexArray(0))
}

