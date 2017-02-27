#pragma once
#include <map>
#include <string>
#include <fstream>
#include <gl_core_4_4.h>
#include <iostream>
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

/*
	GLSLProgram - Shader program object

	Based off of the GLSL cookbook example

	https://github.com/daw42/glslcookbook/tree/master/ingredients
*/

enum GLSLShaderType {
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	TESS_CONTROL = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	COMPUTE = GL_COMPUTE_SHADER
};

class GLSLProgram
{

public:
	GLSLProgram();
	~GLSLProgram();

	void complieShader(const char* fileName);
	void compileShader(const char* filename, GLSLShaderType type);
	void compileShader(const char* source, GLSLShaderType type, const char* filename);
	void link();
	void use();
	void validate();

	int  getHandle() const;
	bool isLinked() const;
		 
	void bindAttribLocation(unsigned int location, const char* name);
	void bindFragDataLocation(unsigned int location, const char* name);
		 
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::vec2& v);
	void setUniform(const char* name, const glm::vec3& v);
	void setUniform(const char* name, const glm::vec4& v);
	void setUniform(const char* name, const glm::mat4& m);
	void setUniform(const char* name, const glm::mat3& m);
	void setUniform(const char* name, float val);
	void setUniform(const char* name, int val);
	void setUniform(const char* name, bool val);
	void setUniform(const char* name, unsigned int val);


protected:

private:
	int handle;
	bool linked;
	std::map<std::string, int> uniformLocations;

	std::string getExtension(const char* name);

	bool fileExists(const std::string& a_fileName);

	int getUniformLocation(const char * name);
};

