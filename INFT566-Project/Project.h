#pragma once
#include "Application.h"
#include "GLM\glm.hpp"
#include "GLM\fwd.hpp"
#include "Grid.h"
#include "Model.h"
#include "Glslprogram.h"
#include "Camera.h" //TODO check if this is still required

/*
	NOTE Ensure Header is Correct
*/
class Project :	public Application
{
public:
	Project();
	~Project();

	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

	void setUpFrameBuffer();
	void createFullScreenQuad();

protected:

private:
	Model* mdlder; //TODO Remove
	Grid* m_grid;
	GLSLProgram* phongProgram;
	GLSLProgram* postProgram;
	Camera* cam;

	unsigned int m_texture;
	unsigned int m_frameBufferObject;
	unsigned int m_frameBufferObjectTexture;
	unsigned int m_frameBufferObjectDepth;

	// For post Processing
	unsigned int m_vao;
	unsigned int m_vbo;
};

