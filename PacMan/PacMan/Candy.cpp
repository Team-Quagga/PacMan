#include "Candy.h"


Candy::Candy(int seed)
{
	superCandy = false;
	srand(seed);
	int candyValue = rand() % 100;
	printf(""+candyValue);
	if (candyValue < 3)
		superCandy = true;
}


Candy::~Candy(void)
{
}


void Candy::Draw()
{
}

void Candy::Init(vec3 position)
{

}