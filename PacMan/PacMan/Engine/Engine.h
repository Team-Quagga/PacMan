#pragma once

#include "Input.h"
#include "Graphics.h"
#include "ScreenManager.h"

#include "../Model.h"

class Engine
{
public:
	static Model* LoadModel(const char* path);
	static char* ReadFile(const char* path);

	static Graphics* GetGraphics() { return Graphics::GetInstance(); }
};