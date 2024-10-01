#include "GameObject.h"
#include "../debug/debug.h"

/**
 * @brief Draws the game object's model
 *
 * This function is responsible for drawing the game object's model, if it has one.
 * It will bind the vertex array object, set the uniforms, and draw the model.
 *
 * @return None
 */
void GameObject::DrawObjectModel()
{
    //send base object postion relative to meshes
    //get game model
    //start shader program
    //get vao
    //bind textures
    if(objectModel == nullptr )//has va?
    {
        debugLog("no model ");
        return;
    }
    else if(objectModel->vertexArray == nullptr ){
        debugLog("no va ");
        return;
    }
    else if(objectModel->meshes.size() == 0)
    {
        debugLog("no meshes ");
        return;
    }
    objectModel->vertexArray->Bind();

    for (int i = 0; i < objectModel->meshes.size(); i++)
    {
        //add object translation scale and rotation to sa
        
        glUseProgram(material->materials->getShaderInterface()->getProgramHandle());
        //set uniforms
       
        if(objectModel->meshes.at(i).shaderType == ShaderType::LIT) //lit material
        {
            LitMaterial *m_mat = (LitMaterial*)material;
            m_mat->UpdateModelShader(transform);
            glm::mat4 trans = glm::mat4(1.0f);
            glm::mat4 rot = glm::mat4(1.0f);
            glm::mat4 sca = glm::mat4(1.0f);

            // Transform the matrices to their correct form
            trans = glm::translate(trans,position);
            glm::quat rotationQuat = glm::quat(rotation);
            rot = glm::mat4_cast(rotationQuat);    
            sca = glm::scale(sca, scale);

        
            // Push the matrices to the vertex shader
            glUniformMatrix4fv(glGetUniformLocation(m_mat->materials->getShaderInterface()->getProgramHandle(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(m_mat->materials->getShaderInterface()->getProgramHandle(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
            glUniformMatrix4fv(glGetUniformLocation(m_mat->materials->getShaderInterface()->getProgramHandle(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
            glUniformMatrix4fv(glGetUniformLocation(m_mat->materials->getShaderInterface()->getProgramHandle(), "model"), 1, GL_FALSE, glm::value_ptr(objectModel->matricesMeshes.at(i)));  
        
           
        }
        else if(objectModel->meshes.at(i).shaderType == ShaderType::LIGHT_OBJ) //light object material
        {
            LightObjectMaterials *m_mat = (LightObjectMaterials*)material;
            m_mat->UpdateModelShader(transform);
            
        }
        else if(objectModel->meshes.at(i).shaderType == ShaderType::TEX_UNLIT) //image material
        {
            ImageMaterial *m_mat = (ImageMaterial*)material;
            m_mat->UpdateModelShader(transform);

        }
        
        for (int j = 0; j < objectModel->meshes.at(i).textures.size(); j++)
        {
            objectModel->meshes.at(i).textures.at(j).Bind(j);
           
        }
    glDrawElements(GL_TRIANGLES, objectModel->vertexArray->buffersInArray.at(0).ib->getCount(), GL_UNSIGNED_INT, 0);
        
    objectModel->vertexArray->UnBind();
    
    }
   
    //draw vbo
    //with ibo
    onDraw();
}

void GameObject::AddChild(GameObject *child)
{
    children.push_back(child);
}

GameObject *GameObject::GetChild(int index)
{
    return children.at(index);
}

int GameObject::GetChildrenCount()
{
    return children.size();
}

void GameObject::SetParent(GameObject *i_parent)
{
    parent = i_parent;
}

GameObject *GameObject::GetParent()
{
    return parent;
}

void GameObject::onUpdate()
{
}

void GameObject::onDraw()
{
   
}
void GameObject::onInit()
{

}
void GameObject::onDestroy()
{

}
GameObject::GameObject(Material *mat, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, GameModel *gameModel)
{
    material = mat;
    position = _position;
    rotation = _rotation;
    scale = _scale;
    objectModel = gameModel;
    //should init transform as well
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, _scale);
    
}
 GameObject::~GameObject()
{
   
    onDestroy();
   delete objectModel;
   delete material;

}