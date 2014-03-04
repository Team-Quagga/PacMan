#pragma once
#include "engine\iscreen.h"
#include "World.h"
#include "Player.h"
#include "Engine\Camera.h"

class GameScreen: public IScreen
{
	World mWorld;
	Player mPlayer;
	Camera* mCamera;
public:
	GameScreen(ScreenManager* manager, GLFWwindow* window);
	~GameScreen(void);

	void Draw();
	void Update();
	bool LoadWorld(const char* path);
};

