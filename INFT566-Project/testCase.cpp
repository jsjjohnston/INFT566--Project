#ifdef CATCH_CONFIG_MAIN
#include "Project.h"
#include <Catch\catch.hpp>
#include "TimeManager.h"
#include <GLFW\glfw3.h>


TEST_CASE("Create", "[TimeManager]")
{
	REQUIRE(TimeManager::m_instance == nullptr);
	TimeManager::create();
	REQUIRE(TimeManager::m_instance != nullptr);
}

TEST_CASE("UpdateDeltaTime", "[TimeManager]")
{
	// Initialise glfwInit
	glfwInit();
	TimeManager::create();
	REQUIRE(TimeManager::getInstance()->getDeltaTime() == 0.0f);
	TimeManager::getInstance()->updateDeltaTime();
	REQUIRE(TimeManager::getInstance()->getDeltaTime() != 0.0f);
	float time = TimeManager::getInstance()->getDeltaTime();
	TimeManager::getInstance()->updateDeltaTime();
	REQUIRE_FALSE(TimeManager::getInstance()->getDeltaTime() == time);
	glfwTerminate();
}


#endif // CATCH_CONFIG_MAIN

