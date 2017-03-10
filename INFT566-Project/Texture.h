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
	std::string		m_filename;
	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_glHandle;
	unsigned int	m_format;
	unsigned char*	m_loadedPixels;
};

