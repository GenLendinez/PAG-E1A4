#include "PAGDirectionalLight.h"

PAGDirectionalLight::PAGDirectionalLight(glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ks, glm::vec3 direction)
{
	this->Ia = Ia;
	this->Id = Id;
	this->Ks = Ks;
	this->Is = Is;
	this->direction = direction;
}

PAGDirectionalLight::~PAGDirectionalLight()
{
}

void PAGDirectionalLight::applyLight(glm::vec3 & Ia, glm::vec3 & Id, glm::vec3 & Is, glm::vec3 & Ks, glm::vec3 & positionLight, glm::vec3 &directionLight, float &angleMax)
{
	Ia = this->Ia;
	Id = this->Id;
	Is = this->Is;
	Ks = this->Ks;
	directionLight = direction;
}
