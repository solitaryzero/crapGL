#pragma once
#include "Vector3.h"
#include "IntersectInfo.h"
#include "ray.h"
#include "material.h"

class Geometry {
public:
	material *mat;

	Geometry();
	virtual IntersectInfo intersection(ray _ray) = 0;
};