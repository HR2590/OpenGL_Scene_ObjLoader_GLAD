#include "Texture.h"

#include <iostream>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


using namespace std;

Texture::Texture(const string& InPathImage): texture(0), texUniform(0), textureType(0)
{
	if (InPathImage.empty()) return;
	LoadImgTexture(InPathImage);

	GenerateTexture(GL_TEXTURE_2D);

	SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	BindTexture();

	

	CreateImage(GL_RGB);
	FreeTexture();
	
}

void Texture::LoadImgTexture(const string& InPathImage)
{
	//stbi_set_flip_vertically_on_load(true);
	
	bytes = stbi_load(InPathImage.c_str(), &width_img, &height_img, &pixel_num, 0);
}

void Texture::BindTexture()
{
	glBindTexture(textureType, texture);
}

void Texture::ActiveTexture(int InTextureUnit)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
}

void Texture::GenerateTexture(const int& InTextureType)
{
	textureType = InTextureType;
	glGenTextures(1, &texture);
}

void Texture::SetParameter(const int& InParameterName, const int& InParameter) const
{
	glTexParameteri(textureType, InParameterName, InParameter);
}

void Texture::CreateImage(const int& InFormat) const
{

	if (bytes)
	{
		glTexImage2D(textureType, 0, InFormat, width_img, height_img, 0, InFormat, GL_UNSIGNED_BYTE, bytes);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

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


}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
