#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <glad/glad.h>
#include <GameObject.h>
struct SceneSkybox
{
    public:
    GLuint cubemapTexture, skyboxVAO, skyboxVBO, skyboxEBO;
    int vertexCount;;
    SkyBoxMaterial *skyboxMat;
    void RenderSkybox();
    SceneSkybox();//take in enum for type of skybox
    ~SceneSkybox();
};
class GameScene //holds basic data for each game scene
{
    public:
    glm::vec4 sceneColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    SceneSkybox *skybox;
    GameScene(glm::vec4 in_sceneColor, SceneSkybox *in_skybox);
    ~GameScene();
};
//Levels with IDs for objects
//Objects file loc and ID stored in resource manager

#endif /* GAME_SCENE_H_ */

