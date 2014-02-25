#include "GLHeader.h"

void FocusWindow(GLFWwindow* window)
{
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
}

GLFWwindow* CreateWindow(const char* tile, int width, int height)
{
	GLFWwindow* window = nullptr;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, tile, NULL /*for fullscreen: glfwGetPrimaryMonitor()*/, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	return window;
}

GLFWwindow*  Init(const char* tile, int width, int height)
{
	GLFWwindow* window;
	//Set callback function so glfw know where do call if an error occured, can be set before init
	//glfwSetErrorCallback(error_callback);

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	if ((window = CreateWindow(tile, width, height)) == nullptr)
		return nullptr;


	FocusWindow(window);

	if (glewInit() != GLEW_OK)
		return nullptr;

	return window;
}