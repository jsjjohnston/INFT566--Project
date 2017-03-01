#pragma once
#include "Cameras.h"
#include "GLFW\glfw3.h"

class FlyCamera :
	public Cameras
{
public:
	FlyCamera();
	~FlyCamera();

	void setWindow(GLFWwindow* a_window);

	GLFWwindow* getWindow() const;
	
	virtual void update(float a_deltaTime);

protected:

private:
	float m_speed;
	glm::vec3 m_up;
	GLFWwindow* m_window;
};

