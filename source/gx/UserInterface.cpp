#include <UserInterface.h>
#include <ResourceManager.h>
extern ResourceManager *gameResourceManager;
UI::Panel::Panel()
{
    //Creates the data to load into the vao and vbo
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}
void UI::Panel::Render(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{
    //Creates a quad from inputs to act as a ui panel
        glm::vec2 halfSize = size / 2.0f;
        GLfloat vertices[4][4] =
        {
            {pos.x - halfSize.x, pos.y + halfSize.y,  0.0f, 1.0f},
            {pos.x + halfSize.x, pos.y + halfSize.y,  1.0f, 1.0f},
            {pos.x + halfSize.x, pos.y - halfSize.y,  1.0f, 0.0f},
            {pos.x - halfSize.x, pos.y - halfSize.y,  0.0f, 0.0f}
        };


        glUseProgram(gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->getShaderInterface()->getProgramHandle());
        glUniform3f(glGetUniformLocation(gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->getShaderInterface()->getProgramHandle(), "textColor"), color.x, color.y, color.z);
   
        //VAO VBO and EBO
      
        glBindVertexArray(vao);
          // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

}

void UI::Panel::Update()
{

}

void UI::Panel::Init()
{

}
