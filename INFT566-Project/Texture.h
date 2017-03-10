#pragma once

#include <string>
#include "gl_core_4_4.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool load(const char* a_fileName);

protected:
	std::string	m_filename;
	int m_width;
	int m_height;
	unsigned int m_glHandle;
	int m_format;
	unsigned char* m_loadedPixels;
};

