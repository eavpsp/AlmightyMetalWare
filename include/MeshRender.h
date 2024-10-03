#ifndef MESHRENDER_H
#define MESHRENDER_H

#include "ShaderMaterialInterface.h"
#include "ViewCamera.h"
#include <objMesh.h>
#include <GameModel.h>

enum MeshType
{
    OBJ,
    GLTF
};

struct MeshRender
{
    MeshType type;
    MeshRender(){};
    virtual ~MeshRender(){};
};

struct OBJ_MeshRenderer : public MeshRender
{
    private:
    ObjMesh *mesh;
    public:
    OBJ_MeshRenderer(const char* filePath)
    {
        mesh = new ObjMesh(filePath);
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

     void UpdateMesh(Material* mat, glm::mat4 transform, glm::quat rotation, glm::vec3 scale, ViewCamera* mainCamera)
    {
        mesh->UpdateMesh(mat, transform, rotation, scale, mainCamera);
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