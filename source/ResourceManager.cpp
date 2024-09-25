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
    
    static const Vertex cube[] = 
    {
    // Define the vertices for the cube
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // vertex 0
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // vertex 1
    {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // vertex 2
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // vertex 3
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // vertex 4
    {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // vertex 5
    {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // vertex 6
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // vertex 7

    // Define the normals for each face
    // Front face
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},

    // Back face
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

    // Left face
    {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},

    // Right face
    {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},

    // Top face
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

    // Bottom face
    {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}},
    {{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
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
    VertexBuffer *vertexBuffer_light = new VertexBuffer(cube, sizeof(cube), GL_TRIANGLES, sizeof(cube)/sizeof(Vertex), sizeof(Vertex), light_shader, (void*)offsetof(Vertex, position) ,(void*)offsetof(Vertex, normal));         
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
