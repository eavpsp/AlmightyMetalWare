#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include <vector>

#include "VertexBuffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout);
    void Bind();
    void UnBind();
    std::vector<VertexBuffer> buffersInArray;
    GLuint GetRendererID();
private:
    GLuint _rendererID = 0;
};
#endif