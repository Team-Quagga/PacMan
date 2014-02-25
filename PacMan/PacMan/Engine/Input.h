#pragma once
#include "GLHeader.h"
#include <vector>
#include <functional>
struct GLFWwindow;

typedef std::function<void(GLFWwindow* w, int key, int scancode, int action, int mods)> KeyPressFun;
typedef std::function<void(GLFWwindow* w, int button, int pressed, double x, double y)> MouseFun;
struct KeyObserver
{
	KeyPressFun mKeyPress;
};
struct MouseObserver
{
	MouseFun mMouseFun;
};

class Input
{
	static Input* i;
	std::vector<KeyObserver*> mKeyPress;
	std::vector<MouseObserver*> mMousePress;
public:
	~Input(){}
	static Input* GetInstance();
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input* instance = GetInstance();
		for (int i = 0; i < instance->mKeyPress.size(); i++)
			instance->mKeyPress[i]->mKeyPress(window, key, scancode, action, mods);
	}
	static void MouseCallback(GLFWwindow* window, int button, int pressed, int modifiers)
	{
		double x, y;
		int width, height;
		glfwGetCursorPos(window, &x, &y);
		glfwGetWindowSize(window, &width, &height);
		for (int a = 0; a < i->mMousePress.size(); a++)
			i->mMousePress[a]->mMouseFun(window, button, pressed, -1 + x / (width / 2), -1 + y / (height / 2));
	}
	void Register(KeyObserver& observer);
	void Register(MouseObserver& observer);
private:
	Input(){}
	Input(Input const&); // prevent copies
	void operator=(Input const&); // prevent assignments

};
Input* Input::i = nullptr;

inline Input* Input::GetInstance()
{
		if (i == nullptr) 
		{
			i = new Input();
		}
		return i;
}

inline void Input::Register(KeyObserver& observer)
{
	mKeyPress.push_back(&observer);
}

inline void Input::Register(MouseObserver& observer)
{
	mMousePress.push_back(&observer);
}