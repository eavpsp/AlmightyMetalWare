#include <vector>

#include "VertexBuffer.h"

class VertexArray
{
public:
    VertexArray(/* args */);
    ~VertexArray();
    void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout);
    void Bind();
    void SetRenderID(GLuint id);
    void UnBind();

    GLuint GetRendererID();
private:
    GLuint _rendererID;
};