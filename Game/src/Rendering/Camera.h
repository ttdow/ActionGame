#pragma once

#include <glm/glm.hpp>

class Camera
{
public:

	Camera();

	void update(glm::vec3 newPos);
	glm::vec3 getPosition() { return cameraPos; }
	glm::vec3 getUp() { return cameraUp; }
	glm::vec3 getRight() { return cameraRight; }
	glm::mat4 view;

private:

	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
};
