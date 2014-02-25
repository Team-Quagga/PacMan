#pragma once
#include "GLHeader.h"
#include "Rect.h"
#include "Input.h"
#include "Sprite.h"
#include <functional>

class Button :public Rect, public MouseObserver
{
	/*Rect
		float x, y, width, height;
		bool InterSect(Rect& r)(float x, float y);
		*/
	Sprite* s;
public:
	float r, g, b;
	Button(float x_, float y_, float width_, float height_, Sprite* s_ = nullptr)
	{
		mMouseFun = nullptr;
		x = x_;
		y = y_;
		width = width_;
		height = height_;
		if (s_ != nullptr)
		{
			s = s_;
			s->Set((Rect)*this);
			//s->Set(x_, y_, width_, height_);
		}
	}
	void Draw()
	{
		if (s != nullptr)
		{
			s->Draw();
		}
		else
		{
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(r, g, b);
			glVertex3f(x, y + height, 0);// up-left
			glVertex3f(x, y, 0);// down-left
			glVertex3f(x + width, y + height, 0);// up-right
			glVertex3f(x + width, y, 0);// down-right
			glEnd();
		}
	}
	void SetClickCallback(MouseFun callback)
	{
		mMouseFun = callback;
	}
	void SetSprite(Sprite* s)
	{
		this->s = s;
		this->s->Set(*(this));
	}
	//Behövs ej om den är registrerad hos Input
	void Clicked(GLFWwindow* w, int button, int pressed, double x, double y)
	{
		if (mMouseFun != nullptr)
			mMouseFun(w, button, pressed, x, y);
	}
};