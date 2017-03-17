#pragma once
//C++
#include <iostream>
#include <string>

//Jay
#include "Camera.h"

//Other
#include "tiny_obj_loader.h"
#include "GLM\glm.hpp" // Math Lib
#include "gl_core_4_4.h" // OpenGL

/*
	NOTE Ensure Header is correct
	Author: Jay Johnston
	Discription: Singelton to manage models
*/

// Vertex of an OBJ
struct OBJVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	float u, v;
};

struct OpenGLInfo
{
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_faceCount;
};

class Model
{
public:
	Model();
	~Model();
	bool loadModel(const char* a_fileName);
	void update(float a_deltaTime);
	void draw();

	Camera* getCamera() const { return m_camera; };
	void setCamera(Camera* a_camera) { m_camera = a_camera; };
	GLFWwindow* getWindow() const { return m_window; };
	void setWindow(GLFWwindow* a_window) { m_window = a_window; };

private:
	std::vector<OpenGLInfo> m_glInfo;
	Camera* m_camera;
	GLFWwindow* m_window;
};

