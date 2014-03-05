#include "Candy.h"	

Candy::Candy(int seed)
{
	superCandy = false;
	srand(seed);
	int candyValue = rand() % 100;
	printf(""+candyValue);
	if (candyValue < 3)
		superCandy = true;
	if(superCandy) mModel = *Engine::LoadModel("super.obj", 1);
	else mModel = *Engine::LoadModel("candy.obj", 1);
}


Candy::~Candy(void)
{
}


void Candy::Draw()
{
	mModel.Draw();
}

//TODO
void Candy::Init(vec3 position)
{
	mPosition = position;
	//Initiate buffers?
}