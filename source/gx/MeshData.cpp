#include "MeshData.h"
#include <VertexArray.h>
#include "../debug/debug.h"
#include <RenderSystem.h>

extern ResourceManager *gameResourceManager;
void MeshData::initMeshLitTexture(std::vector <VertexLit>& vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures)
{
    this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    glGenVertexArrays(1, &gameResourceManager->s_vao);
    vertexBuffer = new VertexBuffer();
    glBindVertexArray(gameResourceManager->s_vao);
    vertexBuffer->initVertexBuffer(vertices.data(), (vertices.size() * sizeof(vertices[0])), ShaderType::LIT, vertices.size());
    vertexBuffer->ib = new IndexBuffer((indices.size()));
    vertexBuffer->ib->Bind(indices.data());
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    vertexBuffer->AddBufferLayout(layout);
    vertexBuffer->UnBind();
    glBindVertexArray(0);
    vertexBuffer->ib->UnBind();
   
}
void MeshData::initMeshLitTexture(std::vector <TexturedUnlit>& vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures)
{
    this->verticesTex = vertices;
	this->indices = indices;
	this->textures = textures;
    glGenVertexArrays(1, &gameResourceManager->s_vao);
    vertexBuffer = new VertexBuffer();
    glBindVertexArray(gameResourceManager->s_vao);
    vertexBuffer->initVertexBuffer(verticesTex.data(), (verticesTex.size() * sizeof(verticesTex[0])), ShaderType::UNLIT, verticesTex.size());
    vertexBuffer->ib = new IndexBuffer((indices.size()));
    vertexBuffer->ib->Bind(indices.data());
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    vertexBuffer->AddBufferLayout(layout);
    vertexBuffer->UnBind();
    glBindVertexArray(0);
    vertexBuffer->ib->UnBind();

}
MeshData::MeshData()
{
  
}