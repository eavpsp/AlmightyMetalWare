#include<RenderSystem.h>
#include<GameManager.h>
#include <ViewCamera.h>
void RenderSystem::render(VertexBuffer *vertexBuffer)//send in program and vao id array
{
    //only works when i direct call lit or unlit, may have two seperate renderers for lit and unlit or every shader lmao
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //vertexBuffer->renderVertexBuffer(this);
    RenderUnlit(vertexBuffer->getCount());
	eglSwapBuffers(s_display, s_surface);

}

RenderSystem& RenderSystem::getRenderSystem() {
	static RenderSystem *renderSystem = NULL;

	if (renderSystem == NULL) 
	{
		renderSystem = new RenderSystem();
	}

	return *renderSystem;
}

void RenderSystem::destroyRenderSystem() {
	RenderSystem renderSystem = getRenderSystem();
    this->deinitEgl();
    this->sceneExit();
	delete &renderSystem;
}

void RenderSystem::RenderUnlit(GLuint _count)
{
        ortho_projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f,SCREEN_HEIGHT, -1.0f, 1.0f);//left, right, bottom, top, near, far
        ViewCamera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        camera.transform = glm::translate(glm::mat4(1.0f), camera.position);
        //Object A Position, Shader 
        {
            obj1->transform = glm::translate(glm::mat4(1.0f),obj1->position);
            glm::mat4 mdlvMtx = ortho_projection * camera.transform * obj1->transform ; //camera * model postition * projections = normalized device coordinates
            obj1->_shaderInterface->SetUniformMat4F("u_ModelViewMatrix", mdlvMtx);
            glUseProgram(obj1->_shaderInterface->getShaderInterface()->getProgramHandle());
            glBindVertexArray(_resourceManager->s_vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, _count);
        }
        //Object B
        {
            obj2->transform = glm::translate(glm::mat4(1.0f),obj2->position);
            glm::mat4 mdlvMtx = ortho_projection * camera.transform * obj2->transform;
            obj2->_shaderInterface->SetUniformMat4F("u_ModelViewMatrix", mdlvMtx);
            glUseProgram(obj2->_shaderInterface->getShaderInterface()->getProgramHandle());
            glBindVertexArray(_resourceManager->s_vao); 
            glDrawArrays(GL_TRIANGLES, 0, _count);
        }
}

void RenderSystem::RenderLit(GLuint _count)
{
        glUseProgram(_resourceManager->_engineMaterials.getLightMaterial()->getShaderInterface()->getProgramHandle());
        glBindVertexArray(_resourceManager->s_vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, _count);
}

void RenderSystem::initRenderSystem(ResourceManager &resourceManager)//later take in projection mode
{
    //set up projection
    _resourceManager = &resourceManager;

    //test objs
    ShaderMaterialInterface *testBitmapMaterial = _resourceManager->_engineMaterials.getColorMaterial();
    testBitmapMaterial->SetUniform4F("u_Texture", 1.0f, 0.5f, 0.5f, 1.0f);
    obj1 = new GameObject(_resourceManager->_engineMaterials.getColorMaterial(), glm::vec3(200.0f, 200.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    obj2 = new GameObject(_resourceManager->_engineMaterials.getColorMaterial(), glm::vec3(200.0f, 500.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

}

RenderSystem::~RenderSystem()
{}

bool RenderSystem::initEgl(NWindow *win)
{
    // Connect to the EGL default display
    s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (!s_display)
    {
        
        goto _fail0;
    }

    // Initialize the EGL display connection
    eglInitialize(s_display, nullptr, nullptr);

    // Select OpenGL (Core) as the desired graphics API
    if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE)
    {
        
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
        
        goto _fail1;
    }

    // Create an EGL window surface
    s_surface = eglCreateWindowSurface(s_display, config, win, nullptr);
    if (!s_surface)
    {
       
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
    glDeleteProgram(s_program);
}