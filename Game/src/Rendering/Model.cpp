#include <iostream>

#include "Model.h"
#include "Mesh.h"

Model::Model(std::string path)
{
	loadModel(path);
}

void Model::draw(Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].draw(shader);
}

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

glm::mat4 convertMat4ToGLMFormat(aiMatrix4x4 from)
{
	glm::mat4 to;

	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;

	return to;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.boneIDs[0] = -1;
		vertex.boneIDs[1] = -1;
		vertex.boneIDs[2] = -1;
		vertex.boneIDs[3] = -1;

		vertex.weights[0] = 0.0f;
		vertex.weights[1] = 0.0f;
		vertex.weights[2] = 0.0f;
		vertex.weights[3] = 0.0f;
		
		glm::vec3 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		vertex.position = position;

		if (mesh->HasNormals())
		{
			glm::vec3 normal;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			vertex.normal = normal;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texCoord;
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = texCoord;
		}
		else
			vertex.texCoord = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Check if this mesh is rigged for animation
	if (mesh->HasBones())
	{
		std::vector<Bone> bones;
		unsigned int numBones = mesh->mNumBones;
		bones.reserve(numBones);

		std::unordered_map<std::string, Bone*> boneMap;
		boneMap.reserve(numBones);
		
		// Loop through each bone in the mesh
		for (unsigned int i = 0; i < numBones; i++)
		{
			bones.emplace_back();

			bones[i].name = mesh->mBones[i]->mName.C_Str();
			bones[i].id = i;
			bones[i].numWeights = mesh->mBones[i]->mNumWeights;
			bones[i].offset = convertMat4ToGLMFormat(mesh->mBones[i]->mOffsetMatrix);

			boneMap.emplace(bones[i].name, &bones[i]);

			// Loop through all the vertices affected by this bone
			for (unsigned int j = 0; j < bones[i].numWeights; j++)
			{
				unsigned int vertexID = mesh->mBones[i]->mWeights[j].mVertexId;

				// Add the first four bone weights to the vertex
				for (unsigned int k = 0; k < 4; k++)
				{
					if (vertices[vertexID].boneIDs[k] == -1)
					{
						vertices[vertexID].boneIDs[k] = bones[i].id;
						vertices[vertexID].weights[k] = mesh->mBones[i]->mWeights[j].mWeight;
						break;
					}
				}
			}
		}

		//traverseTree(scene->mRootNode, bones);
		std::cout << scene->mRootNode->mName.C_Str() << "(";
		std::cout << scene->mRootNode->mNumChildren << "): ";
		std::cout << scene->mRootNode->mChildren[0]->mName.C_Str() << ", ";
		std::cout << scene->mRootNode->mChildren[1]->mName.C_Str() << ", ";
		std::cout << scene->mRootNode->mChildren[2]->mName.C_Str() << ", ";
		std::cout << std::endl;

		return Mesh(vertices, indices, bones);
	}

	return Mesh(vertices, indices);
}

void Model::traverseTree(aiNode* node, std::unordered_map<std::string, Bone*> boneMap)
{
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		node->mChildren[0]->mName.C_Str();
	}
}