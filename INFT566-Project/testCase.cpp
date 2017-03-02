#ifdef CATCH_CONFIG_MAIN
#include "Project.h"
#include <Catch\catch.hpp>
#include "TimeManager.h"
#include <GLFW\glfw3.h>
#include "ModelLoader.h"

TEST_CASE("Main", "[Project]")
{
	auto app = new Project();
	app->run("AIE", 1280, 720, false);
	delete app;
}

#endif // CATCH_CONFIG_MAIN

