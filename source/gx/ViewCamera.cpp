#include <ViewCamera.h>


ViewCamera::ViewCamera(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, float width, float height)
{
    position = _position;
    rotation = _rotation;
    scale = _scale; 
    this->width = width;
    this->height = height;
}

void ViewCamera::Matrix(float fovDef, float nearPlane, float farPlane, ShaderMaterialInterface *shaderInterface, const char *uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::lookAt(position, position + orientaion, upVector);

    projection = glm::perspective(glm::radians(fovDef), (float)width / height, nearPlane, farPlane);
    glm::mat4 newView = projection * view;
    shaderInterface->SetUniformMat4F(uniform, newView);
}


void ViewCamera::Inputs(u32 currentInput)
{
    if (currentInput & HidNpadButton::HidNpadButton_Up) 
    {
		position += speed * orientaion;
	}
	if (currentInput  & HidNpadButton::HidNpadButton_Down)
	{
		position += speed * -glm::normalize(glm::cross(orientaion, upVector));
	}
	if (currentInput & HidNpadButton::HidNpadButton_Left)
	{
		position += speed * -orientaion;
	}
	if (currentInput & HidNpadButton::HidNpadButton_Right)
	{
		position += speed * glm::normalize(glm::cross(orientaion, upVector));
	}
	if (currentInput & HidNpadButton::HidNpadButton_B)
	{
		position += speed * upVector;
	}
	if (currentInput & HidNpadButton::HidNpadButton_L)
	{
		position += speed * -upVector;
	}
	if (currentInput & HidNpadButton::HidNpadButton_X)
	{
		speed = 0.4f;
	}
	else if (currentInput != HidNpadButton::HidNpadButton_X)
	{
		speed = 0.1f;
	}
}
