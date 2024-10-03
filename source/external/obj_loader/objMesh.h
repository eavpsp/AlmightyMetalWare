#ifndef OBJMESH_H
#define OBJMESH_H

#include "objLoader.h"
#include <ShaderMaterialInterface.h>
#include <VertexArray.h>
#include <ViewCamera.h>

class GameObject;
class OBJ_MeshRenderer;
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
	void UpdateMesh(Material* mat, GameObject* obj, ViewCamera* mainCamera);
	ObjMesh(MeshCreateInfo* createInfo);
	ObjMesh(const char* filePath, OBJ_MeshRenderer* meshRender);
	~ObjMesh();
};



#endif // OBJMESH_H
