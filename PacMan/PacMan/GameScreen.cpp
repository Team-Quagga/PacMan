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
	mKeyPress = [&](GLFWwindow* w, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(w, true);
	// Soundtest
		//if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		//	play = true;
	};

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

	glm::mat4 transformM = glm::mat4(1);
	transformM[3][0] = 1;
	transformM[3][1] = 0;

	glm::mat4 transformM2 = glm::mat4(1);
	transformM2[3][0] = -5;
	transformM2[3][1] = 0;
	
	//mModel1.Draw(&glm::mat4(1), mCamera->GetViewMatrix(), mCamera->GetProjMatrix());
	//mModel.Draw(&transformM, mCamera->GetViewMatrix(), mCamera->GetProjMatrix());
	
	//mModel.Draw(&transformM2, mCamera->GetViewMatrix(), mCamera->GetProjMatrix());
	mWorld.Draw(*mCamera->GetViewMatrix(), *mCamera->GetProjMatrix());
	glDisable(GL_DEPTH_TEST);
}

void GameScreen::Update()
{
	mPlayer->Update(mWindow);
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

	mPlayer = new Player(mCamera, glm::vec2(mWorld.mPlayerPosXY[0],mWorld.mPlayerPosXY[1]));
	Input::GetInstance()->Register(*mPlayer);
}