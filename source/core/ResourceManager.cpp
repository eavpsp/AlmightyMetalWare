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

void ResourceManager::initResourceManager()
{
    //set up materials
    _engineMaterials = EngineMaterials::getEngineMaterialsClass();
    _engineMaterials.initEngineMaterials();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //Pipeline: Materials -> Models -> Textures -> Draw
    /*MW_Texture tex("romfs:/tex.bmp");
    tex.Bind(0);
    VertexArray va;
    glGenVertexArrays(1, &s_vao);
    VertexBuffer vb;
    glBindVertexArray(s_vao);
    //create a batching system to store staic verts and draw them all at once
    vb.initVertexBuffer(vertices, sizeof(vertices), ShaderType::UNLIT, sizeof(vertices) / sizeof(vertices[0]));
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    va.AddBuffer(vb,layout);
    vb.UnBind();
    va.UnBind();*/
    MW_Texture tex("romfs:/robo_owl_color.png");
    tex.Bind(0);
    GameModel *modelTest = new GameModel("romfs:/cube.gltf");
    GameObject *obj1 =  new GameObject(_engineMaterials.getLightMaterial(), glm::vec3(50.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest);
    vertexArrays = new std::vector<VertexBuffer *>;       
    vertexArrays->push_back(obj1->objectModel->meshes[0].vertexBuffer);
    gameObjects = new std::vector<GameObject *>;
    gameObjects->push_back(obj1);
    debugLog("model test verts: %d",obj1->objectModel->meshes[0].vertices.size());
    debugLog("model test textures: %d", obj1->objectModel->meshes[0].textures.size());
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
