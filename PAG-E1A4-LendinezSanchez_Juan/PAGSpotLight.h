#pragma once
#include "PAGAbstractLight.h"

class PAGSpotLight : public PAGAbstractLight {
private:
	glm::vec3 positionLight, Ia, Id, Is, Ks, direction;
	float angleMax;
public:
	PAGSpotLight(glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ks, glm::vec3 positionLight, glm::vec3 direction, float angleMax);
	~PAGSpotLight();
	void applyLight(glm::vec3 & Ia, glm::vec3 & Id, glm::vec3 & Is, glm::vec3 & Ks, glm::vec3 & positionLight, glm::vec3 &directionLight, float &angleMax);
};
