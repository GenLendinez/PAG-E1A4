#include "PagShaderProgram.h"

PagShaderProgram::PagShaderProgram()
{
	handler = 0;
	linked = false;
	logString = "";
}

PagShaderProgram::~PagShaderProgram()
{
}

GLuint PagShaderProgram::createShaderProgram(const char *fileName) {
	name_shader = fileName;
	if (handler <= 0) {
		handler = glCreateProgram();
		if (handler == 0) {
			std::cout << "Cannot create shader program: " << fileName << std::endl;
			return 0;
		}
	}

	char fileNameComplete[256];
	strcpy_s(fileNameComplete, fileName);
	strcat_s(fileNameComplete, ".vert");
	GLuint vertexShaderObject = compileShader(fileNameComplete, GL_VERTEX_SHADER);
	if (vertexShaderObject == 0) {
		return 0;
	}
	strcpy_s(fileNameComplete, fileName);
	strcat_s(fileNameComplete, ".frag");
	GLuint fragmentShaderObject = compileShader(fileNameComplete, GL_FRAGMENT_SHADER);
	if (fragmentShaderObject == 0) { 
		return 0; 
	}

	glAttachShader(handler, vertexShaderObject);
	glAttachShader(handler, fragmentShaderObject);

	glLinkProgram(handler);

	GLint linkSuccess = 0;
	glGetProgramiv(handler, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE) {
		GLint logLen = 0;
		glGetProgramiv(handler, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char * cLogString = new char[logLen];
			GLint written = 0;
			glGetProgramInfoLog(handler, logLen, &written, cLogString);
			logString.assign(cLogString);
			delete[] cLogString;
			std::cout << "Cannot link shader " << fileName << std::endl << logString << std::endl;
		}
		return 0;
	} else {
		linked = true;
	}

	return handler;
}

bool PagShaderProgram::use() {
	if ((handler > 0) && (linked)) {
		glUseProgram(handler);
		return true;
	} else {
		std::cout << "Cannot use shader program" << std::endl;
		return false;
	}
}

bool PagShaderProgram::setUniform(std::string name, GLint value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		glUniform1i(location, value);
		return true;
	} else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}

bool PagShaderProgram::setUniform(std::string name, GLfloat value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		glUniform1f(location, value);
		return true;
	} else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}

bool PagShaderProgram::setUniform(std::string name, glm::mat4 value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
		return true;
	} else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}

bool PagShaderProgram::setUniform(std::string name, glm::vec3 value) {
	GLint location = glGetUniformLocation(handler, name.c_str());
	if (location >= 0) {
		glUniform3fv(location, 1, &value[0]);
		return true;
	}
	else {
		std::cout << "Cannot find localization for: " << name << std::endl;
		return false;
	}
}

std::string PagShaderProgram::get_name()
{
	return name_shader;
}


GLuint PagShaderProgram::compileShader(const char *filename, GLenum shaderType) {
	if (!fileExists(filename)) {
		std::cout << "Shader source file " << filename << " not found." << std::endl;
		return 0;
	}

	std::ifstream shaderSourceFile;
	shaderSourceFile.open(filename);
	if (!shaderSourceFile) {
		std::cout << "Cannot open shader source file." << std::endl;
		return 0;
	}

	std::stringstream shaderSourceStream;
	shaderSourceStream << shaderSourceFile.rdbuf();
	std::string shaderSourceString = shaderSourceStream.str();

	shaderSourceFile.close();

	GLuint shaderHandler = glCreateShader(shaderType);
	if (shaderHandler == 0) {
		std::cout << "Cannot create shader object." << std::endl;
		return 0;
	}

	const char * shaderSourceCString = shaderSourceString.c_str();
	glShaderSource(shaderHandler, 1, &shaderSourceCString, NULL);
	glCompileShader(shaderHandler);

	GLint compileResult;
	glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		GLint logLen = 0;
		logString = "";
		glGetShaderiv(shaderHandler, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char * cLogString = new char[logLen];
			GLint written = 0;
			glGetShaderInfoLog(shaderHandler, logLen, &written, cLogString);
			logString.assign(cLogString);
			delete[] cLogString;
			std::cout << "Cannot compile shader " << shaderType << std::endl << logString << std::endl;
		}
	}

	return shaderHandler;
}

bool PagShaderProgram::fileExists(const std::string & fileName)
{
	struct stat info;
	int ret = -1;

	ret = stat(fileName.c_str(), &info);
	return 0 == ret;
}

