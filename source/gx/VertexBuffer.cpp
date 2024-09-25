#include "VertexBuffer.h"



void VertexBuffer::renderVertexBuffer()
{
 
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, _count);
}

void VertexBuffer::configureVertexAttributes()
{
    if(shader->get_aPositionVertex() != -1)
    {
        glVertexAttribPointer(shader->get_aPositionVertex(), 3, GL_FLOAT, GL_FALSE, _stride, NULL);//explain the type of data
        glEnableVertexAttribArray(shader->get_aPositionVertex());//Enable the pointer
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }
}

GLuint VertexBuffer::getVertexBufferID()
{
    return _vertexBufferID;
}

ShaderInterface *VertexBuffer::getShader()
{
    return shader;
}


VertexBuffer::VertexBuffer(const GLvoid *data, GLsizei size, GLenum mode, GLsizei count, GLsizei stride, ShaderInterface *shader, void *offsetPositon, void *offsetNormal) 
: shader(shader),_mode(mode),_count(count), _stride(stride)
{
    GLint s_program = shader->getProgramHandle();
    loc_mdlvMtx = glGetUniformLocation(s_program, "mdlvMtx");
    loc_projMtx = glGetUniformLocation(s_program, "projMtx");
    loc_lightPos = glGetUniformLocation(s_program, "lightPos");
    loc_ambient = glGetUniformLocation(s_program, "ambient");
    loc_diffuse = glGetUniformLocation(s_program, "diffuse");
    loc_specular = glGetUniformLocation(s_program, "specular");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &_vertexBufferID);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, count, offsetPositon);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, count, offsetNormal);
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    glUseProgram(s_program);
    auto projMtx = glm::perspective(40.0f*TAU/360.0f, 1280.0f/720.0f, 0.01f, 1000.0f);
    glUniformMatrix4fv(loc_projMtx, 1, GL_FALSE, glm::value_ptr(projMtx));
    glUniform4f(loc_lightPos, 0.0f, 0.0f, -0.5f, 1.0f);
    glUniform3f(loc_ambient, 0.1f, 0.1f, 0.1f);
    glUniform3f(loc_diffuse, 0.4f, 0.4f, 0.4f);
    glUniform4f(loc_specular, 0.5f, 0.5f, 0.5f, 20.0f);
    glm::mat4 mdlvMtx{1.0};
    mdlvMtx = glm::translate(mdlvMtx, glm::vec3{0.0f, 0.0f, -10.0f});
    mdlvMtx = glm::scale(mdlvMtx, glm::vec3{1.0f});
    mdlvMtx = glm::rotate(mdlvMtx, 15.0f, glm::vec3{0.0f, 10.0f, 0.0f});

    glUniformMatrix4fv(loc_mdlvMtx, 1, GL_FALSE, glm::value_ptr(mdlvMtx));
}


VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &_vertexBufferID);
    _vertexBufferID = 0;
}
