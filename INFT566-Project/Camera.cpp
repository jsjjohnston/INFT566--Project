#include "Camera.h"

#define MOVEMENT_SPEED 10.0f


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
	//Manage Mouse Movement
	double xpos = 0, ypos = 0; //TODO look at how to use cast to floats
	glfwGetCursorPos(m_window, &xpos, &ypos);

	mouseUpdate(glm::vec2(xpos,ypos), deltaTime);

	//Key press movment

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		moveForward(deltaTime);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		moveBackward(deltaTime);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		strafeLeft(deltaTime);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		strafeRight(deltaTime);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
	{
		moveUp(deltaTime);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
	{
		moveDown(deltaTime);
	}




	//TODO REMOVE switch (glfwGetKey(m_window, GLFW_KEY_SPACE))
	//{
	//case GLFW_KEY_W:
	//	break;
	//case GLFW_KEY_S:
	//	break;
	//case GLFW_KEY_A:
	//	break;
	//case GLFW_KEY_D:
	//	break;
	//case GLFW_KEY_R:
	//	break;
	//case GLFW_KEY_F:
	//	break;
	//default:
	//	break;
	//}
}

void Camera::moveForward(float a_deltaTime)
{
	position += MOVEMENT_SPEED * a_deltaTime * viewDirection;
}

void Camera::moveBackward(float a_deltaTime)
{
	position += -MOVEMENT_SPEED * a_deltaTime * viewDirection;
}

void Camera::strafeLeft(float a_deltaTime)
{

	glm::vec3 strafeDirection = glm::cross(viewDirection, up);
	position += MOVEMENT_SPEED * a_deltaTime * strafeDirection;

}

void Camera::strafeRight(float a_deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, up);
	position += -MOVEMENT_SPEED * a_deltaTime * strafeDirection;
}

void Camera::moveUp(float a_deltaTime)
{
	position += MOVEMENT_SPEED * a_deltaTime * up;
}

void Camera::moveDown(float a_deltaTime)
{
	position += -MOVEMENT_SPEED * a_deltaTime * up;
}
