#include <ViewCamera.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../debug/debug.h"
#include <GameObject.h>
#include <mwmath.h>
#include <ScriptCallbacks.h>
extern std::vector<ViewCamera *> *CameraObjects;
extern EngineCallBacks *engineCallBacks;
void ViewCamera::onInit()
{
}

void ViewCamera::onDestroy()
{
}

void ViewCamera::onDraw()
{
}

void ViewCamera::onUpdate()
{

	updateMatrix(45.0f, 0.1f, 100.0f);
	
}

/**
 * @brief Constructs a ViewCamera.
 *
 * The ViewCamera is a special type of EngineObject that handles the camera and view matrix for the game.
 *
 * @param _position The position of the camera.
 * @param _rotation The rotation of the camera.
 * @param _scale The scale of the camera.
 * @param width The width of the screen.
 * @param height The height of the screen.
 */
ViewCamera::ViewCamera(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, float width, float height)
{
	
    position = _position;
    rotation = _rotation;
    scale = _scale; 
    this->width = width;
    this->height = height;
	CameraObjects->push_back(this);
}

void ViewCamera::Matrix(ShaderMaterialInterface *shaderInterface, const char *uniform)
{
   
    glUniformMatrix4fv(glGetUniformLocation(shaderInterface->getShaderInterface()->getProgramHandle(), uniform), 1, GL_FALSE, glm::value_ptr(transform));
}

void ViewCamera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	glm::vec3 Orientation = glm::vec3(orientaion.x, orientaion.y, orientaion.z);
	glm::vec3 up = glm::vec3(upVector.x, upVector.y, upVector.z);
	view = glm::lookAt(position, position + Orientation, up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	transform = projection * view;
	
}

//add rotation
void ViewCamera::Inputs(u32 currentInput)
{
	//debugLog("reading input");
	prevPos = position;
    if (currentInput & HidNpadButton::HidNpadButton_Up) 
    {
		glm::vec3 newPos = prevPos + speed * orientaion;
		position = MW_Math::lerp(prevPos, newPos, engineCallBacks->GetInterpolatedTickTime());
	}
	if (currentInput  & HidNpadButton::HidNpadButton_Left)
	{

		glm::vec3 newPos = prevPos += speed * -glm::normalize(glm::cross(orientaion, upVector));
		position = MW_Math::lerp(prevPos, newPos, engineCallBacks->GetInterpolatedTickTime());

	}
	if (currentInput & HidNpadButton::HidNpadButton_Down)
	{
		glm::vec3 newPos  = prevPos += speed * -orientaion;
		position = MW_Math::lerp(prevPos, newPos, engineCallBacks->GetInterpolatedTickTime());

	}
	if (currentInput & HidNpadButton::HidNpadButton_Right)
	{
		glm::vec3 newPos = prevPos += speed * glm::normalize(glm::cross(orientaion, upVector));
		position = MW_Math::lerp(prevPos, newPos, engineCallBacks->GetInterpolatedTickTime());

	}
	if (currentInput & HidNpadButton::HidNpadButton_R)
	{
		glm::vec3 newPos = prevPos += speed * upVector;
		position = MW_Math::lerp(prevPos, newPos, engineCallBacks->GetInterpolatedTickTime());

	}
	if (currentInput & HidNpadButton::HidNpadButton_L)
	{
		glm::vec3 newPos = prevPos += speed * -upVector;
		position = MW_Math::lerp(prevPos, newPos, engineCallBacks->GetInterpolatedTickTime());

	}
	if (currentInput & HidNpadButton::HidNpadButton_X)
	{
		speed = 0.4f;
	}
	else if (currentInput != HidNpadButton::HidNpadButton_X)
	{
		speed = 0.1f;
	}
	/*
	    HidNpadButton_StickLLeft    = BITL(16), ///< Left Stick pseudo-button when moved Left
		HidNpadButton_StickLUp      = BITL(17), ///< Left Stick pseudo-button when moved Up
		HidNpadButton_StickLRight   = BITL(18), ///< Left Stick pseudo-button when moved Right
		HidNpadButton_StickLDown    = BITL(19), ///< Left Stick pseudo-button when moved Down
		HidNpadButton_StickRLeft    = BITL(20), ///< Right Stick pseudo-button when moved Left
		HidNpadButton_StickRUp      = BITL(21), ///< Right Stick pseudo-button when moved Up
		HidNpadButton_StickRRight   = BITL(22), ///< Right Stick pseudo-button when moved Right
		HidNpadButton_StickRDown    = BITL(23), ///< Right Stick pseudo-button when moved Left

	*/
	// Left stick

	float leftStickX = currentInput & HidNpadButton::HidNpadButton_StickLLeft ? -1.0f : (currentInput & HidNpadButton::HidNpadButton_StickLRight ? 1.0f : 0.0f);
	float leftStickY = currentInput & HidNpadButton::HidNpadButton_StickLUp ? 1.0f : (currentInput & HidNpadButton::HidNpadButton_StickLDown ? -1.0f : 0.0f);
	float rightStickX = currentInput & HidNpadButton::HidNpadButton_StickRLeft ? -1.0f : (currentInput & HidNpadButton::HidNpadButton_StickRRight ? 1.0f : 0.0f);
	float rightStickY = currentInput & HidNpadButton::HidNpadButton_StickRUp ? 1.0f : (currentInput & HidNpadButton::HidNpadButton_StickRDown ? -1.0f : 0.0f);
	if (leftStickX != 0.0f)//horizontal -left right
	{
		position += speed * ( leftStickX * glm::normalize(glm::cross(orientaion, upVector)));
	}
	if(leftStickY != 0.0f)//vertical-forward and backward
	{
		position += speed * (leftStickY * orientaion);

	}
	
	// Right stick

	if (rightStickX != 0.0f || rightStickY != 0.0f)
	{

		float angleX = (rightStickX * sensitivity * 0.01f);
		float angleY = (rightStickY * sensitivity * 0.01f);

		

		glm::quat rotationX = glm::angleAxis(angleX, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat rotationY = glm::angleAxis(angleY, glm::vec3(1.0f, 0.0f, 0.0f));

		glm::quat totalRotation = rotationX * rotationY;
		orientaion = glm::normalize(glm::vec3(totalRotation * glm::vec4(orientaion, 0.0f)));

	

	}

}
