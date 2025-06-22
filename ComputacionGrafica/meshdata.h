#pragma once
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

void processNode(aiNode* node, const aiScene* scene, vector<float>& vertices, vector<unsigned int>& indices);
bool loadModel(const string& filepath, vector<float>& vertices, vector<unsigned int>& indices);
void processMesh(aiMesh* mesh, vector<float>& vertices, vector<unsigned int>& indices);


struct meshdata
{
	meshdata(const string& InPathText,const string& InPathModel);
	meshdata(const string& InPathModel);
	meshdata(const vector<float>& InVertices, const vector<unsigned int>& InIndices);
	vector<float> vertices;
	vector<unsigned int> indices;
	string pathTexture="";
	string pathModel="";
	GLuint VAO, VBO, IBO;
};

struct shadersource
{
	shadersource(const string& InVertexSource, const string& InFragmentSource);
	string vertexSource;
	string fragmentSource;
};


struct light
{
	light(const vec3& InPosition,const vec4& InColor,const float& InAmbient,const float& InDiffuse);
	vec3 position;
	vec4 color;
	float ambientIntensity;
	float diffuseIntensity;

};

struct spotlightdata
{
	spotlightdata(const vec3& InPosition, const vec4& InColor, const float& InAmbient, const float& InDiffuse,const vec3& InDirection,
	const float& InCutOff, const float& InOuterCutOff);
	light lightdata;
	vec3 direction;
	float cutOff;
	float outerCutOff;

};

struct ftransform
{
	ftransform(const vec3& InPosition, const vec3& InRotation,const vec3& InScale);
	vec3 position = vec3(0.0f);
	vec3 rotation = vec3(0.0f);
	vec3 scale = vec3(0.0f);

};
/*
void processMesh(aiMesh* InMesh, vector<float>& InVertices, vector<float>& InColors, vector<float>& InTexCoords, vector<float>& InNormals);
void processNode(aiNode* InNode, const aiScene* InScene, vector<float>& InVertices, vector<float>& InColors, vector<float>& InTexCoords, vector<float>& InNormals);
bool loadModel(const string& InFilepath, vector<float>& InVertices, vector<float>& InColors, vector<float>& InTexCoords, vector<float>& InNormals);
*/