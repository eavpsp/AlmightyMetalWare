#ifndef MESHRENDER_H
#define MESHRENDER_H

#include "ShaderMaterialInterface.h"
#include "ViewCamera.h"
#include <objMesh.h>
#include <GameModel.h>
class GameObject;
enum MeshType
{
    OBJ,
    GLTF
};

struct MeshRender
{
    MeshType type;
    std::vector<MW_Texture*> textures;
    MeshRender(){};
    virtual ~MeshRender(){};
};

struct OBJ_MeshRenderer : public MeshRender
{
   
    public:
     ObjMesh *mesh;
    OBJ_MeshRenderer(const char* filePath)
    {
        mesh = new ObjMesh(filePath, this);
        type = OBJ;
    };
     OBJ_MeshRenderer(MeshCreateInfo* createInfo)
    {
        mesh = new ObjMesh(createInfo);
        type = OBJ;
    };
    virtual ~OBJ_MeshRenderer(){};
     void Draw()
    {
        mesh->Draw();
    };
    void EnableTextures()
    {
        for (int i = 0; i < textures.size(); i++)
        {
            textures[i]->Bind(i);
        }
    }
     void UpdateMesh(Material* mat, GameObject* obj, ViewCamera* mainCamera)
    {
        mesh->UpdateMesh(mat, obj, mainCamera);
    }
};

struct GLTF_MeshRenderer : public MeshRender
{

    public:
    GameModel *mesh;

    GLTF_MeshRenderer(const char* filePath)
    {
        mesh = new GameModel(filePath);
        type = GLTF;
    };
    void Draw()
    {
        mesh->Draw();
    }
    virtual ~GLTF_MeshRenderer(){};
   
};


#endif