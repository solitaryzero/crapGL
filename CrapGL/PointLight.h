#pragma once
#include "LightSource.h"

class PointLight :
	public LightSource
{
public:
	Vector3 origin;

	PointLight();
	PointLight(Vector3 o, myColor lu);
	~PointLight();
	virtual bool isAccessible(scene *sc, Vector3 p);
	virtual LightSample sample(scene *sc, Vector3 p);
	virtual ray generateRay();
};

