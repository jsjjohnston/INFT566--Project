#pragma once
#include "Primitives\OpenGLInfo.h"
#include "Primitives\OBJVertex.h"

#include "tiny_obj_loader.h"

#include <gl_core_4_4.h>

#include <iostream>
#include <vector>

class Model
{
public:
	Model();
	~Model();

	//void createOpenGLBuffers();

	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::vector<OpenGLInfo> m_glInfo;
};

