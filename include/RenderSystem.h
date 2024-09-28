#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

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
#include <ResourceManager.h>
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

		RenderSystem(){};
		~RenderSystem();
	public:
		void initRenderSystem();
		bool initEgl(NWindow* win);
		void render(VertexBuffer *vertexBuffer);
		static RenderSystem& getRenderSystem();
		void destroyRenderSystem();
		void RenderUnlit(GLuint _count);
		void RenderLit(GLuint _count);
		

};


#endif