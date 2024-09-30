#include "IndexBuffer.h"
#include "../debug/debug.h"




IndexBuffer::IndexBuffer( GLsizei count) : _count(count)
{
    glGenBuffers(1, &_indexexBufferID);
    
}
void IndexBuffer::Bind(const GLvoid *data) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    
}
void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &_indexexBufferID);
    _indexexBufferID = 0;
}
