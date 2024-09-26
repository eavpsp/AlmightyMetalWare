#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <glad/glad.h>  // glad library (OpenGL loader)
// GLM headers
#define GLM_FORCE_PURE
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ShaderInterface.h>
struct Vertex//Add more layout structs
{
	float position[3];
	float normal[3];
};

class VertexBuffer
{
	private:
		GLuint _vertexBufferID, vao;
		GLsizei _count; //verts per mesh
		GLsizei _stride;
		GLenum _mode;
		ShaderInterface *shader;
		GLint loc_mdlvMtx, loc_projMtx;
		GLint loc_lightPos, loc_ambient, loc_diffuse, loc_specular;

	public:
		void renderVertexBuffer();
		//void configureVertexAttributes();
		ShaderInterface *getShader();
		GLuint getVertexBufferID();

		VertexBuffer(const GLvoid *data, GLsizei size, GLenum mode, GLsizei count, GLsizei stride, ShaderInterface *shader, void *offsetPositon, void *offsetNormal);
		~VertexBuffer();
};
constexpr auto TAU = glm::two_pi<float>();