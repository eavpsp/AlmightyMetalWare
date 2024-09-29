#include "MeshData.h"

void MeshData::initMeshLitTexture(std::vector <VertexLit>& vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures)
{
    MeshData::vertices = (vertices);
	MeshData::indices = indices;
	MeshData::textures = textures;
    //create vb and export it
    MeshData::vertexBuffer = new VertexBuffer();
    MeshData::vertexBuffer->initVertexBuffer(vertices.data(), sizeof(vertices), ShaderType::LIT, sizeof(vertices) / sizeof(MeshData::vertices[0]));
    //must add to VAO with VB Layout
}

MeshData::MeshData(GLvoid* vertices, std::vector<GLuint> &indices, std::vector<MW_Texture> &textures, ShaderType shaderType)
{
    //decide which init to use
    if (shaderType == ShaderType::LIT)
    {
        initMeshLitTexture(*reinterpret_cast<std::vector<VertexLit>*>(vertices), indices, textures);
    }
}