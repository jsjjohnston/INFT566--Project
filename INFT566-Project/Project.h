#pragma once
#include "Application.h"
#include "GLM\glm.hpp"
#include "GLM\fwd.hpp"
#include "Model.h"
#include "Glslprogram.h"
#include "Camera.h"

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
	Model* m_model;
	GLSLProgram* phongProgram;
	GLSLProgram* postProgram;

	GLSLProgram* postBoxBlur;
	GLSLProgram* postDistort;
	GLSLProgram* postExplosion;
	GLSLProgram* postImplosion;
	GLSLProgram* postEdgeDetection;
	GLSLProgram* postFog;
	GLSLProgram* postFuzz;
	GLSLProgram* postSimple;
	GLSLProgram* postThermal;
	GLSLProgram* postFade;

	Camera* m_cam;

	int m_postIndex;
	double timePressed;

	// For post Processing
	unsigned int m_texture;
	unsigned int m_frameBufferObject;
	unsigned int m_frameBufferObjectTexture;
	unsigned int m_frameBufferObjectDepth;

	unsigned int m_vao;
	unsigned int m_vbo;

	bool demoMode;
};

