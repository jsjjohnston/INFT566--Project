#pragma once
//C++
#include <iostream>
#include <string>

//Jay
#include "Camera.h"
#include "Glslprogram.h"

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
	void loadDiffuseTexture(const char* a_fileName);


	Camera* getCamera() const { return m_camera; };
	void setCamera(Camera* a_camera) { m_camera = a_camera; };

	GLFWwindow* getWindow() const { return m_window; };
	void setWindow(GLFWwindow* a_window) { m_window = a_window; };

	GLSLProgram* getProgram() const { return m_program; };
	void setProgram(GLSLProgram* a_program) { m_program = a_program; };

	glm::vec3 getPostion() const { return m_position; };
	void setPostion(glm::vec3 a_postion) { m_position = a_postion; };

private:
	std::vector<OpenGLInfo> m_glInfo;
	Camera* m_camera;
	GLFWwindow* m_window;
	GLSLProgram* m_program;

	unsigned int m_DiffuseTexture;

	glm::vec3 m_position;
	float m_rotation;
};

