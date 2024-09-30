#include<RenderSystem.h>
#include<GameManager.h>

#include "../debug/debug.h"

bool lightScene = false;
void RenderSystem::render(GameObject *gameObject)//send in program and vao id array
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //RenderLit(gameObject);
	eglSwapBuffers(s_display, s_surface);

}

void RenderSystem::render(VertexBuffer *vertexBuffer)
{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ortho_projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f,SCREEN_HEIGHT, -1.0f, 1.0f);//left, right, bottom, top, near, far
        mainCamera->transform = glm::translate(glm::mat4(1.0f), mainCamera->position);  //Object A Position, Shader 
        {
            glm::mat4 mdlvMtx = ortho_projection * mainCamera->transform * glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f)); //mainCamera * model postition * projections = normalized device coordinates
            _resourceManager->_engineMaterials.getColorMaterial()->SetUniformMat4F("u_ModelViewMatrix", mdlvMtx);
            glUseProgram( _resourceManager->_engineMaterials.getColorMaterial()->getShaderInterface()->getProgramHandle());
            glBindVertexArray(_resourceManager->s_vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawElements(GL_TRIANGLES, vertexBuffer->ib->getCount(), GL_UNSIGNED_INT, 0);

        }
        {
            glm::mat4 mdlvMtx = ortho_projection * mainCamera->transform * glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 100.0f, 0.0f));
             _resourceManager->_engineMaterials.getColorMaterial()->SetUniformMat4F("u_ModelViewMatrix", mdlvMtx);
            glUseProgram( _resourceManager->_engineMaterials.getColorMaterial()->getShaderInterface()->getProgramHandle());
            glBindVertexArray(_resourceManager->s_vao); 
            glDrawElements(GL_TRIANGLES, vertexBuffer->ib->getCount(), GL_UNSIGNED_INT, 0);
            
        }
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

void RenderSystem::RenderUnlit(GameObject *gameObject)
{

}

void RenderSystem::RenderLit(VertexBuffer *vertexBuffer)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (vertexBuffer == nullptr)  {
        // Handle the case where the vector is empty/
        debugLog("gameObjects is empty");
        return;
    }
    if(!lightScene)
    {
        glUseProgram(_resourceManager->_engineMaterials.getLightMaterial()->getShaderInterface()->getProgramHandle());
        mainCamera->Matrix(45.0f,0.1f,100.0f, _resourceManager->_engineMaterials.getLightMaterial(), "camMatrix");
        lightScene = true;
    }
   
    mainCamera->Matrix(45.0f,0.1f,100.0f, _resourceManager->_engineMaterials.getLightMaterial(), "camMatrix");

   
    glBindVertexArray(_resourceManager->s_vao);
   if (vertexBuffer->ib != nullptr) 
   {
   
        glDrawElements(GL_TRIANGLES, vertexBuffer->ib->getCount(), GL_UNSIGNED_INT, 0);
        
    } else {
        // Handle the case where the mesh does not have any indices
        debugLog("No indices found for mesh");
    }
        eglSwapBuffers(s_display, s_surface);

}


void RenderSystem::initRenderSystem(ResourceManager &resourceManager)//later take in projection mode
{
    _resourceManager = &resourceManager;
    mainCamera = new ViewCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

    debugLog("---------------init render system----------------");
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