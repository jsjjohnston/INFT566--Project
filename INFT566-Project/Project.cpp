#include "Project.h"

Project::Project(): m_grid(nullptr)
{
	
}


Project::~Project()
{
	delete m_grid;
}

bool Project::startup()
{
	m_grid = new Grid();
#ifdef DEBUG
	m_flyCamera = new FlyCamera();
	m_flyCamera->setWindow(m_window);
	m_flyCamera->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_flyCamera->setPerspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
	m_grid->setProjectionView(m_flyCamera->getProjectionView());
#endif // DEBUG
	// Setup Time Manager singleton
	TimeManager::create();
	
	// Set Background Colour
	setClearColour(1.0f,0.25f,0.25f);
	clearScreen();

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

#ifdef DEBUG
	m_flyCamera->update(deltaTime);
#endif // DEBUG
}

void Project::draw()
{
	m_grid->draw();
}
