#include "GameScreen.h"


GameScreen::GameScreen(ScreenManager* manager, GLFWwindow* window)
	:IScreen(manager, window)
{
	LoadWorld("bilder/map1.bmp");
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


bool GameScreen::LoadWorld(const char* path)
{
	if(!mWorld.LoadMap(path))
		return false;

	mPlayer = Player(glm::vec2(mWorld.mPlayerPosXY[0],mWorld.mPlayerPosXY[1]));
	mPlayer.SetKeyFunction([&](GLFWwindow* w, int key, int scancode, int action, int mods)->void
	{
		if(!action == GLFW_PRESS)
			return;

		glm::vec2 nPosition = mPlayer.GetPosition();
		glm::vec2 direction; //= glm::vec2(mCamera.GetDirection().x, mCamera.GetDirection().z);
		glm::vec3 right3; //= glm::cross(mCamera.GetDirection(), glm::vec3(0,1,0));
		glm::vec2 right = glm::vec2(right3.x, right3.z);
		switch (key)
		{
		case GLFW_KEY_W:
			{
				nPosition += direction;
			}break;
		case GLFW_KEY_A:
			{
				nPosition -= right;
			}break;
		case GLFW_KEY_S:
			{
				nPosition -= direction;
			}break;
		case GLFW_KEY_D:
			{
				nPosition += right;
			}break;
		default:
			break;
		}
		//mWorld.GetTile(
	});


}