#pragma once

#include <vector>

#include <glm/glm.hpp>

class Shader;

struct Vertex
{
	glm::vec3 vertex;
	glm::vec2 texCoord;
};

class Model
{
public:

	void draw(Shader shader);

private:

	void initialize();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
};