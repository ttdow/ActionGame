#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Bone.h"

class Shader;
class Mesh;

class Model
{
public:

	std::vector<Mesh> meshes;

	Model(std::string path);

	void draw(Shader& shader);

private:

	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void traverseTree(aiNode* node, std::unordered_map<std::string, Bone*> boneMap);
};