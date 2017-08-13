#pragma once
#include "Vector3.h"
#include "CameraRayPoint.h"
#include "IntersectInfo.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

class myKDTree
{
public:
	CameraRayPoint point;
	Vector3 minBound;
	Vector3 maxBound;
	int axis;
	double value;

	myKDTree *left;
	myKDTree *right;

	myKDTree();
	~myKDTree();
	static bool compx(CameraRayPoint &a, CameraRayPoint &b);
	static bool compy(CameraRayPoint &a, CameraRayPoint &b);
	static bool compz(CameraRayPoint &a, CameraRayPoint &b);
	static void bulidTree(std::vector<CameraRayPoint> data, myKDTree *root);
	static void getNeighbours(Vector3 pos, std::vector<CameraRayPoint> &ans, double radius, myKDTree *root);
};

