#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <glad/glad.h>  // glad library (OpenGL loader)
#include <ShaderInterface.h>
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
		ShaderInterface *shader;
	public:
		void renderVertexBuffer();
		void configureVertexAttributes();
		ShaderInterface *getShader();
		GLuint getVertexBufferID();
		VertexBuffer(const Vertex *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride, ShaderInterface *shader);
		~VertexBuffer();
};