#include "Project.h"

Project::Project(): m_grid(nullptr)
{
	mdlder = new ModelLoader();
}


Project::~Project()
{
	delete m_grid;
}

bool Project::startup()
{
	m_grid = new Grid();

	// Setup Time Manager singleton
	TimeManager::create();
	
	// Set Background Colour
	setClearColour(1.0f,0.25f,0.25f);
	clearScreen();

	mdlder->loadModel("./Models/Buddha.obj");

	return true;
}

void Project::shutdown()
{

}

void Project::update(float deltaTime)
{
	//Clear Screen
	clearScreen();

	m_grid->update(deltaTime);
}

void Project::draw()
{
	m_grid->draw();
	mdlder->draw();
}
