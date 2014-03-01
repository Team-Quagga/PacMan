#include "Graphics.h"

Graphics* Graphics::g;

Graphics* Graphics::GetInstance() {
	if (g == NULL) g = new Graphics();
	return g;
};