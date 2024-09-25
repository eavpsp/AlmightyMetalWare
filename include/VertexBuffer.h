#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <glad/glad.h>  // glad library (OpenGL loader)
struct Vertex
{
	float position[3];
	float color[3];
};

class VertexBuffer
{
	private:
		GLuint _vertexBufferID, vao;
		GLsizei _count; //verts per mesh
		GLsizei _stride;
		GLenum _mode;
	public:
		void renderVertexBuffer();
		void configureVertexAttributes(GLint vertexPosition);
		GLuint getVertexBufferID();
		VertexBuffer(const Vertex *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride);
		~VertexBuffer();
};