#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 texCoord;
out vec3 normal;
out vec3 wposition;
out vec3 pixelToCam;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 viewPos;


void main()
{
wposition = vec3(ModelMatrix * vec4(aPos, 1.0f));
gl_Position = projectionMatrix*viewMatrix*vec4(wposition,1.0);

ourColor=aColor;
texCoord=aTex;

normal = mat3(transpose(inverse(ModelMatrix)))*aNormal; 
pixelToCam = viewPos;


}