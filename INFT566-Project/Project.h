#pragma once
#include "Application.h"

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
};

