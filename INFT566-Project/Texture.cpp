#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(): m_filename(""), m_width(0), m_height(0),m_glHandle(0),m_format(0),m_loadedPixels(nullptr)
{
}


Texture::~Texture()
{
}

bool Texture::load(const char * a_fileName)
{
	// Check if texture Already Exists
	if (m_glHandle !=0)
	{
		glDeleteTextures(1, &m_glHandle);
		m_glHandle = 0;
		m_width = 0;
		m_height = 0;
		m_filename = "";
	}
	return false;
}
