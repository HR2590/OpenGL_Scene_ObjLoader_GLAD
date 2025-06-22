#pragma once
#include <glm/fwd.hpp>
#include "meshdata.h"

using namespace std;
using namespace glm;


class ShaderProgram
{
    //Program Variables
    unsigned int Program;

public:
    explicit ShaderProgram();

    //Getters
    void UseProgram()const;
    unsigned int GetprogramID()const;
    bool IsProgramAttached()const;
    bool LinkShaders()const;


    //Static Methods
   
    static void UnBindBuffersData();
    static void ClearBuffer();
    static void DrawInWireMode();

    
};
