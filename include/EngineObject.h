#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <typeinfo>
#include <vector>
class EngineObject
{
    //private funcs onUpdate, onDraw onInit onDestroy
    //implement component handling
    private:

        virtual void onInit() = 0;
        virtual void onDestroy() = 0;
        template <typename T>
        const char* get_type_name() {
            return typeid(T).name();
        }   
    public:
        virtual void onUpdate() = 0;
        virtual void onDraw() = 0;
        EngineObject();
        virtual ~EngineObject(){};
        glm::vec3 position, scale;
        glm::quat rotation;
        glm::mat4 transform;
        std::string name;
        
};


#endif
