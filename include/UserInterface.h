#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>
namespace UI
{
    //Shapes
    //UI Draw Calls
    //Structs for UI Elements
    //UI Event Handling
    struct UIElement
    {
        std::string name;
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        bool visible;
        GLuint vao, vbo;
        //MW_Texture bgImage; //Eventually add this
        virtual void Update() = 0;
        virtual void Init() = 0;
        UIElement(){};
        virtual ~UIElement(){};
    };
    struct Panel : UIElement
    {
        void Render(glm::vec2 pos, glm::vec2 size, glm::vec4 color);//update to intake local vars
        void Update() override;
        void Init() override;
        std::vector<UIElement *> elements;
        Panel();
        ~Panel(){};
    };
    struct Button : UIElement
    {
        void Render(glm::vec2 pos, glm::vec2 size, glm::vec4 color);
        //MW_Texture bgImage;
        std::string text;
        bool pressed;
        void OnClick();
    };
    struct TextBox : UIElement
    {
        //MW_Texture bgImage;
        std::string text;
    };
}



#endif // USERINTERFACE_H
