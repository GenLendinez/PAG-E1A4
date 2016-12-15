#pragma once
#include <glew.h>
#include "glm\vec3.hpp"
#include <glfw3.h>

class PAGAbstractLight {
public:
	virtual void applyLight(glm::vec3 &Ia, glm::vec3 &Id, glm::vec3 &Is, glm::vec3 &Ks, glm::vec3 &positionLight, glm::vec3 &directionLight, float &angleMax) = 0;
};
