#pragma once
#include "Geometry.h"
class sphere :
	public Geometry
{
public:
	Vector3 center;
	double radius;

	sphere();
	sphere(Vector3 c, double r);
	sphere(Vector3 c, double r, material *m);
	double sqrRadius();
	virtual IntersectInfo intersection(ray _ray);
};

