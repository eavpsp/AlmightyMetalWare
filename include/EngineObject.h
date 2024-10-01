#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class EngineObject
{
    //private funcs onUpdate, onDraw onInit onDestroy
    public:
        EngineObject();
        virtual ~EngineObject(){};
        glm::vec3 position, rotation, scale;
        glm::mat4 transform;
        virtual void onUpdate() = 0;
        virtual void onDraw() = 0;
        virtual void onInit() = 0;
        virtual void onDestroy() = 0;
};


#endif
