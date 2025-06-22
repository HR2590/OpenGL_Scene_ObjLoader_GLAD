#include "mesh.h"

#include <iostream>
#include <vector>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "ShaderProgram.h"



using namespace std;
using namespace glm;



mesh::mesh(const meshdata& InMeshData,const shadersource& InSource,const ftransform& InTransform, camera& InCamera,const ShaderProgram& InProgram):
	meshBufferData(InMeshData),programID(InProgram.GetprogramID()),
	worldTransform(InTransform), vertexShader(InSource.vertexSource, GL_VERTEX_SHADER),
	fragmentShader(InSource.fragmentSource, GL_FRAGMENT_SHADER), texture(InMeshData.pathTexture)

{
	//Inout Valication
	if (InMeshData.vertices.empty() || InMeshData.indices.empty()||InSource.fragmentSource.empty() || InSource.vertexSource.empty())return;

	//Compile Shaders
	if (!CompileShaders()) return;
	//Program Check
	if (!InProgram.IsProgramAttached())
	{
		if (!AttachShaders()) return;
		if (!InProgram.LinkShaders())return;
		DeleteShaders();
	}

	BindShadersData();
	EnableDepthTest();
	AttachToCamera(InCamera);
}

mesh::~mesh()
{
		glDeleteVertexArrays(1, &meshBufferData.VAO);
		glDeleteBuffers(1, &meshBufferData.VBO);
		glDeleteBuffers(1, &meshBufferData.IBO);
		glDeleteProgram(programID);

}


unsigned int mesh::GetProgramID() const
{
	return programID;
}

void mesh::UseProgram() const
{
	glUseProgram(programID);
}



void mesh::SetModelMatrix() const
{

	GLuint ModelUniform = glGetUniformLocation(programID, "ModelMatrix");
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(modelMatrix));
}

void mesh::SetProjectionMatrix(const mat4& InMatrix)
{
	UseProgram();
	projectionMatrix = InMatrix;
	GLuint projectionUniform = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, value_ptr(projectionMatrix));
}

void mesh::SetViewMatrix(const mat4& InView)
{
	viewMatrix = InView;
	GLuint ViewMatrixUniform = glGetUniformLocation(programID, "viewMatrix");
	glUniformMatrix4fv(ViewMatrixUniform, 1, GL_FALSE, value_ptr(viewMatrix));
}

void mesh::SetViewSpec(const vec3& InPos) const
{

	GLuint viewPosUniform = glGetUniformLocation(programID, "viewPos");
	glUniform3fv(viewPosUniform, 1, value_ptr(InPos));

}

void mesh::SetShininess() const
{
	GLuint shineUniform = glGetUniformLocation(programID, "shininess");
	glUniform1f(shineUniform, shine);
}

void mesh::BindTexture(const int& InTextureNum)
{
	texture.BindTexture(InTextureNum);
}




void mesh::DeleteShaders() const
{
	vertexShader.DeleteShader();
	fragmentShader.DeleteShader();
}

void mesh::DeleteBuffer() const
{
	
		glDeleteVertexArrays(1, &meshBufferData.VAO);
		glDeleteBuffers(1, &meshBufferData.VBO);
		glDeleteProgram(programID);
	

}

void mesh::TexturePrep()
{
	if (meshBufferData.pathTexture.empty()) return;
	//TexturePreparation
	texture.ActiveTexture(GL_TEXTURE0);
	texture.BindTexture(GL_TEXTURE_2D);
	texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture.SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	texture.SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	texture.CreateImage(GL_RGB);
	texture.SetUniform(programID);
	//texture.FreeTexture();
}

bool mesh::AttachShaders() const
{
	return (vertexShader.AttachShader(programID) && fragmentShader.AttachShader(programID));
}

void mesh::BindShadersData()
{
	constexpr unsigned int stride = 11 * sizeof(float);

			glGenVertexArrays(1, &meshBufferData.VAO);
			glGenBuffers(1, &meshBufferData.VBO);
			glGenBuffers(1, &meshBufferData.IBO);


			glBindVertexArray(meshBufferData.VAO);

			glBindBuffer(GL_ARRAY_BUFFER, meshBufferData.VBO);
			glBufferData(GL_ARRAY_BUFFER, meshBufferData.vertices.size() * sizeof(float), meshBufferData.vertices.data(), GL_STATIC_DRAW);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBufferData.IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshBufferData.indices.size() * sizeof(unsigned int), meshBufferData.indices.data(), GL_STATIC_DRAW);



				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);


				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(float)));
				glEnableVertexAttribArray(3);


			glBindVertexArray(0);



}


void mesh::AttachToCamera(camera& InCamera)
{

	InCamera.BindObject(this);
}


bool mesh::CompileShaders() const
{

	return fragmentShader.CompileShader() && vertexShader.CompileShader();

}

void mesh::AddRelativePosition(const vec3& InPosition)
{
	modelMatrix = translate(modelMatrix, InPosition);
	SetModelMatrix();

}

void mesh::SetPosition(const vec3& InPosition)
{
	worldTransform.position = InPosition;
	modelMatrix = mat4(1.0f);
	modelMatrix = translate(modelMatrix, worldTransform.position);
	SetModelMatrix();
}

void mesh::SetRotation(const vec3& InRotation)
{
	worldTransform.rotation = InRotation;
	modelMatrix = mat4(1.0f);
	modelMatrix = rotate(modelMatrix, radians(InRotation.x), vec3(1.0f, 0.0f, 0.0f)); // Rotación en X
	modelMatrix = rotate(modelMatrix, radians(InRotation.y), vec3(0.0f, 1.0f, 0.0f)); // Rotación en Y
	modelMatrix = rotate(modelMatrix, radians(InRotation.z), vec3(0.0f, 0.0f, 1.0f)); // Rotación en Z
	SetModelMatrix();
}

void mesh::SetScale(const vec3& InScale)
{
	worldTransform.scale = InScale;

	modelMatrix = scale(modelMatrix, worldTransform.scale);
	SetModelMatrix();
}

void mesh::SetTransform(const ftransform& InTransform)
{
	worldTransform = InTransform;
	// Reinicia la matriz de modelo a la identidad
	modelMatrix = mat4(1.0f);

	// 1. Aplica la escala
	modelMatrix = scale(modelMatrix, InTransform.scale);

	// 2. Aplica la rotación (en orden X, Y, Z)
	modelMatrix = rotate(modelMatrix, InTransform.rotation.x,vec3(1.0f, 0.0f, 0.0f)); // Rotación en X
	modelMatrix = rotate(modelMatrix, InTransform.rotation.y, vec3(0.0f, 1.0f, 0.0f)); // Rotación en Y
	modelMatrix = rotate(modelMatrix, InTransform.rotation.z, vec3(0.0f, 0.0f, 1.0f)); // Rotación en Z

	// 3. Aplica la traslación
	modelMatrix = translate(modelMatrix, InTransform.position);

	SetModelMatrix();
}

void mesh::SetLightData(const light& InLight,const int Index) const
{
		glUseProgram(programID);
		glBindVertexArray(meshBufferData.VAO);
		string baseName = "lights[" + to_string(Index) + "].";
		GLuint LightPosUniform = glGetUniformLocation(programID, (baseName+"position").c_str());
		glUniform3fv(LightPosUniform, 1, value_ptr(InLight.position));
		GLuint LightColorUniform = glGetUniformLocation(programID, (baseName + "color").c_str());
		glUniform4f(LightColorUniform, InLight.color.x, InLight.color.y, InLight.color.z, InLight.color.w);

		GLuint AmbientUniform = glGetUniformLocation(programID, (baseName + "ambientIntensity").c_str());
		glUniform1f(AmbientUniform, InLight.ambientIntensity);

		GLuint DiffuseUniform = glGetUniformLocation(programID, (baseName + "diffuseIntensity").c_str());
		glUniform1f(DiffuseUniform, InLight.diffuseIntensity);

	
}

light mesh::GetData() const
{
	light empty(vec3(0.0f), vec4(0.0f), 0.0f, 0.0f);
	return empty;
}


void mesh::Draw()
{
			UseProgram();
			TexturePrep();
			glBindVertexArray(meshBufferData.VAO);
			SetTransform(worldTransform);
			SetShininess();
			glDrawElements(GL_TRIANGLES, meshBufferData.indices.size(), GL_UNSIGNED_INT, (int*)NULL);
			glBindVertexArray(0);

}

void mesh::EnableDepthTest()
{

	glEnable(GL_DEPTH_TEST);
}





