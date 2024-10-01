#ifndef VIEW_CAMERA_H
#define VIEW_CAMERA_H
#include <EngineObject.h>
#include <ShaderMaterialInterface.h>
//Add camera functions for view frustrum and movement
class ViewCamera : public EngineObject
{
    private:

    public:
        glm::vec3 orientaion = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
        virtual void onUpdate();
        virtual void onDraw();
        virtual void onInit();
        virtual void onDestroy();
        ViewCamera(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, float width, float height);
        ~ViewCamera(){};
        float width, height;
        float speed = 0.1f;
        float sensitivity = 5.0f;  
        void Matrix(float fovDef, float nearPlane, float farPlane, ShaderMaterialInterface *shaderInterface, const char *uniform);
        void Inputs(u32 currentInput);
        void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
};


#endif