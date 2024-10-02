#include "TestGameObject.h"
#include "../debug/debug.h"
void TestGameObject::onDraw()
{

}

void TestGameObject::onUpdate() 
{
    //test movement.. works!
   position += glm::vec3(0.01f, 0.01f, 0.01f);
   transform = glm::translate(transform, position);
}
void TestGameObject::onInit()
{
    

}

void TestGameObject::onDestroy()
{

}

