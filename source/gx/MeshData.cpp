#include "MeshData.h"
#include <VertexArray.h>
#include "../debug/debug.h"
#include <RenderSystem.h>
void MeshData::initMeshLitTexture(std::vector <VertexLit>& vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures)
{
    vertices = (vertices);
	indices = indices;
	textures = textures;
    //create vb and export it
    vertexBuffer = new VertexBuffer();
    debugLog("total size of vertices: %d", sizeof(vertices)); 
    debugLog("size of single vert: %d", sizeof(vertices[0]));
    debugLog("vert 0 x: %d", sizeof(vertices[0].position.x));
    debugLog("vert 1 x: %d", sizeof(vertices[1].position.x));
    debugLog("vert 2 x: %d", sizeof(vertices[2].position.x));
    vertexBuffer->initVertexBuffer(vertices.data(), (vertices.size() * sizeof(MeshData::vertices[0])), ShaderType::LIT, vertices.size());
    debugLog("vertex buffer size: %d", (vertices.size() * sizeof(MeshData::vertices[0])));
    VertexArray va;
    glGenVertexArrays(1, &RenderSystem::GetResourceManager()->s_vao);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    va.AddBuffer(*MeshData::vertexBuffer, layout);
    vertexBuffer->UnBind();
    va.UnBind();

}

MeshData::MeshData()
{
  
}