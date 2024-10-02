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
    //sglEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_DEPTH_TEST);
   // glDepthFunc(GL_LESS);
    //Pipeline: Materials -> Models -> Textures -> Draw
    /*
     MW_Texture tex("romfs:/tex.bmp");
    tex.Bind(0);
    glGenVertexArrays(1, &s_vao);
    VertexBuffer *vb = new VertexBuffer();
    glBindVertexArray(s_vao);
    //create a batching system to store staic verts and draw them all at once
    vb->initVertexBuffer(Pyramid, sizeof(Pyramid), ShaderType::LIT, sizeof(Pyramid) / sizeof(Pyramid[0]));
    vb->ib = new IndexBuffer(sizeof(s_indices) / sizeof(s_indices[0]));
    vb->ib->Bind(indices);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    vb->AddBufferLayout(layout);
    vb->UnBind();
    glBindVertexArray(0);
    vb->ib->UnBind();
    debugLog("Index Buffer Count : %d", vb->ib->getCount());
    vertexArrays = new std::vector<VertexBuffer *>;       
    vertexArrays->push_back(vb);
    debugLog("-------------Resources Loaded-------------");
    */
    /*
    MW_Texture tex("romfs:/tex.bmp");
    tex.Bind(0);
    VertexArray va;
    glGenVertexArrays(1, &s_vao);
    VertexBuffer *vb = new VertexBuffer();
    glBindVertexArray(s_vao);
    //create a batching system to store staic verts and draw them all at once
    vb->initVertexBuffer(Square, sizeof(Square), ShaderType::UNLIT, sizeof(Square) / sizeof(Square[0]));
    vb->ib = new IndexBuffer(sizeof(indices) / sizeof(indices[0]));
    vb->ib->Bind(indices);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    va.AddBuffer(*vb,layout);
    vb->UnBind();
    va.UnBind();
    vb->ib->UnBind();
    debugLog("Index Buffer Count : %d", vb->ib->getCount());
    vertexArrays = new std::vector<VertexBuffer *>;       
    vertexArrays->push_back(vb);
    */
    
    
    
        /*MeshData mesh;
        mesh.indices.assign(s_indices, s_indices + sizeof(s_indices) / sizeof(GLuint));
        mesh.vertices.assign(Pyramid, Pyramid + sizeof(Pyramid) / sizeof(VertexLit));
        mesh.initMeshLitTexture(mesh.vertices, mesh.indices, mesh.textures);
        GameModel* modelTest = new GameModel(std::vector<MeshData> { mesh });*/
        


    gameObjects = new std::vector<GameObject *>;

    /*GameModel* modelTest = new GameModel("romfs:/test3.gltf");
    Material *mat = new LitMaterial();
    TestGameObject *obj1 = GameObject::InstantiateGameObject<TestGameObject>(mat, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest);
    gameObjects->push_back(obj1);
    glBindTexture(GL_TEXTURE_2D, 0);
    GameModel*  modelTest2 = new GameModel("romfs:/cube.gltf");
    Material * mat2 = new LitMaterial();
    GameObject *obj2 = GameObject::InstantiateGameObject<GameObject>(mat2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest2);
    //gameObjects->push_back(obj2);*/

   

    
 
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
