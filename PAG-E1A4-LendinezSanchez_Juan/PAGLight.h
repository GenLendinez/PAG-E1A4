#pragma once
#include "PAGPointLight.h"
#include "PAGSpotLight.h"
#include "PAGDirectionalLight.h"
#include "PAGElement3D.h"

const int POINT_LIGHT = 0;
const int DIRECTIONAL_LIGHT = 1;
const int SPOT_LIGHT = 2;

class PAGLight {
private:
	GLfloat angleSpot;
	std::vector<std::pair<int,PAGAbstractLight*>> lights;
	glm::vec3 positionLight, direction, Ia, Id, Is, Ks;
public:
	PAGLight();
	~PAGLight();
	void createPointLight(glm::vec3 positionLight, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is,glm::vec3 Ks);
	void createSpotLight(glm::vec3 position_l, glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, float angleMax, glm::vec3 direction);
	void createDirectionalLight(glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 direction);
	int getSizeLights();
	void applyLight(int pos_light, PagShaderProgram *shader, PAGCamera *camera);
};
