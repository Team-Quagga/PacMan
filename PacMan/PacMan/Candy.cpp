#include "Candy.h"
#include "Engine\Engine.h"

Candy::Candy(bool s, vec3 position)
{
	if(s) super = true;
	Engine.LoadModel("candy.obj");
	Init(position);
}


Candy::~Candy(void)
{
}


void Candy::Draw()
{
	//Draw object
}

void Candy::Init(vec3 position)
{
	//Initiate buffers?
}