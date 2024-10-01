#ifndef MESHDATA_H
#define MESHDATA_H

#include <glad/glad.h>
#include <vector>
#include <Texture.h>
#include <VertexBuffer.h>
class MeshData
{
public:
	std::vector <VertexLit> vertices;
	std::vector <TexturedUnlit> verticesTex;
	std::vector <GLuint> indices;
	std::vector <MW_Texture> textures;
	ShaderType shaderType;

    MeshData(std::vector <VertexLit>& vertices, std::vector <GLuint>& indices, std::vector <MW_Texture>& textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		shaderType = ShaderType::LIT;
	};

	MeshData(std::vector <TexturedUnlit>& vertices, std::vector <GLuint>& indices, std::vector <MW_Texture>& textures)
	{
		this->verticesTex = vertices;
		this->indices = indices;
		shaderType = ShaderType::UNLIT;
		this->textures = textures;
	}
    ~MeshData(){};
};




#endif // MESHDATA_H
