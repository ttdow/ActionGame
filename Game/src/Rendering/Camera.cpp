#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
{
	this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	this->cameraTarget = glm::vec3(0.0f);
	this->cameraDirection = glm::normalize(cameraPos - cameraTarget);
	
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::normalize(glm::cross(worldUp, this->cameraDirection));
	this->cameraUp = glm::cross(cameraDirection, cameraRight);
	this->cameraFront = glm::cross(this->cameraUp, this->cameraRight);

	this->view = glm::mat4(1.0f);
}

void Camera::update(glm::vec3 newPos)
{
	this->cameraPos = newPos;
	
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->cameraDirection = glm::normalize(cameraPos - cameraTarget);
	this->cameraRight = glm::normalize(glm::cross(worldUp, this->cameraDirection));
	this->cameraUp = glm::cross(cameraDirection, cameraRight);
	this->cameraFront = glm::cross(this->cameraUp, this->cameraRight);

	this->view = glm::lookAt(this->cameraPos, this->cameraTarget, this->cameraUp);
}