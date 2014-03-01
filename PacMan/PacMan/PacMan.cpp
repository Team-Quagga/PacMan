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
	Model model = *Engine::LoadModel("../../../content/blender_cube.obj");
	Camera camera(new Viewport(Rect(WIDTH, HEIGHT)));
		Viewport* viewport = camera.GetViewport();
		viewport->BuildProjectionMatrix(3.14f / 3.0f, WIDTH / HEIGHT, 0.1f, 1000.0f);
	camera.SetRotation(glm::vec3(0));


	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1, 0.1, 0.1, 1);
		/* update */
		manager.Update();
		/* Draw */
		manager.Draw();


		camera.Update();
		model.Draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	return 0;
}