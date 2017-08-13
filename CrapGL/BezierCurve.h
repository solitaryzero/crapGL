#pragma once
#include "Vector3.h"

class BezierCurve
{
public:
	Vector3 p0, p1, p2;
	
	BezierCurve();
	BezierCurve(Vector3 p0_, Vector3 p1_, Vector3 p2_);
	~BezierCurve();
	Vector3 getPoint(double t);
};

