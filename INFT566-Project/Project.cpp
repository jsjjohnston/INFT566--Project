#include "Project.h"

Project::Project(): m_grid(nullptr)
{
	mdlder = new ModelLoader();
	program = new GLSLProgram();
	cam = new Camera();
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
	
	program->compileShader("myShader.vert");
	program->compileShader("myShader.frag");
	program->link();
	program->validate();
	program->use();
	
	glm::mat4 modelTransform = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	//program->setUniform("projectionViewWorldMatrix", projection * cam->getWorldToViewMatrix() * modelTransform);
	program->setUniform("modelTransform", modelTransform);
	program->setUniform("projection", projection);
	
	glm::vec4 ambientLight(0.1f,0.1f,0.1f,1.0f);
	program->setUniform("ambientLight", ambientLight);

	

	glm::vec3 lightPosition(0.0f,3.0f,0.0f);
	program->setUniform("lightPositionWorld", lightPosition);

	program->setUniform("modelToWorldTransformMatrix", modelTransform);

	mdlder->loadModel("soulspear.obj");

	cam->setWindow(m_window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // Only render triangles facing the Cam

	return true;
}

void Project::shutdown()
{

}

void Project::update(float deltaTime)
{
	//Clear Screen
	clearScreen();
	
	static float x = 0.0f;
	static float y = 0.0f;
	static float z = -10.0f;

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//x--;
		//y--;
		
		z--;
	}

	if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_PRESS)
	{
		//x--;
		//y--;

		z++;
	}

	glm::mat4 modelTransform = glm::translate(glm::vec3(x, y, z));// * glm::rotate(1.0f, glm::vec3(x,y,z));
	glm::mat4 fullFransform =	glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f) * 
								cam->getWorldToViewMatrix() * modelTransform;

	program->setUniform("modelToProjectionMatrix", fullFransform);
	program->setUniform("modelToWorldTransformMatrix", modelTransform);
	program->setUniform("eyePositionWorld", cam->getPosition());

	cam->update(deltaTime);

	m_grid->update(deltaTime);
}

void Project::draw()
{
	//m_grid->draw();
	mdlder->draw();
}
