#include "GameObject.h"
#include "../debug/debug.h"
extern std::vector<GameObject *> *GameObjects;
extern std::vector<EngineObject *> *GraphicsObjects;
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
        
        glUseProgram(material->shader->getShaderInterface()->getProgramHandle());
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
            glUniformMatrix4fv(glGetUniformLocation(m_mat->shader->getShaderInterface()->getProgramHandle(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(m_mat->shader->getShaderInterface()->getProgramHandle(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
            glUniformMatrix4fv(glGetUniformLocation(m_mat->shader->getShaderInterface()->getProgramHandle(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
            glUniformMatrix4fv(glGetUniformLocation(m_mat->shader->getShaderInterface()->getProgramHandle(), "model"), 1, GL_FALSE, glm::value_ptr(objectModel->matricesMeshes.at(i)));  
        
           
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
        
        if( objectModel->meshes.at(i).textures.size() != 0)
        {
            objectModel->meshes.at(i).textures.at(i).Bind(i);

        }
        
           //
        
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

void GameObject::RegisterObject()
{
    
    GameObjects->push_back(this);
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

GameObject::GameObject()
{
    RegisterObject();
    
};
 GameObject::~GameObject()
{
   
    delete objectModel;
    delete material;

}