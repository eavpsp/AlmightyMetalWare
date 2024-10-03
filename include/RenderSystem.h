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
#include <GameObject.h>
#include <ViewCamera.h>
// nintendo switch screen width and height
const float SCREEN_WIDTH = 1280.0f;
const float SCREEN_HEIGHT = 720.0f;
enum RenderProjectionMode{ORTHOGRAPHIC, PERSPECTIVE};
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
		RenderProjectionMode projectionMode;
 		ResourceManager* _resourceManager;
		RenderSystem(){};
		~RenderSystem();
	public:
		void initRenderSystem(ResourceManager &resourceManager);
		bool initEgl(NWindow* win);
		void render(GameObject *gameObject);
		void render(VertexBuffer *vertexBuffer);
		static RenderSystem& getRenderSystem();
		void destroyRenderSystem();
		ViewCamera *mainCamera, *uiCamera;
		glm::mat4 ortho_projection, perspective_projection;

		void SwapBuffers();
		void RenderLights();

};
constexpr auto TAU = glm::two_pi<float>();

//Group GameObjects into Batches for Rendering
//have gameobjects call renderer to render itself
//vao buffer implementation
//shader -> vao -> draw total vao indicies


#endif