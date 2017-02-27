#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
/*
	NOTE Ensure Upto Date Time Manager 

	Time Manager
	Author: Jay Johnston
	Discription: Singleton class that manages time
*/
class TimeManager
{
public:
	static TimeManager* getInstance() { return m_instance; }

	void updateDeltaTime();

	static void create() 
	{ 
		if (m_instance == nullptr)
		{
			m_instance = new TimeManager();
		}
		else
		{
			std::cout << "Singleton already initialised" << std::endl;
		}
	}
	static void destroy() { delete m_instance; }

#ifdef CATCH_CONFIG_MAIN
	//Singleton pointer
	static TimeManager* m_instance;
#endif // !CATCH_CONFIG_MAIN

	const float getDeltaTime();

protected:

#ifndef CATCH_CONFIG_MAIN
	//Singleton pointer
	static TimeManager* m_instance;
#endif // !CATCH_CONFIG_MAIN

private:
	//Constructor private for singleton
	TimeManager();
	~TimeManager();

	float m_previousTime;
	float m_currentTime;
	float m_deltaTime;

};

