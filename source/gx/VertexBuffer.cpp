#include "VertexBuffer.h"

void VertexBuffer::renderVertexBuffer()
{
    glDrawArrays(_mode, 0, _count);
}

void VertexBuffer::configureVertexAttributes(GLint vertexPosition)
{
    if(vertexPosition != -1)
    {
        glEnableVertexAttribArray(vertexPosition);//Enable the pointer
        glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, _stride, NULL);//explain the type of data
    }
}

GLuint VertexBuffer::getVertexBufferID()
{
    return _vertexBufferID;
}

VertexBuffer::VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride) :
_mode(mode),_count(count), _stride(stride)
{
    glGenBuffers(1, &_vertexBufferID);//genrerate the vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);//bind the vertexbufferID to the array
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);


}

VertexBuffer::~VertexBuffer()
{

    glDeleteBuffers(1, &_vertexBufferID);
    _vertexBufferID = 0;
}
