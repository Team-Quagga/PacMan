#pragma once

#include "Input.h"
#include "Graphics.h"
#include "ScreenManager.h"

#include "../Model.h"

class Engine
{
public:
	static Model* LoadModel(const char* path, float scale);
	static char* ReadFile(const char* path);

	static Graphics* GetGraphics() { return Graphics::GetInstance(); }
};