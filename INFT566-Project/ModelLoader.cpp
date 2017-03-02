#include "ModelLoader.h"



ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

bool ModelLoader::loadModel(const char * a_fileName)
{
	// tinyOBJ Required Parameters
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err; // Errors Warning Messages

	bool success = tinyobj::LoadObj(&attribs, &shapes, &materials, &err, a_fileName);

	/*
		Err could contain warning messages
	*/
	if (!err.empty())
	{
		std::cout << err << std::endl; // Output errors and Warnaings
	}

	// if model load Failed return false
	if (!success)
		return false;

	return success;
}
