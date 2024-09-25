#include "VertexBuffer.h"


void VertexBuffer::renderVertexBuffer()
{
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void VertexBuffer::configureVertexAttributes(GLint vertexPosition)
{
    if(vertexPosition != -1)
    {
        glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, _stride, NULL);//explain the type of data
        glEnableVertexAttribArray(vertexPosition);//Enable the pointer
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }
}

GLuint VertexBuffer::getVertexBufferID()
{
    return _vertexBufferID;
}

VertexBuffer::VertexBuffer(const Vertex *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride) :
_mode(mode),_count(count), _stride(stride)
{
   
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &_vertexBufferID);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    
}


VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &_vertexBufferID);
    _vertexBufferID = 0;
}
