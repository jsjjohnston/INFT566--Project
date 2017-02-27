#pragma once

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include "TimeManager.h"

/*
	NOTE Ensure upto date
	Application
	Author: Jay Johnstonm
	Discription: Used as a base class for new scenes
*/

class Application
{
public:
	Application();
	virtual ~Application();

	// Access to the GLFW window
	GLFWwindow* getWindowPtr() const { return m_window; }

	// Returns the width of the game window
	unsigned int getWindowWidth() const;

	// Returns the height of the game window
	unsigned int getWindowHeight() const;

	// Set the clear (Background) colour on the screen
	void setClearColour(float a_red, float a_green, float a_blue, float a_alpha = 1.0f);

	// Wipes the screen clear to begin a frame of drawing
	void clearScreen();

	//These functions must be implemented by a child class
	virtual bool startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	void endGame() { m_isGameOver = true; };

	// Returns time since application started
	float getTime() const;

	// Creates a window and begins the game loop which calls update() and draw()repeatedly
	// It first calls startup() and if that succeeds it then starts the loop,
	// Ending with shutdown() if m_gameOver is true
	void run(const char* a_title, int a_width, int a_height, bool a_fullscreen);

protected:
	GLFWwindow* m_window; // Applications Instance of window using GLFW

	bool m_isGameOver; // if set to false, the main game loop will exit
	/*
	Create a GLFW window
		a_title -		The title displayed at the top of the window (DEFAULT "DEFAULT WINDOW")
		a_width -		Width of the window in pixels (DEFAULT = 1280)
		a_height -		Height of the window in pixels (DEFAULT = 720)
		a_fullscreen -	Option to display the window in fullscreen or (not = false)

		returns -		True:	if a new window has been created
		False:	if window creation has Failed

		**NOTE**		If window has already been created the previous window will be destroyed and a new one will be created
		*/
	virtual bool createWindow(const char* a_title = "DEFAULT WINDOW", int a_width = 1280, int a_height = 720, bool a_fullscreen = false);

	/*
		Destroy a GLFW window
	*/
	virtual void destroyWindow();

};

