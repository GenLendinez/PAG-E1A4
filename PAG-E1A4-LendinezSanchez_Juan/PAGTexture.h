#pragma once
#include "glm\mat4x4.hpp"
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <iostream>
#include "SOIL.h"


class PAGTexture {
private:
	std::vector<GLuint> id_imgs;
	GLuint ep;
public:
	PAGTexture();
	~PAGTexture();
	void loadTexture(char *path_img, GLuint min_filter, GLuint mag_filter);
	void applyTexture(GLuint id, int pos);
};