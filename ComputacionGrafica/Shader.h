#pragma once
#include <string>

using namespace std;

class Shader final
{
    //ShaderSource
    char* Source;
    //Shaders to compile
    unsigned int ShaderCreated;

public:
    explicit Shader(const string& InSource,const int& InShaderType);
    ~Shader();

    //Getters
    char* GetSource()const;
    unsigned int GetShader()const;

    //Setters
    void SetShaderSource(const string& InSource);
    
    //Methods
    void CreateShader(const int& InShaderType);
	bool CompileShader() const;
    bool AttachShader(const int& InProgram) const;

    void DeleteShader()const;



};



