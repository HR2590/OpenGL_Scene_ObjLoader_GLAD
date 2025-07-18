#include "Camera.h"

class mesh;

camera::camera(const int& InWidth, const int& InHeight, const vec3& InPosition):width(InWidth),height(InHeight),position(InPosition){}

void camera::CameraMatrix(const float& InFOV, const float& InNearPlane, const float& InFarPlane)
{
	view = lookAt(position, position + orientation, up);
	projection= perspective(radians(InFOV), (float)(width / height), InNearPlane, InFarPlane);
	

	Observer.Draw(projection,view,position);
}

void camera::CameraInput(GLFWwindow* window)
{

	if(glfwGetKey(window, GLFW_KEY_W))position += speed * orientation;
	if(glfwGetKey(window, GLFW_KEY_A))position += speed *-normalize( cross(orientation,up));
	if(glfwGetKey(window, GLFW_KEY_S))position += speed * -orientation;
	if(glfwGetKey(window, GLFW_KEY_D))position += speed * normalize(cross(orientation, up));
	if(glfwGetKey(window, GLFW_KEY_Q))position += speed * up;
	if(glfwGetKey(window, GLFW_KEY_E))position += speed * -up;
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))speed = 0.1f;
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))speed = 0.3f;

	if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
	{

		double currentX, currentY;
		glfwGetCursorPos(window, &currentX, &currentY);
		double deltaX=currentX- lastPositionX;
		double deltaY =  currentY- lastPositionY;


		orientation = rotate(orientation, -radians((float)deltaX * speed), up);
		orientation = rotate(orientation, -radians((float)deltaY * speed), right);

		lastPositionX = currentX;
		lastPositionY = currentY;
	}
	if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE)glfwGetCursorPos(window, &lastPositionX, &lastPositionY);

	
}

void camera::BindObject(mesh* InMesh)
{
	if (!InMesh)return;
	Observer.Bind(InMesh);
}

void camera::BindLight(const vector<mesh*>& InLight)
{
	for (auto* lights:InLight)
	{	
		Observer.BindLight(lights);
	}
	
}

void camera::UnbindAll() const
{
	Observer.UnbindAll();
}

void camera::SetRenderingClear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
