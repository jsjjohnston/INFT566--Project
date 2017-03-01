#pragma once
#include "Application.h"
#include "GLM\glm.hpp"
#include "GLM\fwd.hpp"
#include "Grid.h"

#ifdef DEBUG
	#include "FlyCamera.h"
#endif // DEBUG

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
#ifdef DEBUG
	FlyCamera* m_flyCamera;
#endif // DEBUG

	Grid* m_grid;
};

