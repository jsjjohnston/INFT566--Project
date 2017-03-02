#pragma once
#include "tiny_obj_loader.h"
#include <iostream>
#include <string>

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	bool loadModel(const char* a_fileName);
};

