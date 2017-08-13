#include "stdafx.h"
#include "LightSample.h"


LightSample::LightSample()
{
	l = Vector3::zeros;
	c = myColor::myBlack;
}

LightSample::LightSample(Vector3 l_, myColor c_)
{
	l = l_;
	c = c_;
}

LightSample::~LightSample()
{
}

const LightSample LightSample::zeros = LightSample();
