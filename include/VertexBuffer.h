#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <glad/glad.h>  // glad library (OpenGL loader)


class VertexBuffer
{
	private:
		GLuint _vertexBufferID;
		GLsizei _count; //verts per mesh
		GLsizei _stride;
		GLenum _mode;
	public:
		void renderVertexBuffer();
		void configureVertexAttributes(GLint vertexPosition);
		GLuint getVertexBufferID();
		VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride)
		;
		~VertexBuffer();
};