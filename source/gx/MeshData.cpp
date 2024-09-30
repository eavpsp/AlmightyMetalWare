#include "MeshData.h"
#include <VertexArray.h>
#include "../debug/debug.h"
#include <RenderSystem.h>
extern ResourceManager gameResourceManager;

void MeshData::initMeshLitTexture(std::vector <VertexLit>& vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures)
{
    this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    vertexBuffer = VertexBuffer();
    debugLog("total elements in verticess: %d", vertices.size()); 
    debugLog("vert 0 x: %f", vertices[0].position.x);
    debugLog("vert 0 y: %f", vertices[1].position.y);
    debugLog("vert 0 z: %f", vertices[2].position.z);
    vertexBuffer.initVertexBuffer(vertices.data(), (vertices.size() * sizeof(vertices[0])), ShaderType::LIT, vertices.size());
    debugLog("vertex buffer size: %d", (vertices.size() * sizeof(vertices[0])));
    VertexArray va;
    glGenVertexArrays(1, &gameResourceManager.s_vao);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    va.AddBuffer(vertexBuffer, layout);
    vertexBuffer.ib = new IndexBuffer((indices.size()));
    vertexBuffer.ib->Bind(indices.data());
    vertexBuffer.UnBind();
    va.UnBind();
    vertexBuffer.ib->UnBind();

}
void MeshData::initMeshLitTexture(std::vector <TexturedUnlit>& vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures)
{
    this->verticesTex = vertices;
	this->indices = indices;
	this->textures = textures;
    vertexBuffer = VertexBuffer();
    vertexBuffer.initVertexBuffer(verticesTex.data(), (verticesTex.size() * sizeof(verticesTex[0])), ShaderType::UNLIT, verticesTex.size());
    debugLog("vertex buffer size: %d", (verticesTex.size() * sizeof(verticesTex[0])));
    VertexArray va;
    glGenVertexArrays(1, &gameResourceManager.s_vao);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    va.AddBuffer(vertexBuffer, layout);
    vertexBuffer.ib = new IndexBuffer((indices.size()));
    vertexBuffer.ib->Bind(indices.data());
    vertexBuffer.UnBind();
    va.UnBind();
    vertexBuffer.ib->UnBind();

}
MeshData::MeshData()
{
  
}