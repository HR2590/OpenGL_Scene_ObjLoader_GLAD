
#include "Shader.h"
#include <cstring>
#include "glad/glad.h"
#include <iostream>

using namespace std;

Shader::Shader(const string& InSource, const int& InShaderType): ShaderCreated(0)
{
	if (InSource.empty())return;
	Source = new char[InSource.size() + 1];
	strcpy_s(Source, InSource.size() + 1, InSource.c_str());
	ShaderCreated = glCreateShader(InShaderType);
	glShaderSource(ShaderCreated, 1, &Source, nullptr);
}

Shader::~Shader()
{
	delete[] Source;

}
//Getters
char* Shader::GetSource() const{return Source;}
unsigned int Shader::GetShader() const { return ShaderCreated;}

//Setters
void Shader::SetShaderSource(const string& InSource)
{
	delete[] Source;
	Source = new char[InSource.size() + 1];
	strcpy_s(Source, InSource.size() + 1, InSource.c_str());
	
}



//Methods
void Shader::CreateShader(const int& InShaderType)
{
	ShaderCreated=glCreateShader(InShaderType);
	glShaderSource(ShaderCreated, 1, &Source, nullptr);
}
bool Shader::CompileShader() const
{
	glCompileShader(ShaderCreated);
	GLint success;
	glGetShaderiv(ShaderCreated, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(ShaderCreated, 512, nullptr, infoLog);
		cerr << "Error: Shader compilation failed\n" << infoLog << '\n';
		return false;
	}

	//cout << "Shader compilation successful!\n";
	return true;
}

bool Shader::AttachShader(const int& InProgram) const
{
	glAttachShader(InProgram, GetShader());
	GLint success;
	glGetProgramiv(InProgram, GL_ATTACHED_SHADERS, &success);

	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(ShaderCreated, 512, nullptr, infoLog);
		cerr << "Error: Shader compilation failed\n" << infoLog << '\n';
		return false;
	}

	//cout << "Shader compilation successful!\n";
	return true;

}


void Shader::DeleteShader() const{glDeleteShader(ShaderCreated);}




