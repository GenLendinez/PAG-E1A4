#include <iostream>
#include "PAGElement3D.h"
#include "PAGGroup3D.h"
#include "PAGObject3D.h"
#include <Windows.h>
#include "glm\gtc\matrix_transform.hpp"
#include "PAGRender.h"
#include <SOIL.h>
int main() {
	std::cout << "Starting final practice." << std::endl;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "PAG practice", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW." << std::endl;
		glfwTerminate();
		return -3;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glViewport(0, 0, 1024, 768);

	//Creacion camara y texturas

	PAGCamera *camera = new PAGCamera();
	PAGTexture *texturesPack = new PAGTexture();
	texturesPack->loadTexture("Textures/tela.jpg", GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR);
	texturesPack->loadTexture("Textures/TextureBoddy.png", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	texturesPack->loadTexture("Textures/BB8Test.png", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	texturesPack->loadTexture("Textures/Legs.png", GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR);
	texturesPack->loadTexture("Textures/Head.png", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	texturesPack->loadTexture("Textures/BodyLow.png", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	//Creacion mesa

	glm::vec3 *points_table = new glm::vec3[5];
	points_table[0] = glm::vec3(0, 0.7, 0);
	points_table[1] = glm::vec3(2, 1, 0);
	points_table[2] = glm::vec3(4, 1, 0);
	points_table[3] = glm::vec3(6, 1, 0);
	points_table[4] = glm::vec3(8, 1, 0);
	PAGRevolutionObject	*table = new PAGRevolutionObject(points_table, 5, true, false, false);
	table->setTexturesPack(texturesPack);
	table->addTexture(0, Texture_Color);
	table->Revolutionize(50);

	//Creacion araña (esta en funciones)

	PAGObject3D *objeto1 = new PAGObject3D();
	PAGObject3D *objeto2 = new PAGObject3D();

	objeto2->drawLowerBodySpiderAndHead(texturesPack);
	objeto1->drawLegs(texturesPack);

	//Acoplacion araña en grupo

	PAGGroup3D *spider = new PAGGroup3D();
	spider->add_new_object(objeto1);
	spider->add_new_object(objeto2);

	//Creacion del render y acoplacion de todos los elementos

	PAGRender scene = PAGRender();
	scene.addElement(spider);
	scene.addElement(table);
	scene.setCamera(camera);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	////BB8 Antena

	//glm::vec3 *points_ant = new glm::vec3[4];
	//points_ant[0] = glm::vec3(0, 1, 0);
	//points_ant[1] = glm::vec3(0.05, 1, 0);
	//points_ant[2] = glm::vec3(0.05, 3, 0);
	//points_ant[3] = glm::vec3(0, 3, 0);

	//PAGRevolutionObject *bbo_antena = new PAGRevolutionObject(points_ant, 4, true, true, false);
	//bbo_antena->Revolutionize(20);
	//glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(1.35, 4, 0));
	//bbo_antena->setTexturesPack(texturesPack);
	//bbo_antena->addTexture(3, Texture_Color);
	//bbo_antena->setModelMatrix(m);
	//bbo_antena->setModel_m(m);

	////BB8 Head

	//glm::vec3 *points_bb8H = new glm::vec3[25];
	//float pe = float(2 * 3.1415) / 100.0;
	//int size = 0;
	//for (int i = 0; i <25; i++) {
	//	points_bb8H[i] = glm::vec3(1.40 * cos(pe*i), 1.40 * sin(pe*i), 0);
	//}

	//PAGRevolutionObject *bb8_head = new PAGRevolutionObject(points_bb8H, 25, true, true, false);
	//bb8_head->Revolutionize(50);
	//m = glm::translate(glm::mat4(1.0f), glm::vec3(0, 4.8, 0));
	//bb8_head->setModelMatrix(m);
	//bb8_head->setModel_m(m);
	//bb8_head->addTextureBot(6, Texture_Color);
	//bb8_head->addTextureTop(6, Texture_Color);
	//bb8_head->setTexturesPack(texturesPack);
	//bb8_head->addTexture(2, Texture_Color);
	//
	////BB8 body

	//glm::vec3 *points_bb8 = new glm::vec3[50];
	//for (int i = 75; i < 125; i++) {
	//	points_bb8[size] = glm::vec3(2 * cos(pe*(i % 100)), 2 * sin(pe*(i % 100)), 0);
	//	size++;
	//}
	//PAGRevolutionObject *bb8_body = new PAGRevolutionObject(points_bb8, 50, true, true, false);
	//bb8_body->setTexturesPack(texturesPack);
	//bb8_body->addTexture(2, Texture_Color);
	//bb8_body->addTextureBot(6, Texture_Color);
	//bb8_body->addTextureTop(6, Texture_Color);
	//m = glm::translate(glm::mat4(1.0f), glm::vec3(0, 3, 0));
	//bb8_body->setModelMatrix(m);
	//bb8_body->setModel_m(m);
	//bb8_body->Revolutionize(50);

	//PAGGroup3D *bb8 = new PAGGroup3D();
	//bb8->add_new_object(bb8_body);
	//bb8->add_new_object(bb8_head);
	//bb8->add_new_object(bbo_antena);
	//PAGRender scene = PAGRender();
	//scene.addElement(bb8);
	//scene.setCamera(camera);
	//scene.addElement(table);

	scene.createPointLight(glm::vec3(6, 6, 4), 0.1f*glm::vec3(1, 1, 1), 0.3f*glm::vec3(1, 1, 1), 0.3f*glm::vec3(1, 1, 1), glm::vec3(0.7, 0.7, 1.0));
	//El angulo de la luz spot tiene que estar en grados ya que hago la conversion a radianes en el shader
	scene.createSpotLight(glm::vec3(6, 4, 0), glm::vec3(1, 1, 1), 0.5f*glm::vec3(1, 1, 1), 0.8f*glm::vec3(1, 1, 1), 1.0f*glm::vec3(1, 1, 1), 20.0, glm::vec3(-1, -1, 0));
	scene.createPointLight(glm::vec3(-20, 0, 0), 0.1f*glm::vec3(1, 1, 1), 0.8f*glm::vec3(1, 1, 1), 1.0f*glm::vec3(1, 1, 1), glm::vec3(0.5, 0.5, 1));
	scene.setTextures(texturesPack);
	scene.prepareRender();
	glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.renderWithIluminationAndTexture();
		camera->setFreeMovement(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	std::cout << "Finishing Final Practice." << std::endl;
	delete[] points_table;
	return 100;
}
