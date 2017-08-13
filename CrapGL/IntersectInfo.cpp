#include "stdafx.h"
#include "IntersectInfo.h"
#include "Geometry.h"

IntersectInfo::IntersectInfo()
{
	geometry = nullptr;
	distance = 0;
	position = Vector3::zeros;
	normal = Vector3::zeros;
	isOutside = 0;
}

IntersectInfo::IntersectInfo(Geometry *g, double d, Vector3 p, Vector3 n)
{
	geometry = g;
	distance = d;
	position = p;
	normal = n;
	isOutside = 0;
}

IntersectInfo::IntersectInfo(Geometry *g, double d, Vector3 p, Vector3 n, int out)
{
	geometry = g;
	distance = d;
	position = p;
	normal = n;
	isOutside = out;
}

const IntersectInfo IntersectInfo::noHit = IntersectInfo();