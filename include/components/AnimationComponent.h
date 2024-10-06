#ifndef ANIMATIONCOMPONENT_H_
#define ANIMATIONCOMPONENT_H_


#include <vector>
#include <string>
#include <VertexArray.h>
#include <objLoader.h>
#include <map>
#include <glad/glad.h>
#include <GameObject.h>
#include "../debug/debug.h"

//store all obj files for anim
//get framerate
//playback animation in dynamic vao
//store strings for animations in resources to contruct animation file templates 
struct AnimationFile
{
    std::string animName;
    bool loop = false;
    float framerate;
    int frameCount = 0;
    std::vector<std::string> objFiles;

    AnimationFile(const char* name, bool loop, float framerate)
    {
        animName = name;
        this->loop = loop;
        this->framerate = framerate;
        
    };
    ~AnimationFile(){};
};//Files to Load for animation
struct AnimationFrame
{   
    std::vector<VertexLit> animationFrameVerts;
    AnimationFrame(){};
    ~AnimationFrame(){};
};//each mesh loaded is loaded as a frame
struct AnimationData
{
    std::string animName;
    bool loop = false;
    float framerate;
    std::vector<AnimationFrame *> animationFrames;
    AnimationData(){};
    ~AnimationData(){};
};//each frame is stored in animation data
struct AnimationArchive
{
    std::vector<AnimationFile *> animationFiles;
    AnimationArchive(){};
    ~AnimationArchive(){};
};//stores a pack of animation data


class AnimationComponent : public GameComponent//no blending until skeletal mesh
{
    private:
    //vao vbo
    VertexArray *vertexArray;
    VertexBuffer *vertexBuffer;
    bool isPlaying = false;
    int currentTime = 0;
    std::vector<std::string> _animations;
    std::map<std::string, AnimationData*> _animationDataMap;
    AnimationFrame currentFrame;
    AnimationData currentAnimation;
    int vertexCount = 0;
    OBJ_MeshRenderer *_meshRender;
    public:
        void PlayAnimation(std::string animName)
        {
            currentTime = 0;
            currentFrame = *_animationDataMap[animName]->animationFrames[currentTime];//reset frame
            currentAnimation = *_animationDataMap[animName];
           
            if(&currentFrame != NULL && &currentAnimation != NULL)
            {
                 isPlaying = true;
            }

        };
        void RunAnimation(); //must be in render loop
        void ComponentAddedCallback()
        {
            parentObject->hasAnimator = true;
        }
        void StopAnimation()
        {
            currentTime = 0;
            isPlaying = false;
        };
        void PauseAnimation()
        {
            isPlaying = false;
        };
        void ResumeAnimation()
        {
            isPlaying = true;
            RunAnimation();
        };
        bool IsPlaying()
        {
            return isPlaying;
        }

       
        AnimationComponent(AnimationArchive& archiveToLoad, OBJ_MeshRenderer *meshRender)
        {
            _meshRender = meshRender;
            _animationDataMap = std::map<std::string, AnimationData*>();
            _animations = std::vector<std::string>();
            debugLog("Archive Size: %d", archiveToLoad.animationFiles.size());
            for (auto& anim : archiveToLoad.animationFiles)//loop each file to load
            {
                AnimationData *animData = new AnimationData();//create animation data
                _animations.push_back(anim->animName);//store animation name
                animData->animName = anim->animName;
                animData->loop = anim->loop;
                //loop files to load
                debugLog("Frame Count: %d", anim->objFiles.size());
                for (int i = 0; i < anim->objFiles.size(); i++)
                {
                    //create animation frame
                    AnimationFrame *animationFrame = new AnimationFrame();
                    //load model
                    animationFrame->animationFrameVerts = util::load_model_from_file_obj(anim->objFiles[i].c_str(), parentObject->transform, meshRender);
                    //add frame to animation data
                    animData->animationFrames.push_back(animationFrame);
                    debugLog("Loaded Animation Frame: %s", anim->objFiles[i].c_str());
                }
                //add animation data to animations map
                _animationDataMap[anim->animName] = animData;
                }
                //create graphics buffer
                vertexCount = _animationDataMap[_animations[0]]->animationFrames[0]->animationFrameVerts.size();//get size from first animation object
                vertexArray = new VertexArray();
                vertexArray->Bind();
                vertexBuffer = new VertexBuffer();
                vertexBuffer->initVertexBufferDynamic((vertexCount* sizeof(VertexLit)));
                VertexBufferLayout layout;
                layout.AddElement(GL_FLOAT, 3, GL_FALSE);
                layout.AddElement(GL_FLOAT, 3, GL_FALSE);
                layout.AddElement(GL_FLOAT, 2, GL_FALSE);
                vertexArray->AddBuffer(*vertexBuffer,layout);
                glBindVertexArray(0);
        };
        ~AnimationComponent(){};
        void OnUpdate()
        {
            RunAnimation();
        };
        void SetParentObject(GameObject* obj) { parentObject = obj; };
};

#endif /* ANIMATIONCOMPONENT_H_ */
