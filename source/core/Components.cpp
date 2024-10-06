#include<BPhysics.h>
#include<AnimationComponent.h>
#include <ResourceManager.h>
extern ResourceManager *gameResourceManager;

/*****Animations */
 void AnimationComponent::RunAnimation() //must be in render loop
        {
            if(!isPlaying)
            {
                return;
            }
            //check if renderMesh is enable for parentObject
           
            //cycle animation frames

            vertexArray->Bind();
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getVertexBufferID());
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(VertexLit), currentFrame.animationFrameVerts.data()); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // draw frame
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
            //update frame
            currentTime = (currentTime + 1) % currentAnimation.animationFrames.size();
            if (currentTime == 0) { // we've wrapped around to the start, so we've finished playing
                if (currentAnimation.loop) { // do we loop?
                    // do nothing, we've already wrapped around to the start
                } else {
                    isPlaying = false;
                    //remove this from animationcomponents vector
                    
                }
            }
            currentFrame = *_animationDataMap[currentAnimation.animName]->animationFrames[currentTime];//reset frame

        }



/*****Bullet Physics   */
#include "BPhysics.h"

void BPhysicsComponent::ComponentAddedCallback()
{
    return;

}