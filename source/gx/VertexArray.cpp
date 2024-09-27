#include "VertexArray.h"
#include "../debug/debug.h"
VertexArray::VertexArray()
{
    //glGenVertexArrays(1, &_rendererID);
    debugLog("Created VertexArray %u", _rendererID);
}


VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, VertexBufferLayout &layout)
{
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
        glEnableVertexAttribArray(i);

        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}


void VertexArray::Bind() 
{
    glBindVertexArray(_rendererID);
    debugLog("Bound VertexArray %u", _rendererID);
}

void VertexArray::SetRenderID(GLuint id)
{
    _rendererID = id;
}

void VertexArray::UnBind() 
{
    glBindVertexArray(0);

}

GLuint VertexArray::GetRendererID() 
{
    return _rendererID;
}
