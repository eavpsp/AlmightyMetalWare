#ifndef VIEW_CAMERA_H
#define VIEW_CAMERA_H
#define GLM_FORCE_PURE

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//Add camera functions for view frustrum and movement
class ViewCamera
{
    private:

    public:
        glm::vec3 position;
        ViewCamera(){};
        ~ViewCamera(){};
};


#endif