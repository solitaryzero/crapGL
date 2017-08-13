#include "stdafx.h"
#include "PerspectiveCamera.h"
#define PI 3.14159265358979323846

PerspectiveCamera::PerspectiveCamera()
{
	front = Vector3::zeros;
	right = Vector3::zeros;
	up = Vector3::zeros;
	eye = Vector3::zeros;
	fov = 0;
	fovScale = 0;
}

PerspectiveCamera::PerspectiveCamera(Vector3 _eye, Vector3 _front, Vector3 _right, double _fov)
{
	front = _front;
	right = _right;
	eye = _eye;
	fov = _fov;
	up = right.cross(front);
	fovScale = double(tan(fov*0.5*PI / 180) * 2);
}

ray PerspectiveCamera::GenerateRay(double x, double y)
{
	Vector3 r = right*((x - 0.5)*fovScale);
	Vector3 u = up*((y - 0.5)*fovScale);
	return ray(eye, (front + r + u).normalize());
}