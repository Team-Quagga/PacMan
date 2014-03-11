#include <iostream>

#include "Engine\Engine.h"
#include "Engine\Camera.h"

#include "MenuScreen.h"
#include "GameScreen.h"


#define WIDTH 1280
#define HEIGHT 720

int main()
{
	GLFWwindow* window = Init("Pacman", WIDTH, HEIGHT);
	ScreenManager manager;
	Input* i = Input::GetInstance();
	glfwSetKeyCallback(window, &Input::KeyCallback);
	glfwSetMouseButtonCallback(window, &Input::MouseCallback);

	//GameScreen menu(&manager, window);
	MenuScreen menu(&manager, window);
	i->Register(menu);
	manager.AddScreen(&menu);
	manager.SetFocus(&menu);



	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1, 0.1, 0.1, 1);
		//glEnable(GL_DEPTH_TEST);

		//Wireframe
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Disable doublesided
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

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