#include <RenderSystem.h>
class GameManager
{
    private:
        bool _running;
        GameManager(bool running):  _running(running), _renderSystem(&RenderSystem::getRenderSystem()){};
        ~GameManager();
        

    public:
    void runGameLoop();
    void SceneInit();
    void GameLoop();
    bool Running();
    RenderSystem* _renderSystem;
    static GameManager& getGameManager();
    static void destroyGameManager();
};

