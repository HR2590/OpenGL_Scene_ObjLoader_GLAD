#include "Texture.h"

#include <iostream>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


using namespace std;

Texture::Texture(const string& InPathImage): texture(0), texUniform(0), textureType(0)
{
	CreateTexture(InPathImage);
}

void Texture::CreateTexture(const string& InPathImage)
{
	//stbi_set_flip_vertically_on_load(true);
	bytes = stbi_load(InPathImage.c_str(), &width_img, &height_img, &pixel_num, 0);
}

void Texture::BindTexture(const int& InTextureType)
{
	textureType = InTextureType;
	glBindTexture(textureType, texture);
}

void Texture::ActiveTexture(const int& InActiveTexture)
{
	glGenTextures(1, &texture);
	glActiveTexture(InActiveTexture);
}

void Texture::SetParameter(const int& InParameterName, const int& InParameter) const
{
	glTexParameteri(textureType, InParameterName, InParameter);
}

void Texture::CreateImage(const int& InFormat) const
{
	glTexImage2D(textureType, 0, InFormat, width_img, height_img, 0, InFormat, GL_UNSIGNED_BYTE, bytes);

}

void Texture::SetUniform(const unsigned int& InShaderProgram)
{
	texUniform = glGetUniformLocation(InShaderProgram, "tex0");
}

Texture::~Texture()
{
	FreeTexture();
}

void Texture::FreeTexture() const
{
	stbi_image_free(bytes);
	Unbind();

}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
