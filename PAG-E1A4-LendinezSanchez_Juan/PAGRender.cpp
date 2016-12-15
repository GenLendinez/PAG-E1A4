#include "PAGRender.h"

PAGRender::PAGRender()
{
	camera = new PAGCamera();
	lights = new PAGLight();
	this->add_shader_object("adsPointLight");
	this->add_shader_object("adsTexturePointLight");
	this->add_shader_object("adsTextureSpotLight");
}

PAGRender::~PAGRender()
{
	for (int i = 0; i < shaders.size(); i++) {
		delete shaders.at(i);
	}
	for (int i = 0; i < elements.size(); i++) {
		delete elements.at(i);
	}
	delete lights;
	delete camera;
	delete textures;
}

void PAGRender::createPointLight(glm::vec3 position_l, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 Ka)
{
	lights_type.push_back(POINT_LIGHT);
	lights->createPointLight(position_l, Ia, Id, Is, Ka);
}

void PAGRender::createSpotLight(glm::vec3 position_l, glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, float angleMax, glm::vec3 direction)
{
	lights_type.push_back(SPOT_LIGHT);
	lights->createSpotLight(position_l, Ka, Ia, Id, Is, angleMax, direction);
}

void PAGRender::createDirectionalLIght(glm::vec3 Ka, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is, glm::vec3 direction)
{
	lights_type.push_back(DIRECTIONAL_LIGHT);
	lights->createDirectionalLight(Ka, Ia, Id, Is, direction);
}

void PAGRender::setCamera(PAGCamera *newCamera)
{
	camera = newCamera;
}

void PAGRender::addElement(PAGElement3D * element)
{
	elements.push_back(element);
}

void PAGRender::setTextures(PAGTexture * textures)
{
	this->textures = textures;
}

/*
* add_shader_object PAGRender
* This function will add a shader to the vector just with the name
* @param name_shader name of the two files ".frag" and ".vert"
* IMPORTANT: This files has to be in the same proyect file
*/

void PAGRender::add_shader_object(std::string name_shader)
{
	PagShaderProgram *new_shader = new PagShaderProgram();
	new_shader->createShaderProgram(name_shader.c_str());
	shaders.push_back(new_shader);
}

/*
* choose_shader PAGRender
* This function will choose a shader with a given name from all the shaders contains in the class
* @param name_shader shader's name that it will be active until you active another one
*/

void PAGRender::choose_shader(std::string name_shader)
{
	for (int i = 0; i < shaders.size(); i++) {
		if (shaders.at(i)->get_name() == name_shader) shader_choosen = i;
	}
	if (shader_choosen == -1) {
		std::cout << "That name is not a shader" << std::endl;
		return;
	}
	shaders.at(shader_choosen)->use();
}

void PAGRender::prepareRender()
{
	for (int i = 0; i < elements.size(); i++) {
		elements.at(i)->prepareToDraw(GL_TRIANGLE_STRIP);
	}
}

void PAGRender::renderWithIlumination()
{
	this->choose_shader("adsPointLight");
	if (shader_choosen == -1) {
		std::cout << "Fallo" << std::endl;
		return;
	}
	shaders.at(shader_choosen)->setUniform("Shininess", 10.0f);
	glEnable(GLenum(GL_BLEND));
	glDepthFunc(GLenum(GL_LEQUAL));
	for (int i = 0; i < lights->getSizeLights(); i++) {
		if (i == 0) { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
		else { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
		for (int i = 0; i < elements.size(); i++) {
			elements.at(i)->draw(shaders.at(shader_choosen), glm::mat4(1.0f), camera, 1);
		}
	}
}

void PAGRender::renderWithIluminationAndTexture()
{
	if (shader_choosen == -1) {
		std::cout << "Fallo" << std::endl;
		return;
	}
	glEnable(GLenum(GL_BLEND));
	glDepthFunc(GLenum(GL_LEQUAL));
	for (int i = 0; i < lights->getSizeLights(); i++) {
		if (i == 0) { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
		else { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
		if (lights_type.at(i) == POINT_LIGHT) {
			this->choose_shader("adsTexturePointLight");
		}else if (lights_type.at(i) == DIRECTIONAL_LIGHT) {
			this->choose_shader("adsTextureDirLight");
		}else if (lights_type.at(i) == SPOT_LIGHT) {
			this->choose_shader("adsTextureSpotLight");
		}
		shaders.at(shader_choosen)->setUniform("Shininess", 100.0f);
		lights->applyLight(i, shaders.at(shader_choosen), camera);
		for (int i = 0; i < elements.size(); i++) {
			elements.at(i)->draw(shaders.at(shader_choosen), glm::mat4(1.0f), camera, 1);
		}
	}

}


