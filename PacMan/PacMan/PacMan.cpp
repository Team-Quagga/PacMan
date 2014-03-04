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

	GameScreen menu(&manager, window);
	i->Register(menu);
	manager.AddScreen(&menu);
	manager.SetFocus(&menu);

	
	//=============================
	//Graphics* graphics = Engine::GetGraphics(); //TODO: Fix link error that appear for some reason..

	/*Model model = *Engine::LoadModel("../../../content/blender_sphere.obj", 0.1);
	Camera camera(new Viewport(Rect(WIDTH, HEIGHT)));
		Viewport* viewport = camera.GetViewport();
		viewport->BuildProjectionMatrix(60.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 250.0f);

	camera.SetRotation(glm::vec3(0, 0.1, 0));
	camera.SetPosition(glm::vec3(0.0, 0.1, 0.5));*/




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