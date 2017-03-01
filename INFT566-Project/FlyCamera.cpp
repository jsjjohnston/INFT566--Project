#include "FlyCamera.h"
#include <iostream>



FlyCamera::FlyCamera() : m_window(nullptr), m_up(0,1,0), m_speed(2.00f)
{
		
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::setWindow(GLFWwindow * a_window)
{
	m_window = a_window;
}

GLFWwindow * FlyCamera::getWindow() const
{
	return m_window;
}

void FlyCamera::update(float a_deltaTime)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		setPosition(glm::vec3(0, 0, -1));
	}

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		setPosition(glm::vec3(0, 0, 1));
	}

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		setPosition(glm::vec3(-1, 0, 0));
	}

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		setPosition(glm::vec3(1, 0, 0));
	}

	if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		setPosition(glm::vec3(0, 1, 0));
	}

	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
	{
		setPosition(glm::vec3(0, -1, 0));
	}

	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rotate(glm::vec3(1,0,0),a_deltaTime * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rotate(glm::vec3(-1, 0, 0),a_deltaTime * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rotate(glm::vec3(0, -1, 0), a_deltaTime * m_speed);
	}

	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rotate(glm::vec3(0, 1, 0), a_deltaTime * m_speed);
	}

	double* currentCusorPosX = new double();
	double* currentCusorPosY = new double();

	glfwGetCursorPos(m_window, currentCusorPosX, currentCusorPosY);

	if ((*currentCusorPosX) > m_previousCusorPosX - 20)
	{
		rotate(glm::vec3(viewTransform * glm::vec4(0, -1, 0, 0)), a_deltaTime * m_speed);
		glfwSetCursorPos(m_window, m_previousCusorPosX, m_previousCusorPosY);
		//m_previousCusorPosX = (*currentCusorPosX);
	}

	if ((*currentCusorPosX) < m_previousCusorPosX + 20)
	{
		rotate(glm::vec3(viewTransform * glm::vec4(0, 1, 0,0)), a_deltaTime * m_speed);
		glfwSetCursorPos(m_window, m_previousCusorPosX, m_previousCusorPosY);
		//m_previousCusorPosX = (*currentCusorPosX);
	}

	if ((*currentCusorPosY) < m_previousCusorPosY - 20)
	{
		rotate(glm::vec3(-1, 0, 0), a_deltaTime * m_speed);
		glfwSetCursorPos(m_window, m_previousCusorPosX, m_previousCusorPosY);
		//m_previousCusorPosY = (*currentCusorPosY);	
	}

	if ((*currentCusorPosY) > m_previousCusorPosY + 20)
	{
		rotate(glm::vec3(1, 0, 0), a_deltaTime * m_speed);
		glfwSetCursorPos(m_window, m_previousCusorPosX, m_previousCusorPosY);
		//m_previousCusorPosY = (*currentCusorPosY);
	}

	//system("cls");
	//std::cout << "Current\t\tx: [" << *currentCusorPosX << "] y: [" << *currentCusorPosY << "]" << std::endl;
	//std::cout << "Previous\tx: [" << m_previousCusorPosX << "] y: [" << m_previousCusorPosY << "]" << std::endl;
	//std::cout << "DeltaTime\tx: [" << a_deltaTime << "]" << std::endl;
}