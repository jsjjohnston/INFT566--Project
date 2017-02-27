#include "TimeManager.h"

//Singleton initailed TimeManage instance to Null
TimeManager* TimeManager::m_instance = nullptr;

void TimeManager::updateDeltaTime()
{
	m_currentTime = (float) glfwGetTime();
	m_deltaTime = m_currentTime - m_previousTime;
	m_previousTime = m_currentTime;
}

const float TimeManager::getDeltaTime()
{
	return m_deltaTime;
}

TimeManager::TimeManager() : m_currentTime(0.0f), m_deltaTime(0.0f), m_previousTime(0.0f)
{
}


TimeManager::~TimeManager()
{
}
