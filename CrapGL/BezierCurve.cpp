#include "stdafx.h"
#include "BezierCurve.h"


BezierCurve::BezierCurve()
{
	p0 = Vector3::zeros;
	p1 = Vector3::zeros;
	p2 = Vector3::zeros;
}

BezierCurve::BezierCurve(Vector3 p0_, Vector3 p1_, Vector3 p2_)
{
	p0 = p0_;
	p1 = p1_;
	p2 = p2_;
}

BezierCurve::~BezierCurve()
{
}

Vector3 BezierCurve::getPoint(double t)
{
	return Vector3(p0*(1 - t)*(1 - t) + p1 * 2 * t*(1 - t) + p2*t*t);
}
