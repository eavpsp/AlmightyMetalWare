#include "IndexBuffer.h"
#include "../debug/debug.h"




IndexBuffer::IndexBuffer(const GLvoid *data, GLsizei count) : _count(count)
{
    glGenBuffers(1, &_indexexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexexBufferID);
     
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
