#pragma once
#include "engine\iscreen.h"
#include "Player.h"
#include "Engine\Camera.h"
#include "Model.h"
#include "Engine\Engine.h"
#include "AudioSource.h"
#include "AudioEngine.h"


class GameScreen: public IScreen
{
	World mWorld;
	Camera* mCamera;
	AudioEngine* mAEngine;
	// Soundtest
	//AudioSource* mASource;
public:
	GameScreen(ScreenManager* manager, GLFWwindow* window);
	~GameScreen(void);

	void Draw();
	void Update();
	bool LoadWorld(const char* path);
};

