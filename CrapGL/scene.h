#pragma once
#include "Geometry.h"
#include "IntersectInfo.h"
#include <vector>

class scene
{
public:
	std::vector<Geometry*> objects;
	scene();
	~scene();
	void addObject(Geometry *g);
	IntersectInfo intersection(ray _ray);
};

