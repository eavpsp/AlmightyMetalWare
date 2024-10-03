#include<RenderSystem.h>
#include<GameManager.h>

#include "../debug/debug.h"
#include <EngineLight.h>
#include <objMesh.h>

bool lightScene = false;
bool sceneStart = false;

PointLight *pointLight;

/**
 * @brief Renders a GameObject with the given material and lights.
 *
 * This is the main entry point for rendering a GameObject. It sets up the
 * camera and lighting uniforms and then calls the GameObject's DrawObjectModel()
 * function to render the object. The function also swaps the front and back
 * buffers so that the rendered frame is displayed on the screen.
 *
 * @param gameObject The GameObject to render.
 */


void RenderSystem::render(GameObject *gameObject)//send in program and vao id array
{
     if(!sceneStart)
    {
        
        //Create our lights
              sceneStart = true;
    }
 
        gameObject->material->shader->SetUniform4F("u_LightColor",  0.0f, 0.0f, 0.0f, 0.0f);
        gameObject->material->shader->SetUniform3F("u_LightPos", pointLight->position.x, pointLight->position.y, pointLight->position.z);
        //gameObject->material->shader->SetUniform3F("u_LightPos", mainCamera->position.x, mainCamera->position.y, mainCamera->position.z);
        pointLight->light_Material->shader->SetUniform4F("u_LightColor",  pointLight->lightColor.x, pointLight->lightColor.y, pointLight->lightColor.z, pointLight->lightColor.w);

       // glUseProgram(gameObject->material->shader->getShaderInterface()->getProgramHandle());
      //  gameObject->material->shader->SetUniform3F("camPos", mainCamera->position.x, mainCamera->position.y, mainCamera->position.z);
        //mainCamera->Matrix(gameObject->material->shader, "camMatrix");

        
        
}

void RenderSystem::RenderLights()
{
    if(!lightScene)
    {
        pointLight = new PointLight();
        glUseProgram(pointLight->light_Material->shader->getShaderInterface()->getProgramHandle());
        pointLight->transform = glm::translate(pointLight->transform, glm::vec3(5.0f, 0.0f, 0.0f));
         //Create our lights
        pointLight->light_Material->shader->SetUniformMat4F("model", pointLight->transform);
        pointLight->light_Material->shader->SetUniform4F("u_LightColor",  pointLight->lightColor.x, pointLight->lightColor.y, pointLight->lightColor.z, pointLight->lightColor.w);
        debugLog("Created Point Light");
        lightScene = true;
    }
    glUseProgram(pointLight->light_Material->shader->getShaderInterface()->getProgramHandle());
    pointLight->light_Material->shader->SetUniform3F("camPos", mainCamera->position.x, mainCamera->position.y, mainCamera->position.z);
    mainCamera->Matrix(pointLight->light_Material->shader, "camMatrix");
}
void RenderSystem::SwapBuffers()
{
     eglSwapBuffers(s_display, s_surface);
}

void RenderSystem::render(VertexBuffer *vertexBuffer)//2D
{

    //
        /* glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mainCamera->transform = glm::translate(glm::mat4(1.0f), mainCamera->position);  //Object A Position, Shader 
        {
            glm::mat4 mdlvMtx = ortho_projection * mainCamera->transform * glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f)); //mainCamera * model postition * projections = normalized device coordinates
            _resourceManager->_engineMaterials.getColorMaterial()->SetUniformMat4F("u_ModelViewMatrix", mdlvMtx);

            glUseProgram( _resourceManager->_engineMaterials.getColorMaterial()->getShaderInterface()->getProgramHandle());
            glBindVertexArray(_resourceManager->s_vao); 
            glDrawElements(GL_TRIANGLES, vertexBuffer->ib->getCount(), GL_UNSIGNED_INT, 0);

        }
       {
            glm::mat4 mdlvMtx = ortho_projection * mainCamera->transform * glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 100.0f, 0.0f));
             _resourceManager->_engineMaterials.getColorMaterial()->SetUniformMat4F("u_ModelViewMatrix", mdlvMtx);
            glUseProgram( _resourceManager->_engineMaterials.getColorMaterial()->getShaderInterface()->getProgramHandle());
            glBindVertexArray(_resourceManager->s_vao); 
            glDrawElements(GL_TRIANGLES, vertexBuffer->ib->getCount(), GL_UNSIGNED_INT, 0);
            
        }
        eglSwapBuffers(s_display, s_surface);*/
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




void RenderSystem::initRenderSystem(ResourceManager &resourceManager)//later take in projection mode
{
    _resourceManager = &resourceManager;
    mainCamera = new ViewCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    
    ortho_projection = glm::ortho(0.0f, SCREEN_WIDTH, 0.0f,SCREEN_HEIGHT, -1.0f, 1.0f);//left, right, bottom, top, near, far
        //
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