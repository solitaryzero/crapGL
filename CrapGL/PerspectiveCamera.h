#pragma once
#include "ray.h"

class PerspectiveCamera {
public:
	Vector3 front;
	Vector3 right;
	Vector3 up;
	Vector3 eye;
	double fov;
	double fovScale;

	PerspectiveCamera();
	PerspectiveCamera(Vector3 _eye, Vector3 _front, Vector3 _right, double _fov);
	ray GenerateRay(double x, double y);
};