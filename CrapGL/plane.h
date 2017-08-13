#pragma once
#include "Geometry.h"
#include "material.h"

class plane :public Geometry
{
public:
	Vector3 normal;
	Vector3 position;
	double d;

	plane();
	plane(Vector3 n, double d_, material *m);
	virtual IntersectInfo intersection(ray _ray);
};

