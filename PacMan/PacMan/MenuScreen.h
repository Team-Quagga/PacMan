#pragma once
#include "Engine\IScreen.h"
#include "Engine\Button.h"
class MenuScreen: public IScreen
{
	Button start, exit;
	Sprite sstart, sexit, sbackgound;
	bool mActive;
public:
	MenuScreen(ScreenManager* manager, GLFWwindow* window);
	~MenuScreen();

	void Draw();
	void Update();
};

