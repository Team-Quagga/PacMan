#pragma once

#include <vector>
#include "Viewport.h"

class Graphics {
	static Graphics* g;
public:
	inline static Graphics* GetInstance();

private:
	Graphics() {}
	Graphics(Graphics const&); // prevent copies
	void operator=(Graphics const&); // prevent assignments
};
