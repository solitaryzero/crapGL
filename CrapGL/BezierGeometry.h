#pragma once
#include "Geometry.h"
#include "BezierCurve.h"
#include <Eigen/dense>
#include <iostream>
#include <vector>

class BezierGeometry :
	public Geometry
{
public:
	BezierCurve curve;
	ray axis;

	BezierGeometry();
	BezierGeometry(BezierCurve curve_, ray axis_, material *m);
	~BezierGeometry();
	Vector3 getPointbyuv(double u, double v);
	Vector3 getPointbyv(Vector3 p, double v);
	Vector3 Newton(Vector3 paras, ray _ray);
	void outputAsObj();
	virtual IntersectInfo intersection(ray _ray);
};

