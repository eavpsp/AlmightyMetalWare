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
static const float indices[] =
{
   0.0f, 1.0f, 2.0f,

};

/*void ResourceManager::initResourceManager()
{
    //Shader -> VAO -> VBO -> Render
    shaderArray = new std::vector<ShaderInterface *>;
    //ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/SimpleLightShader.vs", "romfs:/shaders/SimpleLightShader.fs");
    ShaderInterface *color_shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
    shaderArray->push_back(color_shader);
   // shaderArray->push_back(light_shader);
    VertexArray va;
    VertexBuffer vb;
    va.Bind();
    vb.initVertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);//adds elment here
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);//adds elment here
    debugLog("Elements Complete");
    va.AddBuffer(vb,layout);
    vertexArrays = new std::vector<VertexArray *>;       
    vertexArrays->push_back(&va);
    vb.UnBind();
    va.UnBind();
    
}*/

void ResourceManager::initResourceManager()
{
    shaderArray = new std::vector<ShaderInterface *>;
    ShaderInterface *color_shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
    shaderArray->push_back(color_shader);
    VertexArray va;
    glGenVertexArrays(1, &s_vao);
    VertexBuffer vb;
    //bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(s_vao);//issue is here
    vb.initVertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);//adds elment here
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);//adds elment here
    debugLog("Elements Complete");
    va.AddBuffer(vb,layout);
    IndexBuffer ib(indices, sizeof(indices) / sizeof(float));
    ib.Bind();
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    vertexArrays = new std::vector<VertexArray *>;       
    vertexArrays->push_back(&va);
    //va.SetRenderID(s_vao);

    
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
