
#include "VertexArray.h"
#include <vector>
#include <lenny.h>
#include <ShaderInterface.h>
class ResourceManager
{
    private:
    std::vector<ShaderInterface *> *shaderArray;
    std::vector<VertexArray *> *vertexArrays;
    ResourceManager(){};
    ~ResourceManager();
    public:
    GLuint s_vao, s_vbo;
    void initResourceManager();
    std::vector<ShaderInterface *> *getShaderArray();
    std::vector<VertexArray *> *getVertexArray();
    static ResourceManager &getResourceManager();
    static void destroyResourceManager();
};