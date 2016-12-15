#pragma once
#include "glm\gtc\matrix_transform.hpp"
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class PAGCamera {
private:
	glm::mat4 proyection, vision;
	glm::vec3 positionCamera, lookAt, upVector;
	float FoV, relation_width_heigh, z_near, z_far;
	int orbit_position;
	glm::vec3 position_orbit;
public:
	PAGCamera();
	~PAGCamera();

	void setPositionCamera(glm::vec3 positionC);
	void setLookAt(glm::vec3 lookA);
	void setUpVector(glm::vec3 upVec);

	//Camera mode

	void setFreeMovement(GLFWwindow *window);
	void setPanMovement(GLFWwindow *window);
	void setTiltMovement(GLFWwindow *window);
	void setTruckMovement(GLFWwindow *window);
	void setCraneMovement(GLFWwindow *window);
	void setOrbitMovement(GLFWwindow *window);

	glm::vec3 getLookAt();
	glm::vec3 getPositionCamera();
	glm::mat4 getVisionMatrix();
	glm::mat4 getProyectionMatrix();

};