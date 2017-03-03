#include "Camera.h"



Camera::Camera(): viewDirection(0.0f,0.0f,-1.0f), up(0.0f,1.0f,0.0f)
{
}


Camera::~Camera()
{
}

void Camera::mouseUpdate(const glm::vec2& newMousePos, const float a_deltaTime)
{
	glm::vec2 mouseDelta = newMousePos - oldMousePosition;
	const float ROTATIONAL_SPEED = 0.05f;
	// Check for major change in mouse Position
	// Stops change in mouse if it moves off the screen
	if (glm::length(mouseDelta) < 50.0f)
	{
		glm::vec3 rorateAround = glm::cross(viewDirection, up);
		glm::mat4 rotator = glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED * a_deltaTime, up) * glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED * a_deltaTime, rorateAround);
		
		viewDirection =  glm::mat3(rotator) * viewDirection;
		oldMousePosition = newMousePos;
	}
	else
	{
		oldMousePosition = newMousePos;
	}

}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position,position + viewDirection, up);
}

void Camera::update(float deltaTime)
{
	double xpos = 0, ypos = 0; //TODO look at how to use cast to floats
	glfwGetCursorPos(m_window, &xpos, &ypos);

	mouseUpdate(glm::vec2(xpos,ypos), deltaTime);
}
