#include "ResourceManager.h"
#include "../debug/debug.h"
#include "Texture.h"
ResourceManager::~ResourceManager()
{
    for(std::vector<ShaderInterface *>::iterator it = shaderArray->begin(); it != shaderArray->end(); it++)
    {
        delete *it;
    }
    delete shaderArray;
    for(std::vector<VertexBuffer *>::iterator it = vertexArrays->begin(); it != vertexArrays->end(); it++)    
    {
        delete *it;
    }
    delete vertexArrays;
}

static const TexturedUnlit vertices[] =
{
    { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } , { 0.0f, 0.0f } },//bottom left
    { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } , { 1.0f, 0.0f } },//bottom right
    { {  0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },//top right
    { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } , { 0.0f, 0.0f } },//bottom left
    { { -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f } , { 0.0f, 1.0f } },//top left
    { {  0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },//top right
};
void ResourceManager::initResourceManager()
{
    //set up materials
    _engineMaterials = EngineMaterials::getEngineMaterialsClass();
    _engineMaterials.initEngineMaterials();

    MW_Texture tex("romfs:/tex.bmp");
    tex.Bind(0);
    _engineMaterials.getColorMaterial()->SetUniform4F("u_Texture", 1.0f, 0.5f, 0.5f, 1.0f);
    VertexArray va;
    glGenVertexArrays(1, &s_vao);
    VertexBuffer vb;
    //bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(s_vao);
    vb.initVertexBuffer(vertices, sizeof(vertices), ShaderType::UNLIT, sizeof(vertices) / sizeof(vertices[0]));
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    va.AddBuffer(vb,layout);
    vb.UnBind();
    va.UnBind();
    vertexArrays = new std::vector<VertexBuffer *>;       
    vertexArrays->push_back(&vb);
    debugLog("vertex array object: %d", vertexArrays->size());
    debugLog("init resource manager complete");
 
}

std::vector<ShaderInterface *> *ResourceManager::getShaderArray()
{
    return shaderArray;
}

std::vector<VertexBuffer *> *ResourceManager::getVertexArray()
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
