#include "Project.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

Project::Project(): m_grid(nullptr)
{
	mdlder = new Model();
	phongProgram = new GLSLProgram();
	cam = new Camera();

	postProgram = new GLSLProgram();
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
	
	// Image Data //TODO Get [Texturing] Working
	int imageWidth = 0;
	int imageHeight = 0;
	int imageFormat = 0;

	// Get Image Data //TODO Get [Texturing] Working
	unsigned char* data = stbi_load("soulspear_diffuse.tga", &imageWidth, &imageHeight, &imageFormat, STBI_default);

	// Load Image data on to the GFX card //TODO Get [Texturing] Working
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,	0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data); // Free Image Data
	
	// Compile Phong Shaders
	phongProgram->compileShader("myShader.vert");
	phongProgram->compileShader("phong.frag");
	//phongProgram->compileShader("texture.frag");
	phongProgram->link();
	phongProgram->validate();
	phongProgram->use();
	
	// Compile Post Processing Shaders
	postProgram->compileShader("post.vert");
	postProgram->compileShader("post.frag");
	postProgram->link();
	postProgram->validate();



	cam->setWindow(m_window);
	cam->setProgram(phongProgram);
	cam->setOriginalMousePos();
	
	mdlder->loadModel("soulspear.obj");
	mdlder->setProgram(phongProgram);
	mdlder->setCamera(cam);
	mdlder->setWindow(m_window);
	mdlder->setPostion(glm::vec3(0, 0, -15));

	setUpFrameBuffer();
	createFullScreenQuad();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // Only render triangles facing the Cam

	return true;
}

void Project::shutdown()
{

}

void Project::update(float deltaTime)
{
	phongProgram->setUniform("lightPositionWorld", glm::vec3(0,3,-1)); // Light Direction
	phongProgram->setUniform("ambientLight", glm::vec4(0.05f, 0.05f, 0.05f, 1.0f));

	cam->update(deltaTime);

	//TODO Get [Texturing] Working
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	int loc = glGetUniformLocation(phongProgram->getHandle(), "diffuse");
	glUniform1i(loc, 0);


	mdlder->update(deltaTime);
	m_grid->update(deltaTime);
}

void Project::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);
	glViewport(0, 0, getWindowWidth(), getWindowHeight());
	
	// clear the target
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	clearScreen();
	
	//phongProgram->use();
	mdlder->draw();
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, getWindowWidth(), getWindowHeight());
	
	clearScreen();

	postProgram->use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferObjectTexture);
	
	int loc = glGetUniformLocation(phongProgram->getHandle(), "target");
	glUniform1i(loc, 1);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	phongProgram->use();
}

void Project::setUpFrameBuffer()
{
	glGenFramebuffers(1, &m_frameBufferObject); //  Generate framebuffer object names
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject); // Bind a framebuffer to a framebuffer target

	// Craete a new Texture
	glGenTextures(1,&m_frameBufferObjectTexture); // Generate texture names
	glBindTexture(GL_TEXTURE_2D, m_frameBufferObjectTexture); // Bind a named texture to a texturing target
	
	/*
		Simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
		https://www.khronos.org/opengl/wiki/GLAPI/glTexStorage2D
	*/
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, getWindowWidth(), getWindowHeight());
	
	/*
		Set texture parameters
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_frameBufferObjectTexture, 0);

	glGenRenderbuffers(1, &m_frameBufferObjectDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_frameBufferObjectDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, getWindowWidth(), getWindowHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, m_frameBufferObjectDepth);
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Project::createFullScreenQuad()
{
	glm::vec2 halfTexel = 1.0f / glm::vec2(getWindowWidth(), getWindowHeight()) * 0.5f;

	float vertexData[] = {
		-1, -1, 0, 1, halfTexel.x, halfTexel.y,
		1, 1, 0, 1, 1 - halfTexel.x, 1 - halfTexel.y,
		-1, 1, 0, 1, halfTexel.x, 1 - halfTexel.y,
		-1, -1, 0, 1, halfTexel.x, halfTexel.y,
		1, -1, 0, 1, 1 - halfTexel.x, halfTexel.y,
		1, 1, 0, 1, 1 - halfTexel.x, 1 - halfTexel.y,
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 6, vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,	sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,	sizeof(float) * 6, ((char*)0) + 16);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
