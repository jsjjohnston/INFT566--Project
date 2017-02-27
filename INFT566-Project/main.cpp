#include "Project.h"

#ifndef CATCH_CONFIG_MAIN
void main()
{
	auto app = new Project();
	app->run("AIE", 1280, 720, false);
	delete app;
}
#endif // !CATCH_CONFIG_MAIN