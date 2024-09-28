#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H
#include <vector>
#include <glad/glad.h>



struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        return 0;
    };
};

class VertexBufferLayout
{
    private:
        /* data */
        std::vector<VertexBufferElement> _elements;
        unsigned int _stride;
    public:
        VertexBufferLayout(/* args */) : _stride(0) {};
        ~VertexBufferLayout();
        /// @brief 
        /// @param type 
        /// @param count 
        /// @param normalized 
        void AddElement(unsigned int type, unsigned int count, unsigned char normalized = GL_FALSE);

   
        inline const std::vector<VertexBufferElement> GetElements() const { return _elements; }   
        inline unsigned int GetStride() { return _stride; }
};

#endif