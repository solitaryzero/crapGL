#pragma once
#include "Vector3.h"
#include "scene.h"
#include "ray.h"
#include "LightSample.h"

class scene;

class LightSource
{
public:
	myColor lumin;

	LightSource();
	~LightSource();
	virtual bool isAccessible(scene *sc, Vector3 p) = 0;
	virtual LightSample sample(scene *sc, Vector3 p) = 0;
	virtual ray generateRay() = 0;
};

