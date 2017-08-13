#include "stdafx.h"
#include "plane.h"

plane::plane()
{
	normal = Vector3::zeros;
	d = 0;
	position = Vector3::zeros;
}

plane::plane(Vector3 n, double d_, material *m)
{
	normal = n;
	d = d_;
	mat = m;
	position = n*d;
}

IntersectInfo plane::intersection(ray _ray)
{
	double a = _ray.direction.dot(normal);
	double b = (_ray.point - position).dot(normal);
	if (a != 0)
	{
		double dist = -b / a;
		if (dist > 1e-3)
		{
			if (a > 0)
				return IntersectInfo(this, dist, _ray.GetPoint(dist), normal.negative(),-1);
			else
				return IntersectInfo(this, dist, _ray.GetPoint(dist), normal, 1);
		}
	}

	return IntersectInfo::noHit;
}