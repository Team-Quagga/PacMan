#pragma once
#include "engine\iscreen.h"
#include "World.h"

class GameScreen: public IScreen
{
	World mWorld;
public:
	GameScreen(ScreenManager* manager, GLFWwindow* window);
	~GameScreen(void);

	void Draw();
	void Update();
};

