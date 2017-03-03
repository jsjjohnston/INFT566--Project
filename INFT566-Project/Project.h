#pragma once
#include "Application.h"
#include "GLM\glm.hpp"
#include "GLM\fwd.hpp"
#include "Grid.h"
#include "ModelLoader.h"
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

protected:

private:
	ModelLoader* mdlder; //TODO Remove
	Grid* m_grid;
	GLSLProgram* program;
	Camera* cam;
};

