#pragma once
#include "Vector3.h"

class Geometry;

class IntersectInfo {
public:
	Geometry *geometry;
	double distance;
	Vector3 position;
	Vector3 normal;
	int isOutside;

	IntersectInfo();
	IntersectInfo(Geometry *g, double d, Vector3 p, Vector3 n);
	IntersectInfo(Geometry *g, double d, Vector3 p, Vector3 n, int out);
	static const IntersectInfo noHit;
};