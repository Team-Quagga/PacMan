#pragma once
#include "igameobject.h"
#include "AudioSource.h"
class Candy :
	public IGameObject
{
public:
	Candy(int seed);
	~Candy(void);
	void Draw();
	void Init(vec3 position);
	void SetSound(AudioSource* a);
	void PlaySound();
private:
	bool superCandy;
};

