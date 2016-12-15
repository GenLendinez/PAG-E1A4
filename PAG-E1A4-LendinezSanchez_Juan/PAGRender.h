#pragma once
#include "PAGObject3D.h"
#include "PAGLight.h"

class PAGRender {
private:
	std::vector<PagShaderProgram*> shaders;
	std::vector<PAGElement3D*> elements;
	std::vector<int> lights_type;
	PAGTexture *textures;
	PAGCamera *camera;
	PAGLight *lights;
	int shader_choosen;
	glm::mat4 pr;
protected:
	void add_shader_object(std::string name_shader);
	void choose_shader(std::string name_shader);
public:
	PAGRender();
	~PAGRender();

	//Light functions

	void createPointLight(glm::vec3 position_l, glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
	void createSpotLight(glm::vec3 position_l, glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, float angleMax, glm::vec3 direction);
	void createDirectionalLIght( glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is,glm::vec3 direction);

	//Camera functions

	void setCamera(PAGCamera *newCamera);

	//Elements Functions

	void addElement(PAGElement3D *element);

	//Texture Functions

	void setTextures(PAGTexture *textures);

	//Render fucntions

	void prepareRender();
	void renderWithIlumination();
	void renderWithIluminationAndTexture();
};