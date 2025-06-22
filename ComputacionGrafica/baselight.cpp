#include "baselight.h"

#include <glm/gtc/type_ptr.hpp>


baselight::baselight(const meshdata& InMeshData, const shadersource& InSource, const ftransform& InTransform,
                     camera& InCamera,const ShaderProgram& InProgram, const light& InLight)
: mesh(InMeshData, InSource, InTransform, InCamera, InProgram),data(InLight)
{

}

void baselight::SetLightColor(const vec4& InColor, const string& InName)
{
	data.color = InColor;
	GLuint ColorUniform = glGetUniformLocation(programID, "lightColor");
	glUniform4fv(ColorUniform,1, value_ptr(InColor));

	GLuint IntensityUniform = glGetUniformLocation(programID, "lightColorIntensity");
	glUniform1f(IntensityUniform, data.ambientIntensity);
}

void baselight::SetLightPosition(const vec3& InPosition, const string& InName)
{
	data.position = InPosition;
	GLuint LightPosUniform = glGetUniformLocation(programID, InName.c_str());
	glUniform3fv(LightPosUniform, 1, value_ptr(InPosition));
}

void baselight::SetLightData(const light& InLight, const int Index) const
{
	glUseProgram(programID);
	glBindVertexArray(meshBufferData.VAO);
	GLuint LightColorUniform = glGetUniformLocation(programID, "lightColor");
	glUniform4fv(LightColorUniform,1, value_ptr(data.color));

	GLuint IntensityUniform = glGetUniformLocation(programID, "lightColorIntensity");
	glUniform1f(IntensityUniform, data.ambientIntensity);

}

void baselight::SetViewSpec(const vec3& InPos) const
{

}

void baselight::SetShininess() const
{

}

light baselight::GetData() const
{
	return data;
}

