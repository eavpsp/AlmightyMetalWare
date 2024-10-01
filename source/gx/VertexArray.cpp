#include "VertexArray.h"
#include "../debug/debug.h"
VertexArray::VertexArray(GLuint id)
{   
    _rendererID = id;
    debugLog("Created VertexArray %u", _rendererID);
}


VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_rendererID);
}

/**
 * @brief Add a VertexBuffer to the VertexArray, applying the layout to it
 *
 * @param[in] vb The VertexBuffer to add
 * @param[in] layout The VertexBufferLayout to apply to the VertexBuffer
 *
 * This function applies the VertexBufferLayout to the VertexBuffer, and then
 * binds the VertexBuffer to the VertexArray.
 */
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
    buffersInArray.push_back(vb);
}


void VertexArray::Bind() 
{
    glBindVertexArray(_rendererID);
    
}



void VertexArray::UnBind() 
{
    glBindVertexArray(0);

}

GLuint VertexArray::GetRendererID() 
{
    return _rendererID;
}
