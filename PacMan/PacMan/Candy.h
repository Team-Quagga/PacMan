#pragma once
#include "igameobject.h"
class Candy :
	public IGameObject
{
public:
	Candy(int seed);
	~Candy(void);
	void Draw();
	void Init(vec3 position);
private:
	bool superCandy;
};

