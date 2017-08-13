#pragma once
#include "Vector3.h"
#include "IntersectInfo.h"
#include "ray.h"

class CameraRayPoint
{
public:
	int x, y;
	ray cameraRay;
	double modifier;
	IntersectInfo info;
	CameraRayPoint();
	CameraRayPoint(int x_, int y_, double mo, ray c_, IntersectInfo info_);
	~CameraRayPoint();
};

