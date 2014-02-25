#pragma once
#include "Input.h"
class ScreenManager;
class IScreen:public KeyObserver
{
protected:
	ScreenManager* mManager;
	GLFWwindow* mWindow;
public:
	IScreen(ScreenManager* manager, GLFWwindow* window)
	{
		mManager = manager;
		mWindow = window;
	}

	virtual ~IScreen()
	{
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;
	void FocusMe();
	void RemoveMe();
	GLFWwindow* GetWindow();
};

#include "ScreenManager.h"

inline void IScreen::FocusMe()
{
	mManager->SetFocus(this);
}

inline void IScreen::RemoveMe()
{
	mManager->RemoveScreen(this);
}

inline GLFWwindow* IScreen::GetWindow()
{
	return mWindow;
}