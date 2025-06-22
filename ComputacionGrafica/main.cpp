
#include "Shader.h"
#include "ShaderProgram.h"
#include "fstream"
#include "sstream"
#include "glad/glad.h"
#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <GLFW/glfw3.h>

#include "baselight.h"
#include "stb/stb_image.h"
#include "camera.h"
#include "mesh.h"
#include "meshdata.h"





using namespace std;
using namespace glm;


//Functions Declarations
void Framebuffer_size_callback(GLFWwindow* window,const int width,const int height);
bool WindowInitializer(GLFWwindow*& window, int& value1);
string ReadTextFile(const string& FileName);
void processInput(GLFWwindow*& InWindow);


//Global Variables
const unsigned int width = 800;
const unsigned int height = 600;


//Init positions
vec3 cameraInitPosition(0.0f, 0.0f, 30.0f);

vector<ftransform> InitTransforms = {
	ftransform(vec3(0.0f,5.0f,0.0f),vec3(0.0f),vec3(1.0f)), //Light1
	ftransform(vec3(5.0f,5.0f,0.0f),vec3(0.0f),vec3(1.0f)), //Light2
    ftransform(vec3(0.0f,-80.0f,0.0f),vec3(0.0f,radians(90.f),0.0f),vec3(0.05f)), //Carpet
    ftransform(vec3(0.0f,0.0f,5.0f),vec3(radians(0.0f),0.0f,0.0f),vec3(0.5f)), //Dragon
    ftransform(vec3(-1.0f,-1.0f,0.0f),vec3(0.0f),vec3(4.0f)),//JugLeft
    ftransform(vec3(1.0f,-1.0f,0.0f),vec3(0.0f),vec3(4.0f)) //JugRight

};


//Shader source
shadersource normalShader(ReadTextFile("Recursos/shaders/MeshVertex.glsl"), ReadTextFile("Recursos/shaders/MeshFragment.glsl"));
shadersource lightShader(ReadTextFile("Recursos/shaders/AmbientLightVertex.glsl"), ReadTextFile("Recursos/shaders/AmbientLightFragment.glsl"));



int main()
{

	//Window Init
	GLFWwindow* window;
	int value1 = 0;
	if (WindowInitializer(window, value1)) return value1;


    //ShaderPrograms
	ShaderProgram LightProgram;
	ShaderProgram MeshProgram;

    //Camera
	camera cameraWindow(width, height, cameraInitPosition);

	//MeshData
	vector<meshdata> meshdatas =
	{
		meshdata("Recursos/bulb.obj"),  //Light model
		meshdata("Recursos/Carpet.png", "Recursos/Carpet.obj"),
		meshdata("Recursos/Dragon.jpeg", "Recursos/Dragon.obj"),
		meshdata("Recursos/Jug.png", "Recursos/Jug.obj")

	};
	

  


	//Lights
	vector<light> lights = {
			light(InitTransforms.at(0).position, vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.5f, 0.5f), //Light1
			light(InitTransforms.at(1).position, vec4(0.0f, 0.0f, 0.5f, 1.0f),0.5f,0.5f)    //Light2
	};
    vector<mesh*> Lights =
    {
    new baselight(meshdatas.at(0), lightShader,InitTransforms.at(0), cameraWindow,LightProgram,lights.at(0)), //Light1
    new baselight(meshdatas.at(0), lightShader,InitTransforms.at(1), cameraWindow,LightProgram,lights.at(1))  //Light2

    };


    cameraWindow.BindLight(Lights);

	//Meshes

    mesh Carpet(meshdatas.at(1), normalShader, InitTransforms.at(2), cameraWindow, MeshProgram);
	mesh Dragon(meshdatas.at(2), normalShader, InitTransforms.at(3), cameraWindow, MeshProgram);
	mesh Jug1(meshdatas.at(3), normalShader, InitTransforms.at(4), cameraWindow, MeshProgram);
	mesh Jug2(meshdatas.at(3), normalShader, InitTransforms.at(5), cameraWindow, MeshProgram);



   
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
        ShaderProgram::ClearBuffer();

		///RENDERING COMMANDS
		camera::SetRenderingClear();

		
		cameraWindow.CameraMatrix(45.0f, 0.1f, 100.f);
		cameraWindow.CameraInput(window);
	

        glfwSwapBuffers(window);
		glfwPollEvents();
        
	}
   
	cameraWindow.UnbindAll();
    glfwTerminate();
    return 0;
}




//Functions Definitions

bool WindowInitializer(GLFWwindow*& window, int& value1)
{
	//Initialization
	glfwInit(); //Inicia GFLW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Define version con la que se trabaja max y min
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Define que tipo de compatibilidad correra solamente Coreesla mas segura



	window = glfwCreateWindow(width, height, "Computacion Grafica OpenGL Proyecto Final", nullptr, nullptr);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	if (!window)
	{
		std::cout << "Failed to create Window! \n";
		glfwTerminate();
		value1 = -1;
		return true;
	}

	glfwMakeContextCurrent(window); //Especifica en que ventana deseamos trabajar


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Garantiza que inicializo bien
	{
		std::cout << "Failed to create Window! \n";
		value1 = -1;
		return true;
	}

	glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);
	return false;

}

void Framebuffer_size_callback(GLFWwindow* window, const int InWidth,const int InHeight)
{
	glViewport(0, 0, InWidth, InHeight);
}

string ReadTextFile(const string& FileName) {

	ifstream File(FileName);
	if (!File.is_open())
		return "Archivo no encontrado";

	stringstream stringbuffer{};
	stringbuffer << File.rdbuf();
	File.close();
	return stringbuffer.str();
}

void processInput(GLFWwindow*& InWindow)
{
    if (glfwGetKey(InWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(InWindow, true);

}

