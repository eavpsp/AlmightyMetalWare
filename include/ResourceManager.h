
#include<VertexBuffer.h>
#include <vector>
class ResourceManager
{
    private:
    std::vector<ShaderInterface *> *shaderArray;
    std::vector<VertexBuffer *> *vertexBufferArray;
    ResourceManager(){};
    ~ResourceManager();
    VertexBuffer *_vertexBuffer;
    public:
    void initResourceManager();
    std::vector<ShaderInterface *> *getShaderArray();
    std::vector<VertexBuffer *> *getVertexBufferArray();
    static ResourceManager &getResourceManager();
    static void destroyResourceManager();
};