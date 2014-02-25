#include "GameScreen.h"


GameScreen::GameScreen(ScreenManager* manager, GLFWwindow* window)
	:IScreen(manager, window)
{

}


GameScreen::~GameScreen(void)
{
}

void GameScreen::Draw()
{
}

void GameScreen::Update()
{
	if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(mWindow, true);
}