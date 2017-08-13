#pragma once
#include "Vector3.h"
#include "myColor.h"

class LightSample
{
public:
	Vector3 l;
	myColor c;
	LightSample();
	LightSample(Vector3 l_, myColor c_);
	~LightSample();
	static const LightSample zeros;
};

