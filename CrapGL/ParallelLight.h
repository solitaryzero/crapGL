#pragma once
#include "LightSource.h"

class ParallelLight :
	public LightSource
{
public:
	Vector3 direction;

	ParallelLight();
	ParallelLight(Vector3 d, myColor lu);
	~ParallelLight();
	virtual bool isAccessible(scene *sc, Vector3 p);
	virtual LightSample sample(scene *sc, Vector3 p);
	virtual ray generateRay();
};

