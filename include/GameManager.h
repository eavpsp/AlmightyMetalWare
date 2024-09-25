#include <RenderSystem.h>

class GameManager
{
    private:
        bool _running;
        GameManager(bool running);
        ~GameManager();
    public:
    void runGameLoop();
    void SceneInit();
    void GameLoop();
    bool Running();
    RenderSystem *_renderSystem;
    ResourceManager *_resourceManager;
    static GameManager& getGameManager();
    static void destroyGameManager();
};

