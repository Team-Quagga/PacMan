#pragma once
#include "igameobject.h"
class Candy :
	public IGameObject
{
public:
	Candy(bool, vec3);
	~Candy(void);
	void Draw();
	void Init(vec3);
private:
	bool super;
};

