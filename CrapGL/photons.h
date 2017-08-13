#pragma once
#include "myColor.h"

class photons
{
public:
	int x, y;
	myColor color;
	photons(int x_, int y_, myColor c_);
	~photons();
};

