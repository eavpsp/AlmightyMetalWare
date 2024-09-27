
#include <glad/glad.h>  // glad library (OpenGL loader)


//Add Binding and Unbinding
//Create Class for indicies
class IndexBuffer
{
	private:
		GLuint _indexexBufferID;
		GLuint _count; //num of indices elements
	public:
		void Bind() const;
		void UnBind() const;
		inline unsigned int getCount() { return _count; }
		IndexBuffer(const GLvoid *data, GLsizei count);
		~IndexBuffer();
};
