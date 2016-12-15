#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
#include <string>
#include <glew.h>
#include <glfw3.h>
#include "glm\glm.hpp"

class PagShaderProgram
{
public:
	PagShaderProgram();
	~PagShaderProgram();
	
	GLuint createShaderProgram(const char *filename);
	bool use();

	bool setUniform(std::string name, GLfloat value);
	bool setUniform(std::string name, GLint value);
	bool setUniform(std::string name, glm::mat4 value);
	bool setUniform(std::string name, glm::vec3 value);

	std::string get_name();

private:
	GLuint handler;
	bool linked;
	std::string name_shader;
	std::string logString;

	GLuint compileShader(const char *filename, GLenum shaderType);
	bool fileExists(const std::string & fileName);
};

