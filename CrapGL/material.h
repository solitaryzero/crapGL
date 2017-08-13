#pragma once
#include "Vector3.h"
#include "myColor.h"
#include "ray.h"

class material
{
public:
	double alt_reflectiveness;
	double reflectiveness;
	double refractiveness;
	double transparency;
	myColor absorbance;
	myColor diffuse;

	material();
	virtual myColor sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular = true) = 0;
};

