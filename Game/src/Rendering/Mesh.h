#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Bone.h"

class Shader;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;

	glm::ivec4 boneIDs;
	glm::vec4 weights;
};

class Mesh
{
public:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Bone> bones;
	std::unordered_map<std::string, Bone*> boneMap;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Bone> bones);
	void draw(Shader& shader);

private:

	unsigned int VAO, VBO, EBO;

	void setupMesh();
};