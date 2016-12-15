#include "PAGLight.h"

PAGLight::PAGLight()
{
}

PAGLight::~PAGLight()
{
	for (int i = 0; i < lights.size(); i++) {
		delete lights.at(i).second;
	}
}

void PAGLight::createPointLight(glm::vec3 positionLight, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ks)
{
	lights.push_back(std::pair<int, PAGAbstractLight*>(POINT_LIGHT, new PAGPointLight(Ia, Id, Is, Ks, positionLight)));
}

void PAGLight::createSpotLight(glm::vec3 position_l, glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, float angleMax, glm::vec3 direction)
{
	lights.push_back(std::pair<int, PAGAbstractLight* >(SPOT_LIGHT, new PAGSpotLight(Ia, Id, Is, Ka, position_l, direction, angleMax)));
}

void PAGLight::createDirectionalLight(glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 direction)
{
	lights.push_back(std::pair<int, PAGAbstractLight* >(DIRECTIONAL_LIGHT, new PAGDirectionalLight(Ia,Id,Is,Ka,direction)));
}

int PAGLight::getSizeLights()
{
	return lights.size();
}

void PAGLight::applyLight(int pos_light, PagShaderProgram * shader, PAGCamera *camera)
{
	glm::vec4 resultVarPosLight;
	switch (lights.at(pos_light).first) {
	case POINT_LIGHT:
		lights.at(pos_light).second->applyLight(Ia, Id, Is, Ks, positionLight, direction, angleSpot);
		shader->setUniform("Ia", Ia);
		shader->setUniform("Ks", Ks);
		shader->setUniform("Id", Id);
		shader->setUniform("Is", Is);
		resultVarPosLight = camera->getVisionMatrix() * glm::vec4(positionLight.x, positionLight.y, positionLight.z, 1.0);
		shader->setUniform("lightPosition", glm::vec3(resultVarPosLight.x, resultVarPosLight.y, resultVarPosLight.z));
		break;
	case SPOT_LIGHT:
		lights.at(pos_light).second->applyLight(Ia, Id, Is, Ks, positionLight, direction, angleSpot);
		shader->setUniform("Ia", Ia);
		shader->setUniform("Ks", Ks);
		shader->setUniform("Id", Id);
		shader->setUniform("angleMax", angleSpot);
		resultVarPosLight = camera->getVisionMatrix() * glm::vec4(direction.x, direction.y,direction.z, 0.0);
		shader->setUniform("direction", glm::vec3(resultVarPosLight.x, resultVarPosLight.y, resultVarPosLight.z));
		shader->setUniform("Is", Is);
		resultVarPosLight = camera->getVisionMatrix() * glm::vec4(positionLight.x, positionLight.y, positionLight.z, 1.0);
		shader->setUniform("lightPosition", glm::vec3(resultVarPosLight.x, resultVarPosLight.y, resultVarPosLight.z));
		break;
	case DIRECTIONAL_LIGHT:
		lights.at(pos_light).second->applyLight(Ia, Id, Is, Ks, positionLight, direction, angleSpot);
		shader->setUniform("Ia", Ia);
		shader->setUniform("Ks", Ks);
		shader->setUniform("Id", Id);
		resultVarPosLight = camera->getVisionMatrix() * glm::vec4(direction.x, direction.y, direction.z, 0.0);
		shader->setUniform("direction", glm::vec3(resultVarPosLight.x, resultVarPosLight.y, resultVarPosLight.z));
		shader->setUniform("Is", Is);
		break;
	}
}
