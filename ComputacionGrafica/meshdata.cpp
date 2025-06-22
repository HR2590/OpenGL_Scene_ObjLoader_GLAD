#include "meshdata.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/fwd.hpp>

#include <glm/gtc/matrix_transform.hpp>



meshdata::meshdata(const string& InPathText, const string& InPathModel)
{
    if (!loadModel(InPathModel, vertices, indices)) return;

    pathTexture = InPathText;
    pathModel = InPathModel;

}

meshdata::meshdata(const string& InPathModel)
{
    if (!loadModel(InPathModel, vertices, indices)) return;
    pathModel = InPathModel;
}

meshdata::meshdata(const vector<float>& InVertices, const vector<unsigned int>& InIndices)
{
    vertices = InVertices;
    indices = InIndices;

}

shadersource::shadersource(const string& InVertexSource, const string& InFragmentSource)
{
	vertexSource = InVertexSource;
	fragmentSource = InFragmentSource;
}

light::light(const vec3& InPosition, const vec4& InColor,const float& InAmbient, const float& InDiffuse)
{
	position = InPosition;
	color = InColor;
	ambientIntensity = InAmbient;
	diffuseIntensity = InDiffuse;
}

spotlightdata::spotlightdata(const vec3& InPosition, const vec4& InColor, const float& InAmbient,
	const float& InDiffuse,const vec3& InDirection,const float& InCutOff, const float& InOuterCutOff):lightdata(InPosition,InColor,InAmbient,InDiffuse)
{
	direction = InDirection;
	cutOff=cos(InCutOff);       
	outerCutOff=cos(InOuterCutOff);
}

ftransform::ftransform(const vec3& InPosition, const vec3& InRotation, const vec3& InScale)
{
	position = InPosition;
	rotation = InRotation;
	scale = InScale;
	
}



// Función para procesar el mesh de Assimp y extraer vértices intercalados con posiciones, colores, UVs, normales e índices
void processMesh(aiMesh* mesh, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    // Extraer vértices, normales, colores y coordenadas UV intercalados
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Posiciones (x, y, z)
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // Colores (r, g, b)
        if (mesh->HasVertexColors(0)) {
            vertices.push_back(mesh->mColors[0][i].r);
            vertices.push_back(mesh->mColors[0][i].g);
            vertices.push_back(mesh->mColors[0][i].b);
        }
        else {
            vertices.push_back(1.0f);  // Color blanco por defecto
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
        }

        // Coordenadas de textura (u, v)
        if (mesh->mTextureCoords[0]) { // Soportamos solo el primer conjunto de UV
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
        else {
            vertices.push_back(0.0f); // UV por defecto
            vertices.push_back(0.0f);
        }

        // Normales (nx, ny, nz)
        if (mesh->HasNormals()) {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        }
        else {
            vertices.push_back(0.0f); // Normal por defecto
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    // Extraer los índices de las caras
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

// Función para procesar un nodo del modelo Assimp
void processNode(aiNode* node, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    // Procesar cada mesh que contenga el nodo actual
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, vertices, indices);
    }

    // Procesar nodos hijos
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, vertices, indices);
    }
}

// Función para cargar el modelo con Assimp y extraer la información en un vector de vértices intercalados e índices
bool loadModel(const std::string& filepath, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return false;
    }

    // Procesar el nodo raíz
    processNode(scene->mRootNode, scene, vertices, indices);

    return true;
}