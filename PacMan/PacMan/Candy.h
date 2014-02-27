#pragma once
#include "igameobject.h"
class Candy :
	public IGameObject
{
public:
	Candy(void);
	~Candy(void);
	void Draw();
	void Init(vec3 position, int difficulty);
};

