#include <iostream>
#include "Engine\Engine.h"

int main()
{
	GLFWwindow* window = Init("Pacman", 1280, 720);
	ScreenManager manager;

	while(!glfwWindowShouldClose(window))
	{
		/* update */
		manager.Update();
		/* Draw */
		manager.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	return 0;
}