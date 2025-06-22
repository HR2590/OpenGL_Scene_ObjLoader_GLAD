#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 viewPos;


void main()
{

gl_Position = projectionMatrix*viewMatrix*ModelMatrix*vec4(aPos,1.0);

}