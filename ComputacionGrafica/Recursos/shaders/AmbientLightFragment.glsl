#version 330 core
out vec4 FragColor;

uniform vec4 lightColor;
uniform float lightColorIntensity;

void main()
{
	FragColor=lightColor*lightColorIntensity;
}

