#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "VertexArray.h"
#include <vector>
#include <EngineMaterials.h>    
class ResourceManager
{
    private:
    std::vector<ShaderInterface *> *shaderArray;
    std::vector<VertexBuffer *> *vertexArrays;
    ResourceManager(){};
    ~ResourceManager();
    public:
    EngineMaterials _engineMaterials;
    GLuint s_vao, s_vbo;
    void initResourceManager();
    std::vector<ShaderInterface *> *getShaderArray();
    std::vector<VertexBuffer *> *getVertexArray();
    static ResourceManager &getResourceManager();
    static void destroyResourceManager();
};
#endif