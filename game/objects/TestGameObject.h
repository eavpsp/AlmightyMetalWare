#ifndef TESTGAMEOBJECT_H
#define TESTGAMEOBJECT_H
#include <GameObject.h>
extern std::vector<GameObject *> *GameObjects;

class TestGameObject : public GameObject
{
    public:
        void onDraw() override;
        void onUpdate() override;
        void onInit() override; 
        void onDestroy() override;
        TestGameObject(){};
        ~TestGameObject()
        {
            onDestroy();
        };
};

#endif