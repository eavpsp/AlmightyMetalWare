#include "VertexBuffer.h"
#include "../debug/debug.h"
// GLM headers
#define GLM_FORCE_PURE
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <ShaderInterface.h>
#include <ResourceManager.h>
#include <RenderSystem.h>

GLuint VertexBuffer::getVertexBufferID()
{
    return _vertexBufferID;
}


void VertexBuffer::renderVertexBuffer(void *_renderSystem) //this just doesnt work and i have no idea why, unless i use debuglog to output each frame lol
{
 
   
}

VertexBuffer::VertexBuffer() 
{
    glGenBuffers(1, &_vertexBufferID);

}


void VertexBuffer::initVertexBuffer(const GLvoid *data, GLsizei size, ShaderType shader, GLuint count)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    shaderType = &shader;
    _count = count;
}
void VertexBuffer::initVertexBufferDynamic(GLsizei size)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);

}
void VertexBuffer::initVertexBuffer(std::vector <VertexLit>& vertices, GLsizei size, ShaderType shader, GLuint count)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    shaderType = &shader;
    _count = count;
}
void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    
}
void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

GLuint VertexBuffer::getCount()
{
    return _count;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_vertexBufferID);
    _vertexBufferID = 0;
}

