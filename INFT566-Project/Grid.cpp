#include "Grid.h"



Grid::Grid()
{
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);	m_projectionView = projection * view;
}


Grid::~Grid()
{
}

const glm::mat4 Grid::getProjectionView()
{
	return m_projectionView;
}

void Grid::setProjectionView(const glm::mat4 a_projectionView)
{
	m_projectionView = a_projectionView;
}

void Grid::startup()
{
	Gizmos::create();
}

void Grid::shutdown()
{
	Gizmos::destroy();
}

void Grid::update(float deltaTime)
{
	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1));

	glm::vec4 white(1); // All white Vector
	glm::vec4 black(0, 0, 0, 1); // Black Vector
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}
}

void Grid::draw()
{
	Gizmos::draw(m_projectionView);
}
