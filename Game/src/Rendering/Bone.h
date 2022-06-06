#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

class Bone
{
public:

	unsigned int id;
	std::string name;
	unsigned int numWeights;

	std::vector<std::pair<unsigned int, float>> weights;

	std::vector<Bone> children;
	glm::mat4 offset;

private:

};