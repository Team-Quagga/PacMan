#include "Candy.h"

Candy::Candy(bool s, vec3 position)
{
	if(s) super = true;
	if(super) mModel = *Engine::LoadModel("super.obj", 1);
	else mModel = *Engine::LoadModel("candy.obj", 1);
	
	Init(position);
}


Candy::~Candy(void)
{
}


void Candy::Draw()
{
	mModel.Draw();
}

void Candy::Init(vec3 position)
{
	mPosition = position;
	//Initiate buffers?
}