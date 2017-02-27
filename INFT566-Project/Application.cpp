#include "Application.h"

Application::Application() : m_window(nullptr), m_isGameOver(false)
{
}


Application::~Application()
{
}

bool Application::createWindow(const char* a_title, int a_width, int a_height, bool a_fullscreen)
{
	// If window already exist destroy it
	if (m_window != nullptr)
	{
		destroyWindow();
	}

	// Initialise glfwInit
	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	// Create Instance of GLFWwindow
	m_window = glfwCreateWindow(a_width,a_height,a_title, (a_fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

	// Make sure created successfully
	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	// Set Window to current contex
	glfwMakeContextCurrent(m_window);

	// Load OpenGL OpenGL extensions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	return true;
}

void Application::destroyWindow()
{
	// If window created destroy it
	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		m_window = nullptr;
	}
}

unsigned int Application::getWindowWidth() const
{
	// Check if window instance has been created
	if (m_window != nullptr)
	{
		// Get window width and return
		int width = 0, height = 0;
		glfwGetWindowSize(m_window, &width, &height);
		return width;
	}
	else
	{
		return 0;
	}
}

unsigned int Application::getWindowHeight() const
{
	// Check if window instance has been created
	if (m_window != nullptr)
	{
		// Get window height and return
		int width = 0, height = 0;
		glfwGetWindowSize(m_window, &width, &height);
		return height;
	}
	else
	{
		return 0;
	}
}

void Application::setClearColour(float a_red, float a_green, float a_blue, float a_alpha)
{
	glClearColor(a_red, a_green, a_blue, a_alpha);
}

void Application::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Application::getTime() const
{
	return (float) glfwGetTime();
}

void Application::run(const char * a_title, int a_width, int a_height, bool a_fullscreen)
{
	if (createWindow(a_title, a_width, a_height, a_fullscreen) /*TODO Include && startup()*/)
	{
		// Check if time Manager hasnt been initailised
		if (TimeManager::getInstance() == nullptr)
		{
			std::cout << "Time Manage has not been initialised" << std::endl;
			TimeManager::create();
		}

		while (!m_isGameOver)
		{
			
			TimeManager::getInstance()->updateDeltaTime();

			// Update window events
			glfwPollEvents();

			if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
				continue;
			
			update(float(TimeManager::getInstance()->getDeltaTime()));
			
			//present backbuffer to the monitor
			glfwSwapBuffers(m_window);

			// Should the game exit?
			m_isGameOver = m_isGameOver || glfwWindowShouldClose(m_window) == GLFW_TRUE;
		}

		// Clean up when game is over
		// TODO shutdown();
		destroyWindow();
	}
}

