#include "Candy.h"	

Candy::Candy(int seed)
{
	superCandy = false;
	srand(seed);
	int candyValue = rand() % 100;
	if (candyValue < 3)
		superCandy = true;
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