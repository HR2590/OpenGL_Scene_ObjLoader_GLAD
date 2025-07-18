#pragma once
#include <glm/vec3.hpp>
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include "meshdata.h"
#include "ShaderProgram.h"


class camera;

using namespace std;
using namespace glm;


class mesh
{
protected:
	//Data
	meshdata meshBufferData;
	unsigned int programID;
	ftransform worldTransform;
	float shine = 32.0f;

	//Components
	Shader vertexShader;
	Shader fragmentShader;
	Texture texture;

	//Internal matrix
	mat4 modelMatrix = mat4(1.0f);
	mat4 projectionMatrix = mat4(1.0f);
	mat4 viewMatrix = mat4(1.0f);

	//Internal Functions
	bool CompileShaders()const;
	void BindTexture();
	bool AttachShaders() const;
	void DeleteShaders()const;
	void DeleteBuffer()const;
	void TexturePrep();
	void BindShadersData();
	void AttachToCamera(camera& InCamera);
	

	

public:
	mesh(const meshdata& InMeshData,const shadersource& InSource,const ftransform& InTransform, camera& InCamera,const ShaderProgram& InProgram);
	virtual ~mesh();

	//Functions
	unsigned int GetProgramID() const;
	void UseProgram() const;
	void SetModelMatrix() const;
	void SetProjectionMatrix(const mat4& InMatrix);
	void SetViewMatrix(const mat4& InView);
	virtual void SetViewSpec(const vec3& InPos) const;
	virtual void SetShininess()const;
	void AddRelativePosition(const vec3& InPosition);
	void SetPosition(const vec3& InPosition);
	void SetRotation(const vec3& InRotation);
	void SetScale(const vec3& InScale);
	void SetTransform(const ftransform& InTransform);
	virtual void SetLightData(const light& InLight,const int Index) const;
	virtual light GetData() const;

	void Draw();
	

	static void EnableDepthTest();

};






