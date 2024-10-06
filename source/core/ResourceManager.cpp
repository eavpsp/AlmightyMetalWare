#include "ResourceManager.h"
#include "../debug/debug.h"
#include "Texture.h"
#include "GameShapes.h"
#include "ScriptCallbacks.h"
#include <TestGameObject.h>
#include <BPhysics.h>
#include <AnimationComponent.h>
#include <mwmath.h>
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
//praying animation
//207 frames
//praying_Anim000x.obj naming convention
//romfs:/models/animations/praying/praying_Anim000x.obj

void ResourceManager::initResourceManager()
{
    //set up materials
    _engineMaterials = EngineMaterials::getEngineMaterialsClass();
    _engineMaterials.initEngineMaterials();
    //Set up font
    _gameFont = new GameFont("romfs:/gameFonts/mp1m.ttf", 32);
    //set up Game Scene and Skybox
    SceneSkybox *skybox = new SceneSkybox();//load default skybox

    _gameScene = new GameScene(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f), skybox);
   //Objects must use the same shader to draw into the scene at its own positions
   //this is because the shader program stores uniform data such as camera position and view matrix
   //since this is how the camera references positions, the objects can use the same shader//
   //if not objects spawn in the most recent object shader program position because they are using the data first stored into the shader

    gameObjects = new std::vector<GameObject *>;

    glm::vec3 pos = glm::vec3(MW_Math::Random(0.0f,5.0f), 0.0f, 0.0f);
    GameObject *obj1 = GameObject::CreateCapsule(_engineMaterials.getLightMaterial(), pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    
    btCollisionShape* colShape1 = new btSphereShape(btScalar(1.));//need
   
    BPhysicsComponent* rigidBody1 = new BPhysicsComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, colShape1);

   
    obj1->AddComponent(rigidBody1);
    AnimationFile *prayingAnim = new AnimationFile("praying", true, 60.0f);
    prayingAnim->frameCount = 207;
  
    for (int i = 0; i < prayingAnim->frameCount; i++)//works create a func for this later
    {
        std::string num = std::to_string(i + 1);
        std::stringstream ss;
        ss << "romfs:/models/animations/praying/praying_Anim" << std::setw(4) << std::setfill('0') << (i + 1) << ".obj";
        std::string filename = ss.str();
        prayingAnim->objFiles.push_back(filename);
    }
    AnimationArchive *prayingArchive = new AnimationArchive();
    debugLog("archive made");
    prayingArchive->animationFiles.push_back(prayingAnim);
    debugLog("animation files added");
    OBJ_MeshRenderer* modelTest2 = new OBJ_MeshRenderer("romfs:/models/aman.obj"); //object model name or sha hash buffer for dupes
    AnimationComponent *animComp = new AnimationComponent(*prayingArchive,modelTest2);
    debugLog("animation component made");

    GameObject *obj2 = GameObject::InstantiateGameObject<GameObject>(_engineMaterials.getLightMaterial(), glm::vec3(5.0f, 15.0f, 0.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), modelTest2);
    
    btCollisionShape* colShape = new btSphereShape(btScalar(1.));//need
   
    BPhysicsComponent* rigidBody = new BPhysicsComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, colShape);
    obj2->AddComponent(animComp);
     AnimationComponent *animCompGot = obj2->GetComponent<AnimationComponent>();
    animCompGot->PlayAnimation("praying");
   
    obj2->AddComponent(rigidBody);
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
