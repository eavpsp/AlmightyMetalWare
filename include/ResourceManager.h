#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "VertexArray.h"
#include <vector>
#include <EngineMaterials.h>    
#include "GameObject.h"
#include <GameFont.h>

class ResourceManager
{
    private:
    std::vector<ShaderInterface *> *shaderArray;
    std::vector<VertexBuffer *> *vertexArrays;
    
    public:
    ResourceManager(){};
    ~ResourceManager();
    EngineMaterials _engineMaterials;
    //make sure to init in initResourceManagers//
    GLuint s_vao_Default, s_vao_Lit, s_vao_Unlit, s_vao_3D, s_vao_2D, fontAtlasID;
    GameFont *_gameFont;
    void initResourceManager();
    std::vector<ShaderInterface *> *getShaderArray();
    std::vector<VertexBuffer *> *getVertexArray();
    std::vector<GameObject *> *gameObjects;
    //Batching system
    std::vector<VertexLit> VertexLitBatch;
    std::vector<TexturedUnlit> _2DBatch;
    std::vector<unsigned int> VertexLitBatchIndices;
    std::vector<unsigned int> Vertex2DBatchIndices;
    static ResourceManager &getResourceManager();
    static void destroyResourceManager();
};

//
/*
Outline all possible VAOs to be used for rendering
Outline all engine shaders
Outline all scene lights in a vector
*/

#endif