#pragma once
#include <string>
#include "glad/glad.h"

using namespace std;
class Texture
{
	int width_img, height_img, pixel_num,textureType;
	GLuint texture;
	GLuint texUniform;
	unsigned char* bytes;
public:
	explicit Texture(const string& InPathImage);
	void CreateTexture(const string& InPathImage);
	void BindTexture(const int& InTextureType);
	void ActiveTexture(const int& InActiveTexture);
	void SetParameter(const int& InParameterName, const int& InParameter) const;
	void CreateImage(const int& InFormat) const;
	void SetUniform(const unsigned int& InShaderProgram);
	~Texture();
	void FreeTexture() const;
	void Unbind()const;


};

