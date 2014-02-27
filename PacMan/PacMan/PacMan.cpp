#include <iostream>
#include "Engine\Engine.h"
#include "MenuScreen.h"
#include "GameScreen.h"

int main()
{
	GLFWwindow* window = Init("Pacman", 1280, 720);
	ScreenManager manager;
	Input* i = Input::GetInstance();
	glfwSetKeyCallback(window, &Input::KeyCallback);
	glfwSetMouseButtonCallback(window, &Input::MouseCallback);

	GameScreen menu(&manager, window);
	i->Register(menu);
	manager.AddScreen(&menu);
	manager.SetFocus(&menu);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0,0,0,0);
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