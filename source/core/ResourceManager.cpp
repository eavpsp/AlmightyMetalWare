#include "ResourceManager.h"
#include "../debug/debug.h"
#include "Texture.h"
#include "GameShapes.h"
#include "ScriptCallbacks.h"
#include <TestGameObject.h>
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
    VertexLit Square[] =
    {
        { { -50.0f, -50.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } , { 0.0f, 0.0f } },//bottom left
        { { 50.0f, -50.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } , { 1.0f, 0.0f } },//bottom right
        { { 50.0f, 50.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },//top right
        { { -50.0f, 50.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } , { 0.0f, 1.0f } },//top left
    };

     GLuint indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    VertexLit Pyramid[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        {{-0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},	{0.0f, 0.0f}},
        {{-0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},	{5.0f, 0.0f}},
        {{ 0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},	{0.0f, 0.0f}},
        {{ 0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},	{5.0f, 0.0f}},
        {{ 0.0f, 0.8f,  0.0f},     {0.92f, 0.86f, 0.76f},	{2.5f, 5.0f}}
    };

// Indices for vertices order
GLuint s_indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

void ResourceManager::initResourceManager()
{
    //set up materials
    _engineMaterials = EngineMaterials::getEngineMaterialsClass();
    _engineMaterials.initEngineMaterials();
    _gameFont = new GameFont("romfs:/gameFonts/mp1m.ttf", 32);

   //Objects must use the same shader to draw into the scene at its own positions
   //this is because the shader program stores uniform data such as camera position and view matrix
   //since this is how the camera references positions, the objects can use the same shader
   //if not objects spawn in the most recent object shader program position because they are using the data first stored into the shader

    gameObjects = new std::vector<GameObject *>;

    OBJ_MeshRenderer* modelTest = new OBJ_MeshRenderer("romfs:/models/prim/sphere.obj");

    GameObject *obj1 = GameObject::InstantiateGameObject<GameObject>(_engineMaterials.getLightMaterial(), glm::vec3(0.0f, 0.0f,0.0f), glm::vec3(100.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest);
    
    OBJ_MeshRenderer* modelTest2 = new OBJ_MeshRenderer("romfs:/models/owl.obj"); //object model name or sha hash buffer for dupes

    GameObject *obj2 = GameObject::InstantiateGameObject<GameObject>(_engineMaterials.getLightMaterial(), glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest2);
    //TestGameObject *obj1 = GameObject::InstantiateGameObject<TestGameObject>(mat, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest);
    gameObjects->push_back(obj1);
    gameObjects->push_back(obj2);
    

   

    
 
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
