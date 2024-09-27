
#include <glad/glad.h>  // glad library (OpenGL loader)

#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

struct Vertex//Add more layout structs
{
	float position[3];//Postion Vector
	float normal[3];//Normal Vector
};
struct ColorVertex
{
	GLfloat position[3];
	GLfloat color[3];
};
class VertexBuffer
{
	private:
		GLuint _vertexBufferID;
		GLsizei size; //verts per mesh
	
		IndexBuffer *indexBuffer;
	public:
		void renderVertexBuffer();
		//void configureVertexAttributes();
		GLuint getVertexBufferID();
		void Bind() const;
		void UnBind() const;
		void initVertexBuffer(const GLvoid *data, GLsizei size);
		VertexBuffer();
		//VertexBuffer(const GLvoid *data, GLsizei size, GLenum mode, GLsizei count, GLsizei stride, ShaderInterface *shader, void *offsetPositon, void *offsetNormal, IndexBuffer* indicies_);
		~VertexBuffer();
};
