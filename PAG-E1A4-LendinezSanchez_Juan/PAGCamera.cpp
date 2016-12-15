#include "PAGCamera.h"

PAGCamera::PAGCamera()
{
	z_near = 0.1f;
	z_far = 100.0f;
	FoV = 45.0f;
	relation_width_heigh = 4.0f / 3.0f;
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	positionCamera = glm::vec3(3, 2, 10);
	lookAt = glm::vec3(0, 2, 0);
	upVector = glm::vec3(0, 1, 0);
	orbit_position = 1;
	position_orbit = positionCamera;
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

PAGCamera::~PAGCamera()
{
}

void PAGCamera::setPositionCamera(glm::vec3 positionC)
{
	positionCamera = positionC;
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

void PAGCamera::setLookAt(glm::vec3 lookA)
{
	lookAt = lookA;
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

void PAGCamera::setUpVector(glm::vec3 upVec)
{
	upVector = upVec;
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

void PAGCamera::setFreeMovement(GLFWwindow *window)
{
	double xpos, ypos;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float speed = 0.2f;
	float mouseSpeed = 0.005f;

	glfwGetCursorPos(window, &xpos, &ypos);
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	lookAt = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
	upVector = glm::cross(right, lookAt);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		positionCamera += lookAt * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		positionCamera -= lookAt * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		positionCamera += right * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		positionCamera -= right * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		FoV += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		FoV -= 0.01f;
	}
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	vision = glm::lookAt(positionCamera, lookAt + positionCamera, upVector);
	
}

void PAGCamera::setPanMovement(GLFWwindow * window)
{
	double xpos, ypos;
	float horizontalAngle = 0.0f;
	float mouseSpeed = 0.010f;
	glfwGetCursorPos(window, &xpos, &ypos);
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	lookAt = glm::vec3(horizontalAngle, lookAt.y, lookAt.z);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		FoV += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		FoV -= 0.01f;
	}
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

void PAGCamera::setTiltMovement(GLFWwindow * window)
{
	double xpos, ypos;
	float verticalAngle = 3.14f;
	float mouseSpeed = 0.005f;
	glfwGetCursorPos(window, &xpos, &ypos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	lookAt = glm::vec3(lookAt.x, sin(verticalAngle), cos(verticalAngle));
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		FoV += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		FoV -= 0.01f;
	}
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	vision = glm::lookAt(positionCamera, lookAt + positionCamera, upVector);
}

void PAGCamera::setTruckMovement(GLFWwindow * window)
{
	float speed = 0.5f;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		positionCamera.z += 1 * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		positionCamera.z -= 1 * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		FoV += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		FoV -= 0.01f;
	}
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

void PAGCamera::setCraneMovement(GLFWwindow * window)
{
	float speed = 0.1f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		positionCamera.y += 1 * speed;
		lookAt.y += 1 * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		positionCamera.y -= 1 * speed;
		lookAt.y -= 1 * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		FoV += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		FoV -= 0.01f;
	}
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}

void PAGCamera::setOrbitMovement(GLFWwindow * window)
{
	const float nPI = 3.14159265;
	float angleIncrement = ((float)nPI * 2) / 100.0f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		positionCamera.x = position_orbit.z *  cos(angleIncrement * orbit_position);
		positionCamera.z = position_orbit.z * -sin(angleIncrement * orbit_position);
		if (orbit_position == 100) orbit_position = 0;
		orbit_position++;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		positionCamera.x = position_orbit.z *  cos(angleIncrement * orbit_position);
		positionCamera.z = position_orbit.z * -sin(angleIncrement * orbit_position);
		if (orbit_position == 0) orbit_position = 100;
		orbit_position--;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		FoV += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		FoV -= 0.01f;
	}
	proyection = glm::perspective(FoV, relation_width_heigh, z_near, z_far);
	vision = glm::lookAt(positionCamera, lookAt, upVector);
}



glm::vec3 PAGCamera::getLookAt()
{
	return lookAt;
}

glm::vec3 PAGCamera::getPositionCamera()
{
	return positionCamera;
}

glm::mat4 PAGCamera::getVisionMatrix()
{
	return vision;
}

glm::mat4 PAGCamera::getProyectionMatrix()
{
	return proyection;
}
