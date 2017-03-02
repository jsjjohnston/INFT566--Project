#pragma once
#include "tiny_obj_loader.h"
#include <iostream>
#include <string>
#include "GLM\glm.hpp" // Math Lib
#include "gl_core_4_4.h" // OpenGL

/*
	NOTE Ensure Headder is correct
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

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	bool loadModel(const char* a_fileName);
	void draw();

private:
	std::vector<OpenGLInfo> m_glInfo;
};

