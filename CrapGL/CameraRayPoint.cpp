#include "stdafx.h"
#include "CameraRayPoint.h"

CameraRayPoint::CameraRayPoint()
{
	x = -1;
	y = -1;
	cameraRay = ray();
	info = IntersectInfo::noHit;
}

CameraRayPoint::CameraRayPoint(int x_, int y_, double mo, ray c_, IntersectInfo info_)
{
	x = x_;
	y = y_;
	modifier = mo;
	cameraRay = c_;
	info = info_;
}

CameraRayPoint::~CameraRayPoint()
{
}
