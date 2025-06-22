#include "ShaderProgram.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"

using namespace std;
using namespace glm;


ShaderProgram::ShaderProgram(): Program(glCreateProgram()){}

void ShaderProgram::UseProgram() const
{
    glUseProgram(Program);
}

unsigned int ShaderProgram::GetprogramID() const
{
    return Program;
}

bool ShaderProgram::IsProgramAttached() const
{
    GLint success=0;
    glGetProgramiv(Program, GL_ATTACHED_SHADERS, &success);
    return success;
}

bool ShaderProgram::LinkShaders() const
{
    glLinkProgram(Program);
    GLint success=0;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(Program, 512, NULL, infoLog);
        cout << "Error linking shader program: " << infoLog << endl;
        return false;
    }

    return true;
}


//Static Methods
    void ShaderProgram::UnBindBuffersData()
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    
    }

    void ShaderProgram::ClearBuffer()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void ShaderProgram::DrawInWireMode()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }




