#include<RenderSystem.h>
void RenderSystem::render(VertexBuffer *vertexBuffer)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    vertexBuffer->configureVertexAttributes(0);
    vertexBuffer->renderVertexBuffer();
	eglSwapBuffers(s_display, s_surface);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

RenderSystem& RenderSystem::getRenderSystem() {
	static RenderSystem *renderSystem = NULL;

	if (renderSystem == NULL) 
	{
		renderSystem = new RenderSystem();
	}
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    auto projMtx = glm::perspective(40.0f*TAU/360.0f, 1280.0f/720.0f, 0.01f, 1000.0f);
    glViewport(0, 0, 1280, 720);
    
	return *renderSystem;
}

void RenderSystem::destroyRenderSystem() {
	RenderSystem renderSystem = getRenderSystem();
    this->deinitEgl();
    this->sceneExit();
	delete &renderSystem;
}

RenderSystem::RenderSystem()
{
    shaderArray = new std::vector<ShaderInterface *>;
    ShaderInterface *shader = new ShaderInterface("ColorShader.vs", "FragmentShader.fs");
    shaderArray->push_back(shader);
}

/**
 * Destructor for RenderSystem
 *
 * Deletes the shaderArray, which is a vector of ShaderInterface pointers, and the
 * ShaderInterface object itself.
 *
 * @see ~ShaderInterface()
 * @see std::vector::~vector()
 */
RenderSystem::~RenderSystem()
{
    delete shaderArray->at(0);
    delete shaderArray;
}

bool RenderSystem::initEgl(NWindow *win)
{
    // Connect to the EGL default display
    s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (!s_display)
    {
        TRACE("Could not connect to display! error: %d", eglGetError());
        goto _fail0;
    }

    // Initialize the EGL display connection
    eglInitialize(s_display, nullptr, nullptr);

    // Select OpenGL (Core) as the desired graphics API
    if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE)
    {
        TRACE("Could not set API! error: %d", eglGetError());
        goto _fail1;
    }

    // Get an appropriate EGL framebuffer configuration
    EGLConfig config;
    EGLint numConfigs;
    static const EGLint framebufferAttributeList[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE,     8,
        EGL_GREEN_SIZE,   8,
        EGL_BLUE_SIZE,    8,
        EGL_ALPHA_SIZE,   8,
        EGL_DEPTH_SIZE,   24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
    eglChooseConfig(s_display, framebufferAttributeList, &config, 1, &numConfigs);
    if (numConfigs == 0)
    {
        TRACE("No config found! error: %d", eglGetError());
        goto _fail1;
    }

    // Create an EGL window surface
    s_surface = eglCreateWindowSurface(s_display, config, win, nullptr);
    if (!s_surface)
    {
        TRACE("Surface creation failed! error: %d", eglGetError());
        goto _fail1;
    }

    // Create an EGL rendering context
    static const EGLint contextAttributeList[] =
    {
        EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
        EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
        EGL_CONTEXT_MINOR_VERSION_KHR, 3,
        EGL_NONE
    };
    s_context = eglCreateContext(s_display, config, EGL_NO_CONTEXT, contextAttributeList);
    if (!s_context)
    {
        TRACE("Context creation failed! error: %d", eglGetError());
        goto _fail2;
    }

    // Connect the context to the surface
    eglMakeCurrent(s_display, s_surface, s_surface, s_context);

    return true;

_fail2:
    eglDestroySurface(s_display, s_surface);
    s_surface = nullptr;
_fail1:
    eglTerminate(s_display);
    s_display = nullptr;
_fail0:
    return false;
}

void RenderSystem::deinitEgl()
{
    if (s_display)
    {
        eglMakeCurrent(s_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (s_context)
        {
            eglDestroyContext(s_display, s_context);
            s_context = nullptr;
        }
        if (s_surface)
        {
            eglDestroySurface(s_display, s_surface);
            s_surface = nullptr;
        }
        eglTerminate(s_display);
        s_display = nullptr;
    }
}
void RenderSystem::sceneExit()
{
    glDeleteBuffers(1, &s_vbo);
    glDeleteVertexArrays(1, &s_vao);
    glDeleteProgram(s_program);
}