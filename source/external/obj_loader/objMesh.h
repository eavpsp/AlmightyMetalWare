#ifndef OBJMESH_H
#define OBJMESH_H

#include "objLoader.h"
#include <ShaderMaterialInterface.h>
#include <VertexArray.h>
#include <ViewCamera.h>
struct MeshCreateInfo {
	const char* filename;
	glm::mat4 preTransform;
};

class ObjMesh {
public:
	unsigned int VBO, VAO, vertexCount;
	VertexArray *vertexArray;
	VertexBuffer *vertexBuffer;
	void Draw();
	void UpdateMesh(Material* mat, glm::mat4 transform, glm::quat rotation, glm::vec3 scale, ViewCamera* mainCamera);
	ObjMesh(MeshCreateInfo* createInfo);
	ObjMesh(const char* filePath);
	~ObjMesh();
};



#endif // OBJMESH_H
