#pragma once

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glad/glad.h>

class Texture
{
public:

	Texture();

	void load(std::string path, GLint interpolation);

	void bind() { glBindTexture(GL_TEXTURE_2D, this->textureID); }
	void unbind() { glBindTexture(GL_TEXTURE_2D, textureID); }

	glm::ivec2 getDimensions() { return glm::ivec2(this->width, this->height); };
	std::string getPath() { return this->path; }
	GLint getInterpolation() { return this->interpolation;  }

private:

	unsigned int textureID;

	int width;
	int height;
	int nrChannels;

	std::string path;
	GLint interpolation;
};