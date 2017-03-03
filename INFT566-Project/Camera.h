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

private:
	glm::vec3 viewDirection;
	glm::vec3 position;
	const glm::vec3 up;
	glm::vec2 oldMousePosition;

	GLFWwindow* m_window;
};

