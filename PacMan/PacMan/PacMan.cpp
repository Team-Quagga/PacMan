#include <iostream>
#include "Engine\Engine.h"
#include "Engine\Button.h"

int main()
{
	Input* i = Input::GetInstance();
	Button b(1,1,1,1);
	b.SetClickCallback([](GLFWwindow* w, int button, int pressed, double x, double y)->void
	{
		std::cout<<"Hej GitHub! "<<std::endl;
	});

	i->Register(b);

	std::cout<<"Hej GitHub! "<<std::endl;

	return 0;
}