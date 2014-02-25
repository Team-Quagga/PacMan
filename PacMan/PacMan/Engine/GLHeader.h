#pragma once
#ifndef GLHeader_H
#define GLHeader_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

void FocusWindow(GLFWwindow* window);

GLFWwindow* CreateWindow(const char* tile, int width, int height);

GLFWwindow*  Init(const char* tile, int width, int height);



#endif // !GLHeader_H