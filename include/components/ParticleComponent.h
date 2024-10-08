#ifndef PARTICLECOMPONENT_H_
#define PARTICLECOMPONENT_H_
#include <GameObject.h> 
#include <glm/glm.hpp>
#include <vector>
#include <VertexArray.h>
#include <mwmath.h>
#include <ScriptCallbacks.h>
#include <ResourceManager.h>
#include <RenderSystem.h>
#include <mwmath.h>
#include <objLoader.h>  
//hold vertex postions of quad, use gamefont code.
//hold particle lifetime
//store particle color
//store particle texture id
//always a rendered quad with a texture
//todo 3d particles
extern EngineCallBacks *engineCallBacks;
extern ResourceManager *gameResourceManager;
extern RenderSystem *gameRenderSystem;
enum ParticleType
{
    SPHERE, 
    CUBE,
    PLANE
};

struct Particle//individual particle data Custom Shader takes in Layout 0 POS, 1 COL, UNiform SIZE, 2 TEX
{//2d texture particle

    glm::mat4 transform;
    glm::vec3 position, prevPos, newPos, startPos;
    glm::vec3 velocity;
    float size;
    glm::vec4 color;
    float lifetime, currentLifetime;
    bool isAlive, doLoop;
    ParticleType particleType;//used to determine type of mesh data
    std::vector<ParticleVertexData> vertexData;//Mesh Data
    VertexArray *vertexArray;
    VertexBuffer *vertexBuffer;
    void RunParticle()
    {
           
        if (currentLifetime > 0)
        {
            currentLifetime -= 1.0f;//1 lifetime per frame
            prevPos = position;
            newPos = position + velocity;
            position = MW_Math::lerp(position, newPos, engineCallBacks->GetInterpolatedTickTime());
            glm::mat4 trans = glm::mat4(1.0f);
            glm::mat4 rot = glm::mat4(1.0f);
            glm::mat4 sca = glm::mat4(1.0f) * size;

            // Transform the matrices to their correct form
            trans = glm::translate(trans,position);
            glUniformMatrix4fv(glGetUniformLocation(gameResourceManager->_engineMaterials.getGet3DParticleFXMaterial()->shader->getShaderInterface()->getProgramHandle(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(gameResourceManager->_engineMaterials.getGet3DParticleFXMaterial()->shader->getShaderInterface()->getProgramHandle(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
            glUniformMatrix4fv(glGetUniformLocation(gameResourceManager->_engineMaterials.getGet3DParticleFXMaterial()->shader->getShaderInterface()->getProgramHandle(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
            glUniformMatrix4fv(glGetUniformLocation(gameResourceManager->_engineMaterials.getGet3DParticleFXMaterial()->shader->getShaderInterface()->getProgramHandle(), "model"), 1, GL_FALSE, glm::value_ptr(trans));  
            gameRenderSystem->mainCamera->Matrix(gameResourceManager->_engineMaterials.getGet3DParticleFXMaterial()->shader, "camMatrix");
            glUseProgram(gameResourceManager->_engineMaterials.getGet3DParticleFXMaterial()->shader->getShaderInterface()->getProgramHandle());
            vertexArray->Bind();
            glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
          
        }
        else if(currentLifetime <= 0)
        {
            position = startPos;
            currentLifetime = lifetime;
        }
       
    };

    Particle(ParticleType type, glm::vec3 velocity, float lifetime, glm::vec4 color, float size)
    {
        currentLifetime = lifetime;
        this->velocity = velocity;
        this->color = color;
        this->size = size;
        this->particleType = type;
        startPos = position;
        switch (this->particleType)
        {
            case CUBE:
                vertexData = util::load_particle_from_file_obj("romfs:/models/prim/cube.obj", color);
                break;
            case SPHERE:
                vertexData = util::load_particle_from_file_obj("romfs:/models/prim/sphere.obj", color);
                break;
            
            default: //plane
                vertexData = util::load_particle_from_file_obj("romfs:/models/prim/plane.obj", color);
                break;
        }
        vertexArray = new VertexArray();
        vertexBuffer = new VertexBuffer();
        vertexArray->Bind();
        vertexBuffer->initVertexBuffer(vertexData.data(), vertexData.size() * sizeof(ParticleVertexData), ShaderType::LIT, vertexData.size());
        VertexBufferLayout particleVertexDataLayout;
        particleVertexDataLayout.AddElement(GL_FLOAT, 3, GL_FALSE);//position
        particleVertexDataLayout.AddElement(GL_FLOAT, 4, GL_FALSE);//color
        vertexArray->AddBuffer(*vertexBuffer, particleVertexDataLayout);
        vertexBuffer->UnBind();
        vertexArray->UnBind();
    };
    Particle(){};
    ~Particle(){};

};
struct ParticleFX//particle data bunch/ vector used to manipulate each individual particle
{
   
    
    std::vector<Particle> particles;


    void RenderParticles()
    {
        UpdateParticles();
       
    };
    void AddParticle(Particle p)
    {
        particles.push_back(p);
      
    };
    void UpdateParticles()
    {
        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].RunParticle();
        }
    };//RunParticle() on each particle
    ParticleFX(int numOfParticles, glm::vec4 particleColors, float radius, float lifeTimeInSeconds)
    {
     
        for (int i = 0; i < numOfParticles; i++)
        {   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            Particle particle = Particle(ParticleType::SPHERE, up, lifeTimeInSeconds * (TARGET_FPS), particleColors, 1.0f);
            particle.isAlive = true;
            particle.doLoop = true;
            particle.position = glm::vec3(MW_Math::Random(-radius, radius), 0.0f, MW_Math::Random(-radius, radius));
            particles.push_back(particle);
        }

    };
    ~ParticleFX(){};
    

};
class ParticleComponent : public GameComponent//system used to control particle fx
{   

    ParticleFX *particleFXs;
    bool isPlaying;
    public:
        void PlayParticleFX()
        {
            isPlaying = true;
        };
        void RenderParticles()
        {
            particleFXs->RenderParticles();
        }
        void StopParticleFX()
        {
            isPlaying = false;
        };
        bool IsPlaying() { return isPlaying; }  
        void OnUpdate() override
        {
           return;
            
        };
        void ComponentAddedCallback() override
        {
            parentObject->hasParticleFX = true;
            parentObject->renderMesh = false;
            PlayParticleFX();
        };
        void SetParentObject(GameObject* obj) { parentObject = obj; }
        bool isActive = true;
        ParticleComponent(int numOfParticles, glm::vec4 particleColors, float radius, float lifeTimeInSeconds)
        {
            particleFXs = new ParticleFX(numOfParticles, particleColors, radius, lifeTimeInSeconds);
        };
        ~ParticleComponent(){};
};


#endif /* PARTICLECOMPONENT_H_ */
