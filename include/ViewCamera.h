#ifndef VIEW_CAMERA_H
#define VIEW_CAMERA_H
#include <EngineObject.h>
//Add camera functions for view frustrum and movement
class ViewCamera : public EngineObject
{
    private:

    public:
        ViewCamera(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
        ~ViewCamera(){};
};


#endif