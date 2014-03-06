#pragma once
#include "engine\iscreen.h"
#include "World.h"
#include "Player.h"
#include "Engine\Camera.h"
#include "Model.h"
#include "Engine\Engine.h"
#include "AudioSource.h"
#include "AudioEngine.h"

class GameScreen: public IScreen
{
	World mWorld;
	Player mPlayer;
	Camera* mCamera;
	Model mModel;
	AudioEngine* mAEngine;
	// Soundtest
	//AudioSource* mASource;
	bool play;
public:
	GameScreen(ScreenManager* manager, GLFWwindow* window);
	~GameScreen(void);

	void Draw();
	void Update();
	bool LoadWorld(const char* path);
};

