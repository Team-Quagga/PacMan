#include "GameScreen.h"
#include <cstdio>
#include <stdio.h>
#include <iostream>

GameScreen::GameScreen(ScreenManager* manager, GLFWwindow* window)
	:IScreen(manager, window)//mAEngine(nullptr),mASource("WAVE/sound.wav", glm::vec3(1,1,1))
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);// sätt i engine
	glfwSetCursorPos(mWindow, width / 2, height / 2);

	mCamera = new Camera(new Viewport(0,0, width, height));
		Viewport* viewport = mCamera->GetViewport();
		viewport->BuildProjectionMatrix(60.0f, (float)width / (float)height, 0.1f, 250.0f);

		
	mCamera->SetOrientation(0, 0.1);
	mCamera->SetPosition(glm::vec3(0.0, 0.0, 0.0));
	play = false;
	mKeyPress = [&](GLFWwindow* w, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(w, true);
	// Soundtest
		//if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		//	play = true;
	};
	mModel = *Engine::LoadModel("../../content/blender_suzanne.obj", 0.1);
	mAEngine = new AudioEngine(mCamera);
	// Soundtest
	//mASource = new AudioSource(mAEngine, "WAVE/Sound.wav", glm::vec3(0,0,0));
	
	mAEngine->Update();
	LoadWorld("bilder/map1.bmp");
}


GameScreen::~GameScreen(void)
{
	delete mCamera;
}

void GameScreen::Draw()
{
	glEnable(GL_DEPTH_TEST);
	mModel.Draw(&glm::mat4(1), mCamera->GetViewMatrix(), mCamera->GetProjMatrix());
	glDisable(GL_DEPTH_TEST);
}

void GameScreen::Update()
{
	static float horizontalAngle;
	// Initial vertical angle : none
	static float verticalAngle;
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	static double oxpos = 1280/2, oypos = 720/2;
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);


	// Compute new orientation
	horizontalAngle -= (oxpos-xpos)*0.1;//float(1024/2 - xpos );
	verticalAngle   -= (oypos-ypos)*0.1;//float( 768/2 - ypos );


	mCamera->Update();
	// Reset mouse position for next frame
	glfwSetCursorPos(mWindow, 1280/2, 720/2);
	if (verticalAngle > 15.0 / 2) verticalAngle = 15.0 / 2;
	if (verticalAngle < -15.0 / 2) verticalAngle = -15.0 / 2;

	glm::vec3 forward = glm::vec3(0, 0, 1) * mCamera->orientation;
	glm::vec3 strafe = glm::vec3(1, 0, 0) * mCamera->orientation;
	glm::vec3 position = mCamera->position;
	
	// Move forward
	if (glfwGetKey(mWindow,  GLFW_KEY_W ) == GLFW_PRESS)
	{
		position -= forward * deltaTime;
	}
	// Move backward
	if (glfwGetKey(mWindow,  GLFW_KEY_S ) == GLFW_PRESS)
	{
		position += forward * deltaTime;
	}
	// Strafe right
	if (glfwGetKey(mWindow,  GLFW_KEY_A ) == GLFW_PRESS)
	{
		position -= strafe * deltaTime;
	}
	// Strafe left
	if (glfwGetKey(mWindow,  GLFW_KEY_D ) == GLFW_PRESS)
	{
		position += strafe * deltaTime;
	}

	mCamera->SetPosition(position);
	mCamera->SetOrientation(verticalAngle, horizontalAngle);
	//mCamera->LookAt(glm::vec3(0, 0, 0)); Not working yet
		
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	mCamera->Update();
	mAEngine->Update();
	// Soundtest
	//if(play) 
	//{
	//	mASource->Play();
	//	play = false;
	//}
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