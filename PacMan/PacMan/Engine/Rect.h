#pragma once
#include "Helper.h"
struct Rect
{
protected:
	float x, y, width, height;
public:
	Rect() {}
	Rect(int _width, int _height) : width(_width), height(_height) {};
	inline void Set(float x, float y, float w, float h);
	inline void Set(Rect& r);
	inline bool Intersect(Rect& r);
	inline bool Intersect(float x_, float y_);
};

inline void Rect::Set(float x_, float y_, float w_, float h_)
{
	x = x_;
	y = y_;
	width = w_;
	height = h_;
}

inline void Rect::Set(Rect& r_)
{
	Set(r_.x, r_.y, r_.width, r_.height);
}

inline bool Rect::Intersect(Rect& r)
{
	bool xOverlap = valueInRange(x, r.x, r.x + r.width) ||
		valueInRange(r.x, x, x + width);

	bool yOverlap = valueInRange(y, r.y, r.y + r.height) ||
		valueInRange(r.y, y, y + r.height);

	return xOverlap && yOverlap;
};

inline bool Rect::Intersect(float x_, float y_)
{
	return (x <= x_ && y <= y_ && x + width >= x_ && y + height >= y_);
};

