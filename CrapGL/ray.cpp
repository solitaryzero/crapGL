#include "stdafx.h"
#include "ray.h"

ray::ray()
{
	point = Vector3();
	direction = Vector3();
}

ray::ray(const Vector3 &p, const Vector3 &d)
{
	point = p;
	direction = d;
}

Vector3 ray::GetPoint(double t)
{
	return point + direction*t;
}