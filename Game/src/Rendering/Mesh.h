#pragma once

#include <vector>
#include <glm/glm.hpp>

class Shader;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh
{
public:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void draw(Shader& shader);

private:

	unsigned int VAO, VBO, EBO;

	void setupMesh();
};