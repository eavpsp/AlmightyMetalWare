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
    VertexBuffer vertexBuffer;
	// Initializes the mesh
	void initMeshLitTexture(std::vector <VertexLit>& vertices, std::vector <GLuint>& indices, std::vector <MW_Texture>& textures);
	void initMeshLitTexture(std::vector <TexturedUnlit>& vertices, std::vector <GLuint>& indices, std::vector <MW_Texture>& textures);

    MeshData();
    ~MeshData(){};
};




#endif // MESHDATA_H
