#include "objMesh.h"
#include <glad/glad.h>

ObjMesh::ObjMesh(MeshCreateInfo* createInfo) 
{

	std::vector<float> vertices = 
		util::load_model_from_file(createInfo->filename, createInfo->preTransform);
	vertexCount = int(vertices.size()) / 8;
    vertexArray = new VertexArray();
    vertexArray->Bind();
	vertexBuffer = new VertexBuffer();
    //VertexLit elem = 24 bytes
    //3, 2, 3 elm
  
    vertexBuffer->initVertexBuffer(&vertices.data()[0], (GLsizei)(vertices.size() * sizeof(float)), ShaderType::LIT, vertexCount);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    vertexArray->AddBuffer(*vertexBuffer,layout);


	//pos: 0, texcoord: 1, normal: 2

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}
ObjMesh::ObjMesh(const char* fileName, OBJ_MeshRenderer* meshRender) 
{

	std::vector<VertexLit> vertices = util::load_model_from_file_obj(fileName, glm::mat4(1.0f), meshRender);
	vertexCount = vertices.size();
    vertexArray = new VertexArray();
    vertexArray->Bind();
	vertexBuffer = new VertexBuffer();
    //VertexLit elem = 24 bytes
    //3, 2, 3 elm
  
    vertexBuffer->initVertexBuffer(vertices.data(), (vertices.size() * sizeof(VertexLit)), ShaderType::LIT, vertexCount);
    VertexBufferLayout layout;
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 3, GL_FALSE);
    layout.AddElement(GL_FLOAT, 2, GL_FALSE);
    vertexArray->AddBuffer(*vertexBuffer,layout);


	//pos: 0, texcoord: 1, normal: 2

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}
void ObjMesh::Draw()
{
    vertexArray->Bind();
    vertexBuffer->Bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void ObjMesh::UpdateMesh(Material* mat, glm::mat4 transform, glm::quat rotation, glm::vec3 scale, ViewCamera *mainCamera) 
{
    glm::quat rotationQuat = glm::quat(rotation);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);
    rot = glm::mat4_cast(rotationQuat);    
    sca = glm::scale(sca, scale); 
    glUseProgram(mat->shader->getShaderInterface()->getProgramHandle());
    glUniformMatrix4fv(glGetUniformLocation(mat->shader->getShaderInterface()->getProgramHandle(), "translation"), 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(glGetUniformLocation(mat->shader->getShaderInterface()->getProgramHandle(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(mat->shader->getShaderInterface()->getProgramHandle(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(mat->shader->getShaderInterface()->getProgramHandle(), "model"), 1, GL_FALSE, glm::value_ptr(transform));  
    mat->shader->SetUniform4F("u_LightColor",  1.0f, 1.0f, 1.0f, 1.0f);
    mat->shader->SetUniform3F("u_LightPos", 1, 1, 1);
    mat->shader->SetUniform3F("camPos", mainCamera->position.x, mainCamera->position.y, mainCamera->position.z);
    mainCamera->Matrix(mat->shader, "camMatrix");
   
    
  
}
ObjMesh::~ObjMesh() 
{
	vertexArray->~VertexArray();
    vertexBuffer->~VertexBuffer();
}