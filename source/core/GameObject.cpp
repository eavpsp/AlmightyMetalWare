#include "GameObject.h"
#include "../debug/debug.h"

#include <RenderSystem.h>
extern std::vector<GameObject *> *GameObjects;
extern std::vector<EngineObject *> *GraphicsObjects;
extern RenderSystem *gameRenderSystem;
/**
 * @brief Draws the game object's model
 *
 * This function is responsible for drawing the game object's model, if it has one.
 * It will bind the vertex array object, set the uniforms, and draw the model.
 *
 * @return None
 */

void GameObject::DrawMesh()
{
    //switch
    switch (objectModel->type)
    {
    case MeshType::OBJ:
            DrawOBJ();
        /* code */
        break;
    
    default:
        DrawGLTF();
        break;
    }
    onDraw();

}

void GameObject::UpdateMesh()
{
    switch (objectModel->type)
    {
        case MeshType::OBJ:

            UpdateOBJ();
            break;

        default:
        
            UpdateGLTF();
            break;
    }
}
//GLTF
void GameObject::UpdateGLTF()
{
    //send base object postion relative to meshes
    //get game model
    //start shader program
    //get vao
    //bind textures
    GLTF_MeshRenderer *meshRenderer = (GLTF_MeshRenderer*)objectModel;
    if(meshRenderer == nullptr )//has va?
    {
        debugLog("no model ");
        return;
    }
    else if(meshRenderer->mesh->vertexArray == nullptr ){
        debugLog("no va ");
        return;
    }
    else if(meshRenderer->mesh->meshes.size() == 0)
    {
        debugLog("no meshes ");
        return;
    }
    meshRenderer->mesh->vertexArray->Bind();

    for (int i = 0; i < meshRenderer->mesh->meshes.size(); i++)
    {
        //bind texture
       
        //add object translation scale and rotation to sa
        
        glUseProgram(material->shader->getShaderInterface()->getProgramHandle());
        //set uniforms
       
        if(meshRenderer->mesh->meshes.at(i).shaderType == ShaderType::LIT) //lit material
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
            glUniformMatrix4fv(glGetUniformLocation(m_mat->shader->getShaderInterface()->getProgramHandle(), "model"), 1, GL_FALSE, glm::value_ptr(trans));  
        
           
        }
        else if(meshRenderer->mesh->meshes.at(i).shaderType == ShaderType::LIGHT_OBJ) //light object material
        {
            LightObjectMaterials *m_mat = (LightObjectMaterials*)material;
            m_mat->UpdateModelShader(transform);
            
        }
        else if(meshRenderer->mesh->meshes.at(i).shaderType == ShaderType::TEX_UNLIT) //image material
        {
            ImageMaterial *m_mat = (ImageMaterial*)material;
            m_mat->UpdateModelShader(transform);

        }
        
        if( meshRenderer->mesh->meshes.at(i).textures.size() != 0)
        {
            for(int j = 0; j < meshRenderer->mesh->meshes.at(i).textures.size(); j++)
            {
            meshRenderer->mesh->meshes.at(i).textures.at(j).Bind(j);

            }

        }
        
           //
   
     if( meshRenderer->mesh->meshes.at(i).textures.size() != 0)
        {
            for(int j = 0; j < meshRenderer->mesh->meshes.at(i).textures.size(); j++)
            {
            meshRenderer->mesh->meshes.at(i).textures.at(j).UnBind();

            }

        }   
    meshRenderer->mesh->vertexBuffer->UnBind();
    meshRenderer->mesh->vertexArray->UnBind();
    
    }
   
    //draw vbo
    //with ibo
}

void GameObject::DrawGLTF()
{
    GLTF_MeshRenderer *meshRenderer = (GLTF_MeshRenderer*)objectModel;
    meshRenderer->Draw();
  
}

//OBJ
void GameObject::DrawOBJ()
{
    OBJ_MeshRenderer *meshRender = (OBJ_MeshRenderer*)objectModel;
    meshRender->Draw();
}


void GameObject::UpdateOBJ()
{
    OBJ_MeshRenderer *mesh = (OBJ_MeshRenderer*)objectModel;
    mesh->UpdateMesh(material,this, gameRenderSystem->mainCamera);       
    mesh->EnableTextures();

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