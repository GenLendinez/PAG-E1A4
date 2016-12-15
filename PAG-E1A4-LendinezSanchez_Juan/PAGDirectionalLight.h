#pragma once
#include "PAGAbstractLight.h"

class PAGDirectionalLight : public PAGAbstractLight {
private:
	glm::vec3 Ia, Id, Is, Ks, direction;
public:
	PAGDirectionalLight(glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ks, glm::vec3 direction);
	~PAGDirectionalLight();
	void applyLight(glm::vec3 & Ia, glm::vec3 & Id, glm::vec3 & Is, glm::vec3 & Ks, glm::vec3 & positionLight, glm::vec3 &directionLight, float &angleMax);
};
