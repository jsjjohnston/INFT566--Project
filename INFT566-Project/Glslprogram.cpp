#include "glslprogram.h"
using std::ifstream;
using std::ios;
#include <sstream>

struct shader_file_extension {
	const char *ext;
	GLSLShaderType type;
};

struct shader_file_extension extensions[] =
{
	{ ".vs", GLSLShaderType::VERTEX },
	{ ".vert", GLSLShaderType::VERTEX },
	{ ".gs", GLSLShaderType::GEOMETRY },
	{ ".geom", GLSLShaderType::GEOMETRY },
	{ ".tcs", GLSLShaderType::TESS_CONTROL },
	{ ".tes", GLSLShaderType::TESS_EVALUATION },
	{ ".fs", GLSLShaderType::FRAGMENT },
	{ ".frag", GLSLShaderType::FRAGMENT },
	{ ".cs", GLSLShaderType::COMPUTE }
};

GLSLProgram::GLSLProgram(): handle(0), linked(false)
{
}

GLSLProgram::~GLSLProgram()
{
	if (handle == 0) return;

	// Query the number of attached shaders
	int numShaders = 0;
	glGetProgramiv(handle, GL_ATTACHED_SHADERS, &numShaders);

	// Get the shader names
	GLuint * shaderNames = new GLuint[numShaders];
	glGetAttachedShaders(handle, numShaders, NULL, shaderNames);

	// Delete the shaders
	for (int i = 0; i < numShaders; i++)
		glDeleteShader(shaderNames[i]);

	// Delete the program
	glDeleteProgram(handle);

	delete[] shaderNames;
}

void GLSLProgram::compileShader(const char * fileName)
{
	int numExts = sizeof(extensions) / sizeof(shader_file_extension);

	std::string ext = getExtension(fileName);
	GLSLShaderType type;
	bool matchFound = false;
	for (int i = 0; i < numExts; i++)
	{
		if (ext == extensions[i].ext)
		{
			matchFound = true;
			type = extensions[i].type;
			break;
		}
	}

	if (!matchFound)
	{
		std::cout << "COMPLIE SHADER ERRROR: Shader File extention not found: " << fileName << std::endl;
	}
	else
	{
		compileShader(fileName, type);
	}
}

void GLSLProgram::compileShader(const char * filename, GLSLShaderType type)
{
	// If File Doesnt Exist
	if (!fileExists(filename))
	{
		std::cout << "COMPLIE SHADER ERRROR : Shader File not found: " << filename << std::endl;
		return; //Dont crash
	}

	if (handle <= 0)
	{
		handle = glCreateProgram();
		if (handle == 0)
		{
			std::cout << "COMPLIE SHADER ERRROR: Unable to create shader program: " << filename << std::endl;
			return; //Dont crash
		}
	}

	std::ifstream inFile(filename, std::ios::in);
	if (!inFile) {
		std::cout << "COMPLIE SHADER ERRROR: Unable to open: " << filename << std::endl;
		return; //Dont Crash
	}

	// Get file contents
	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	
	std::string s_code = code.str();
	const char * c_code = s_code.c_str();

	compileShader(c_code, type, filename);

}

void GLSLProgram::compileShader(const char* source, GLSLShaderType type, const char * filename)
{
	if (handle <= 0)
	{
		handle = glCreateProgram();
		if (handle == 0)
		{
			std::cout << "COMPLIE SHADER ERRROR: Unable to create shader program: " << filename << std::endl;
			return; //Dont crash
		}
	}

	// Get Handle for shader
	unsigned int shaderHandle = glCreateShader(type);

	// Assign Shader source to handle
	glShaderSource(shaderHandle, 1, (const char**)&source, 0);

	// Complie Shader
	glCompileShader(shaderHandle);

	// Check for Shader Complie Errors
	int result;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);
	// If complie failed, display errors
	if (GL_FALSE == result)
	{
		//printf("%c - %c shader compilation failed!\n", stderr, type);

		std::cout << "shader compilation failed!: " << std::endl;

		int logLen;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			char* log = new char[logLen];

			int written;
			glGetShaderInfoLog(shaderHandle, logLen, &written, log);

			std::cout << "Shader log: " << log << std::endl;
			delete[] log;
		}

		if (filename)
		{
			std::cout << "Shader compilation failed!: " << filename << std::endl;
		}
		else
		{
			std::cout << "Shader compilation failed!" << std::endl;
		}

		return;
	}
	else
	{
		glAttachShader(handle, shaderHandle);
	}

}

void GLSLProgram::link()
{
	// Check if program has already been linked
	if (linked) return;

	if (handle <= 0)
	{
		std::cout << "Program has not been compiled." << std::endl;
		return;
	}

	glLinkProgram(handle);

	int status = 0;
	glGetProgramiv(handle, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		int length = 0;
		std::string logString;

		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
		
		if (length > 0)
		{
			char* c_log = new char[length];
			int written = 0;
			glGetProgramInfoLog(handle, length, &written, c_log);
			logString = c_log;
			delete[] c_log;
		}
		std::cout << "Program link failed:" << std::endl << logString << std::endl;
		return;
	}
	else
	{
		uniformLocations.clear();
		linked = true;
	}
}

void GLSLProgram::use()
{
	if (handle <= 0 || (!linked))
		std::cout << "Shader has not been linked:" << std::endl;
	
	glUseProgram(handle);
}

void GLSLProgram::validate()
{
	if (!linked)
	{
		std::cout << "Program is not linked" << std::endl;
		return;
	}

	int status;
	glValidateProgram(handle);
	glGetProgramiv(handle, GL_VALIDATE_STATUS, &status);

	if (GL_FALSE == status)
	{
		// Store log and return false
		int length = 0;
		std::string logString;

		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
		
		if (length = 0)
		{
			char* c_log = new char[length];
			int written = 0;
			glGetProgramInfoLog(handle, length, &written, c_log);
			logString = c_log;
			delete[] c_log;
		}

		std::cout << "Program Failed to validate" << std::endl;
	}
}

int GLSLProgram::getHandle() const
{
	return handle;
}

bool GLSLProgram::isLinked() const
{
	return linked;
}

void GLSLProgram::bindAttribLocation(unsigned int location, const char* name)
{
	glBindAttribLocation(handle, location, name);
}

void GLSLProgram::bindFragDataLocation(unsigned int location, const char* name)
{
	glBindFragDataLocation(handle, location, name);
}

void GLSLProgram::setUniform(const char * name, float x, float y, float z)
{
	int loc = getUniformLocation(name);
	glUniform3f(loc, x, y, z);
}

void GLSLProgram::setUniform(const char * name, const glm::vec2& v)
{
	int loc = getUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void GLSLProgram::setUniform(const char * name, const glm::vec3& v)
{
	int loc = getUniformLocation(name);
	glUniform3f(loc, v.x, v.y, v.z);
}

void GLSLProgram::setUniform(const char * name, const glm::vec4& v)
{
	int loc = getUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void GLSLProgram::setUniform(const char * name, const glm::mat4& m)
{
	int loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char * name, const glm::mat3 & m)
{
	int loc = getUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char * name, float val)
{
	int loc = getUniformLocation(name);
	glUniform1f(loc, val);
}

void GLSLProgram::setUniform(const char * name, int val)
{
	int loc = getUniformLocation(name);
	glUniform1i(loc, val);
}

void GLSLProgram::setUniform(const char * name, bool val)
{
	int loc = getUniformLocation(name);
	glUniform1i(loc, val);
}

void GLSLProgram::setUniform(const char * name, unsigned int val)
{
	int loc = getUniformLocation(name);
	glUniform1ui(loc, val);
}


std::string GLSLProgram::getExtension(const char * name)
{
	std::string nameStr(name);

	unsigned int location = nameStr.find_last_of('.');

	if (location != std::string::npos)
	{
		return nameStr.substr(location, std::string::npos);
	}

	return "";
}

bool GLSLProgram::fileExists(const std::string & a_fileName)
{
	struct stat buff; //System struct http://codewiki.wikidot.com/c:struct-stat 
	if (stat(a_fileName.c_str(), &buff) != -1)
	{
		return true;
	}
	return false;
}

int GLSLProgram::getUniformLocation(const char * name)
{
	if (uniformLocations.find(name) == uniformLocations.end())
	{
		uniformLocations[name] = glGetUniformLocation(handle, name);
	}
	return uniformLocations[name];
}
