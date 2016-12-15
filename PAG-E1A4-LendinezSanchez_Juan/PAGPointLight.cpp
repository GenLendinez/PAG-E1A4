#include "PAGPointLight.h"
#include <iostream>

PAGPointLight::PAGPointLight(glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ks, glm::vec3 positionLight)
{
	this->Ia = Ia;
	this->Id = Id;
	this->Ks = Ks;
	this->Is = Is;
	this->positionLight = positionLight;
}

PAGPointLight::~PAGPointLight()
{
}

void PAGPointLight::applyLight(glm::vec3 & Ia, glm::vec3 & Id, glm::vec3 & Is, glm::vec3 & Ks, glm::vec3 & positionLight, glm::vec3 &directionLight, float &angleMax)
{
	Ia = this->Ia;
	Id = this->Id;
	Is = this->Is;
	Ks = this->Ks;
	positionLight = this->positionLight;
}
