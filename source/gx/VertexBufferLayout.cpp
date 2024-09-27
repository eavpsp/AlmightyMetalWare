#include "VertexBufferLayout.h"
#include "../debug/debug.h"

VertexBufferLayout::~VertexBufferLayout()
{

}
void VertexBufferLayout::AddElement(unsigned int type, unsigned int count, unsigned char normalized)
{
    VertexBufferElement element = {type, count, normalized};
    _elements.push_back(element);
    _stride += VertexBufferElement::GetSizeOfType(type) * count;
    debugLog("Added Element");
}

//never get called?
