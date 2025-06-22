#pragma once
#include <memory>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "observer.h"

class mesh;
using namespace std;
using namespace glm;

class camera
{
	int width;
	int height;
	vec3 position;
	vec3 orientation = vec3(0.0f, 0.0f, -1.0f);
	float speed = 0.5f;

	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);


	vec3 right = normalize(cross(orientation, vec3(0.0f, 1.0f, 0.0f)));
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	
	double lastPositionX;
	double lastPositionY;

	observer Observer;
public:

	camera(const int& InWidth,const int& InHeight, const vec3& InPosition);
	void CameraMatrix(const float& InFOV, const float& InNearPlane,const float& InFarPlane);
	void CameraInput(GLFWwindow* window);
	void BindObject(mesh* InMesh);
	void BindLight(const vector<mesh*>& InLight);
	void UnbindAll()const;
	//Static Functions
	static void SetRenderingClear();


};





