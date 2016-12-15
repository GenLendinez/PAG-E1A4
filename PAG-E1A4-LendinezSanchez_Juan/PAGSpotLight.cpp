#include "PAGSpotLight.h"
#include <iostream>

PAGSpotLight::PAGSpotLight(glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ks, glm::vec3 positionLight, glm::vec3 direction, float angleMax)
{
	this->Ia = Ia;
	this->Id = Id;
	this->Ks = Ks;
	this->Is = Is;
	this->positionLight = positionLight;
	this->direction = direction;
	this->angleMax = angleMax;
}

PAGSpotLight::~PAGSpotLight()
{
}

void PAGSpotLight::applyLight(glm::vec3 & Ia, glm::vec3 & Id, glm::vec3 & Is, glm::vec3 & Ks, glm::vec3 & positionLight, glm::vec3 & directionLight, float & angleMax)
{
	Ia = this->Ia;
	Id = this->Id;
	Is = this->Is;
	Ks = this->Ks;
	positionLight = this->positionLight;
	directionLight = direction;
	angleMax = this->angleMax;
}
