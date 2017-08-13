#include "stdafx.h"
#include "sphere.h"


sphere::sphere()
{
	center = Vector3::zeros;
	radius = 0;
}

sphere::sphere(Vector3 c, double r)
{
	center = c;
	radius = r;
}

sphere::sphere(Vector3 c, double r, material *m)
{
	center = c;
	radius = r;
	mat = m;
}

double sphere::sqrRadius()
{
	return radius*radius;
}

IntersectInfo sphere::intersection(ray _ray)
{
	Vector3 v = _ray.point - center;
	double dDOTv = _ray.direction.dot(v);
	if ((fabs(v.sqrLength() - sqrRadius()) < 1e-3) && (dDOTv > 0)) return IntersectInfo::noHit;
	if (dDOTv <= 0)
	{
		double a0 = v.sqrLength() - sqrRadius();
		double disc = dDOTv*dDOTv - a0;
		if (disc >= 0)
		{
			if (fabs(v.sqrLength() - sqrRadius()) < 1e-3)
			{
				double t = -dDOTv + double(sqrt(disc));
				Vector3 p = _ray.GetPoint(t);
				return IntersectInfo(this, t, p, (center - p).normalize(), -1);
			}

			double t = -dDOTv - double(sqrt(disc));
			Vector3 p = _ray.GetPoint(t);
			return IntersectInfo(this, t, p, (p - center).normalize(),1);
		}
	}

	return IntersectInfo::noHit;
}
