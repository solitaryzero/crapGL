#pragma once
#include "scene.h"
#include "ray.h"
#include "myColor.h"
#include "LightSource.h"
#include "CameraRayPoint.h"
#include <vector>

class RayTracer
{
public:
	RayTracer();
	
	Vector3 calRefract(Vector3 l, Vector3 n, double refractiveness);
	myColor RayTracing(scene *_scene, std::vector<LightSource*> lights, ray _ray, int maxReflection, std::vector<CameraRayPoint> &rayPoints, int x, int y, double modifier, Geometry *dst);
};

