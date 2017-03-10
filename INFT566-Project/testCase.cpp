#ifdef CATCH_CONFIG_MAIN
#include "Project.h"
#include <Catch\catch.hpp>
#include "TimeManager.h"
#include <GLFW\glfw3.h>
#include "ModelLoader.h"
#include "Texture.h"

TEST_CASE("Main", "[Project]")
{
	auto app = new Project();
	app->run("AIE", 1280, 720, false);
	delete app;

}

TEST_CASE("Load", "[Textures]")
{
	auto tex = new Texture();
	REQUIRE(tex->load("soulspear_diffuse.tga") == true);
}
#endif // CATCH_CONFIG_MAIN

