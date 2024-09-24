#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <EGL/egl.h>    // EGL library
#include <EGL/eglext.h> // EGL extensions
#include <glad/glad.h>  // glad library (OpenGL loader)

// GLM headers
#define GLM_FORCE_PURE
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <VertexBuffer.h>
#include <vector>
#include<ShaderInterface.h>
class RenderSystem
{
	private:
		//-----------------------------------------------------------------------------
		// EGL initialization
		//-----------------------------------------------------------------------------

		EGLDisplay s_display;
		EGLContext s_context;
		EGLSurface s_surface;
		void deinitEgl();
		void sceneExit();
		GLuint s_program;
		GLuint s_vao, s_vbo;

		GLint loc_mdlvMtx, loc_projMtx;
		GLint loc_lightPos, loc_ambient, loc_diffuse, loc_specular;
		std::vector<ShaderInterface *> *shaderArray;
		RenderSystem();
		~RenderSystem();
	public:
		bool initEgl(NWindow* win);
		void render(VertexBuffer *vertexBuffer);
		static RenderSystem& getRenderSystem();
		void destroyRenderSystem();

};
constexpr auto TAU = glm::two_pi<float>();

#define TRACE(fmt,...) printf("%s: " fmt "\n", __PRETTY_FUNCTION__, ## __VA_ARGS__)



