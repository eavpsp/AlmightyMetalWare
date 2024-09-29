#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
//TODO Assign buffer to GameEntity
#include <glad/glad.h>  // glad library (OpenGL loader)
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "ShaderInterface.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"



//set up vb layouts to the structs to store the layout data
struct VertexLit//Add more layout structs tex coords
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
	VertexLit(){}
	VertexLit(glm::vec3 position, glm::vec3 normal, glm::vec2 texUV) 
	{
		this->position = position;
		this->normal = normal;
		this->texUV = texUV;
		}
	~VertexLit(){}

};
struct ColorVertex
{
	glm::vec3 position;
	glm::vec4 color;
};
struct TexturedUnlit
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texUV;
};
enum ShaderType
{
	UNLIT,
	LIT,
	TEX_UNLIT,
	TEX_LIT
};
class VertexBuffer
{
	private:
		GLuint _vertexBufferID, _count;
		GLsizei size; //verts per mesh
	public:
		GLuint getVertexBufferID();
		void renderVertexBuffer(void *_renderSystem);
		ShaderType *shaderType;
		void Bind() const;
		void UnBind() const;
		GLuint getCount();
		void initVertexBuffer(const GLvoid *data, GLsizei size, ShaderType shader, GLuint count);
		void initVertexBuffer(std::vector <VertexLit>& vertices, GLsizei size, ShaderType shader, GLuint count);
		VertexBuffer();
		~VertexBuffer();
};
#endif