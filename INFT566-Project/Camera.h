#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include "GLFW\glfw3.h"
class Camera
{
public:
	Camera();
	~Camera();
	void mouseUpdate(const glm::vec2& newMousePos, const float a_deltaTime);
	glm::mat4 getWorldToViewMatrix() const;

	void setWindow(GLFWwindow* a_window) { m_window = a_window; };
	GLFWwindow* getWindow() const { return m_window; };

	void update(float deltaTime);

	glm::vec3 getPosition() const { return position; };

	void setOriginalMousePos() 
	{
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		orignalMousePosition = glm::vec2(x, y);
	}


private:
	glm::vec3 viewDirection;
	glm::vec3 position;
	const glm::vec3 up;
	glm::vec2 orignalMousePosition;

	void moveForward(float a_deltaTime);
	void moveBackward(float a_deltaTime);
	void strafeLeft(float a_deltaTime);
	void strafeRight(float a_deltaTime);
	void moveUp(float a_deltaTime);
	void moveDown(float a_deltaTime);

	GLFWwindow* m_window;
};

