#include "ResourceManager.h"
#include "../debug/debug.h"
ResourceManager::~ResourceManager()
{
    for(std::vector<ShaderInterface *>::iterator it = shaderArray->begin(); it != shaderArray->end(); it++)
    {
        delete *it;
    }
    delete shaderArray;
    for(std::vector<VertexArray *>::iterator it = vertexArrays->begin(); it != vertexArrays->end(); it++)    
    {
        delete *it;
    }
    delete vertexArrays;
}
static const ColorVertex vertices[] =
{
    { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
    { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
    { {  0.0f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
};   
static const unsigned int indices[] =
{
   0, 1, 2,

};

void ResourceManager::initResourceManager()
{
    shaderArray = new std::vector<ShaderInterface *>;
    ShaderInterface *color_shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
    shaderArray->push_back(color_shader);
    VertexArray va;
    glGenVertexArrays(1, &s_vao);
    VertexBuffer vb;
    //bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(s_vao);
    vb.initVertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    debugLog("Elements Complete");
    va.AddBuffer(vb,layout);
    vb.UnBind();
    va.UnBind();
    vertexArrays = new std::vector<VertexArray *>;       
    vertexArrays->push_back(&va);
 
}

std::vector<ShaderInterface *> *ResourceManager::getShaderArray()
{
    return shaderArray;
}

std::vector<VertexArray *> *ResourceManager::getVertexArray()
{
    return vertexArrays;
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
