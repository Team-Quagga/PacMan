#include "Input.h"

Input* Input::i = nullptr;

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (int a = 0; a < i->mKeyPress.size(); a++)
		if(i->mKeyPress[a]->mKeyPress != nullptr)
			i->mKeyPress[a]->mKeyPress(window, key, scancode, action, mods);
}

void Input::MouseCallback(GLFWwindow* window, int button, int pressed, int modifiers)
{
	double x, y;
	int width, height;
	glfwGetCursorPos(window, &x, &y);
	glfwGetWindowSize(window, &width, &height);
	for (int a = 0; a < i->mMousePress.size(); a++)
		if(i->mMousePress[a]->mMouseFun != nullptr)
			i->mMousePress[a]->mMouseFun(window, button, pressed, -1 + x / (width / 2), 1 - y / (height / 2));
}

