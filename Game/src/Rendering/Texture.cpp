#define STB_IMAGE_IMPLEMENTATION
#include "STBI/stb_image.h"

#include "Texture.h"

Texture::Texture()
{
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->nrChannels = 0;
	this->path = "";
	this->interpolation = 0;
}

void Texture::load(std::string path, GLint interpolation)
{
	this->path = path;
	this->interpolation = interpolation;

	glGenTextures(1, &this->textureID);
	this->bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->interpolation);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->interpolation);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(this->path.c_str(), &this->width, &this->height, &this->nrChannels, 0);

	if (data)
	{
		GLuint format = GL_RGB;
		switch (this->nrChannels)
		{
		case 4:
			format = GL_RGBA;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 2:
			format = GL_RG;
			break;
		case 1:
			format = GL_RED;
			break;
		default:
			std::cout << "Invalid texture format: " << path << "\n";
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	this->unbind();
	stbi_image_free(data);
}