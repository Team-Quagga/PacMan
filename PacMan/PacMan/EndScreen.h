#pragma once
#include "engine\iscreen.h"
#include "Engine\Sprite.h"
class EndScreen :
	public IScreen
{
	Sprite mEndSprite;
public:
	EndScreen(ScreenManager* manager, GLFWwindow* window);
	~EndScreen(void);
	
	void Draw();
	void Update();
};

