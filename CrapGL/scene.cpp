#include "stdafx.h"
#include "scene.h"


scene::scene()
{
	objects.clear();
}

scene::~scene()
{
}

void scene::addObject(Geometry *g)
{
	objects.push_back(g);
}

IntersectInfo scene::intersection(ray _ray)
{
	IntersectInfo tmp;
	IntersectInfo ans = IntersectInfo::noHit;
	double minDist = INFINITY;
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		tmp = objects[i]->intersection(_ray);
		if ((tmp.geometry != nullptr) && (tmp.distance < minDist))
		{
			ans = tmp;
			minDist = tmp.distance;
		}
	}

	return ans;
}