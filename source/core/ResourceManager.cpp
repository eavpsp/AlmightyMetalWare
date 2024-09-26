#include "ResourceManager.h"


ResourceManager::~ResourceManager()
{
    for(std::vector<ShaderInterface *>::iterator it = shaderArray->begin(); it != shaderArray->end(); it++)
    {
        delete *it;
    }
    delete shaderArray;
    for(std::vector<VertexBuffer *>::iterator it = vertexBufferArray->begin(); it != vertexBufferArray->end(); it++)    
    {
        delete *it;
    }
    delete vertexBufferArray;
}
    static const Vertex vertices[] =
    {
        { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { {  0.0f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
    };   

void ResourceManager::initResourceManager()
{

    shaderArray = new std::vector<ShaderInterface *>;
    ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/SimpleLightShader.vs", "romfs:/shaders/SimpleLightShader.fs");
    ShaderInterface *shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
    shaderArray->push_back(shader);
    shaderArray->push_back(light_shader);
    vertexBufferArray = new std::vector<VertexBuffer *>;
    VertexBuffer *vertexBuffer = new VertexBuffer(vertices, sizeof(vertices), GL_TRIANGLES, 3, sizeof(Vertex), shader, (void*)offsetof(Vertex, position) ,(void*)offsetof(Vertex, normal));  
    VertexBuffer *vertexBuffer_light = new VertexBuffer(lennyVertices, sizeof(lennyVertices), GL_TRIANGLES, lennyVerticesCount, sizeof(lennyVertex), light_shader, (void*)offsetof(lennyVertex, x) ,(void*)offsetof(lennyVertex, nx));         
    vertexBufferArray->push_back(vertexBuffer);
    vertexBufferArray->push_back(vertexBuffer_light);
}

std::vector<ShaderInterface *> *ResourceManager::getShaderArray()
{
    return shaderArray;
}

std::vector<VertexBuffer *> *ResourceManager::getVertexBufferArray()
{
    return vertexBufferArray;
}

ResourceManager& ResourceManager::getResourceManager()
{
    static ResourceManager *resourceManager = nullptr;
    if(resourceManager == nullptr)
    {
        resourceManager = new ResourceManager();
    }
    return *resourceManager;
}

void ResourceManager::destroyResourceManager()
{
  ResourceManager *resouceManager = &getResourceManager();

        if(resouceManager != nullptr)
        {
            printf("\x1b[16;20HDestroyed ResourceManager!");
            delete resouceManager;

        }
}
