#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include <glad/glad.h>  // glad library (OpenGL loader)


//Add Binding and Unbinding
//Create Class for indicies
class IndexBuffer
{
	private:
		GLuint _indexexBufferID;
		GLuint _count; //num of indices elements
	public:
		void Bind(const GLvoid *data) const;
		void UnBind() const;
		inline unsigned int getCount() { return _count; }
		inline GLuint getBufferID() { return _indexexBufferID; }
		IndexBuffer(GLsizei count);
		IndexBuffer(){};
		~IndexBuffer();
};
#endif