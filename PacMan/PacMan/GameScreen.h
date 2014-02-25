#pragma once
#include "engine\iscreen.h"
class GameScreen: public IScreen
{
public:
	GameScreen(ScreenManager* manager, GLFWwindow* window);
	~GameScreen(void);

	void Draw();
	void Update();
};

