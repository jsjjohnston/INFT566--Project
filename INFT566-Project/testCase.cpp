#ifdef CATCH_CONFIG_MAIN

#include <Catch\catch.hpp>
#include "Application.h"


TEST_CASE("Window creation", "[Application]") {
	
	SECTION("Create a window with params")
	{
		auto app = new Application();

		REQUIRE(app->createWindow("TestCase Window", 800, 600, false) == true);
		REQUIRE(app->getWindowPtr() != nullptr);

		SECTION("Check window size")
		{
			REQUIRE(app->getWindowHeight() == 600);
			REQUIRE(app->getWindowWidth() == 800);
		}
		delete app;
	}

	SECTION("Create a window with default params")
	{
		auto app = new Application();
		REQUIRE(app->createWindow() == true);
		REQUIRE(app->getWindowPtr() != nullptr);

		SECTION("Check window size")
		{
			REQUIRE(app->getWindowHeight() == 720);
			REQUIRE(app->getWindowWidth() == 1280);
		}
		delete app;
	}

	SECTION("Create a default window then create a custom window")
	{
		auto app = new Application();
		REQUIRE(app->createWindow() == true);
		REQUIRE(app->getWindowPtr() != nullptr);

		SECTION("Check default window size")
		{
			REQUIRE(app->getWindowHeight() == 720);
			REQUIRE(app->getWindowWidth() == 1280);
		}

		REQUIRE(app->createWindow("TestCase Window", 800, 600, false) == true);
		REQUIRE(app->getWindowPtr() != nullptr);

		SECTION("Check customw indow size")
		{
			REQUIRE(app->getWindowHeight() == 600);
			REQUIRE(app->getWindowWidth() == 800);
		}
		delete app;
	}

	SECTION("Create a custom window then create a default window")
	{
		auto app = new Application();
		REQUIRE(app->createWindow("TestCase Window", 800, 600, false) == true);
		REQUIRE(app->getWindowPtr() != nullptr);

		SECTION("Check customw indow size")
		{
			REQUIRE(app->getWindowHeight() == 600);
			REQUIRE(app->getWindowWidth() == 800);
		}

		REQUIRE(app->createWindow() == true);
		REQUIRE(app->getWindowPtr() != nullptr);

		SECTION("Check default window size")
		{
			REQUIRE(app->getWindowHeight() == 720);
			REQUIRE(app->getWindowWidth() == 1280);
		}
		delete app;
	}
}

TEST_CASE("Window destruction", "[Application]")
{
	SECTION("Create a window then destory window")
	{
		auto app = new Application();
		
		REQUIRE(app->createWindow() == true);
		app->destroyWindow();
		REQUIRE(app->getWindowPtr() == nullptr);
	}
}

TEST_CASE("Test End Game", "[Application]")
{
	auto app = new Application();

	app->setClearColour(0.5f, 0.6f, 0.3f, 0.5f);

	app->endGame();

	REQUIRE(app->m_isGameOver == true);
}

TEST_CASE("getTime", "[Application]")
{
	auto app = new Application();
	app->createWindow();
	REQUIRE(app->getTime() != 0.0f);
	float time = app->getTime();
	REQUIRE(app->getTime() > time);
	REQUIRE_FALSE(app->getTime() <= time);
}

TEST_CASE("Run", "[Application]")
{
	auto app = new Application();
	app->run("TestCase Window", 800, 600, false);
	REQUIRE(app->getWindowPtr() != nullptr);
}

#endif // CATCH_CONFIG_MAIN

