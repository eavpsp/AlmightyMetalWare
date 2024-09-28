#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
//TODO Assign buffer to GameEntity
#include <glad/glad.h>  // glad library (OpenGL loader)
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "ShaderInterface.h"

struct Vertex//Add more layout structs tex coords
{
	float position[3];//Postion Vector
	float normal[3];//Normal Vector
};
struct ColorVertex
{
	GLfloat position[3];
	GLfloat color[3];
};
enum ShaderType
{
	UNLIT,
	LIT	
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
		VertexBuffer();
		~VertexBuffer();
};
#endif