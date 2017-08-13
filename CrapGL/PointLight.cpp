#include "stdafx.h"
#include "PointLight.h"
#define M_PI 3.1415926535

PointLight::PointLight()
{
}

PointLight::PointLight(Vector3 o, myColor lu)
{
	origin = o;
	lumin = lu;
}

PointLight::~PointLight()
{
}

bool PointLight::isAccessible(scene *sc, Vector3 p)
{
	ray r = ray(origin, (p - origin).normalize());
	IntersectInfo info = sc->intersection(r);
	if ((info.geometry == nullptr) || (info.distance +2e-3 > (p - origin).length())) return true;

	return false;
}

LightSample PointLight::sample(scene *sc, Vector3 p)
{
	if (isAccessible(sc, p))
	{
		return LightSample((origin - p).normalize(), lumin);
	}
	return LightSample();
}

ray PointLight::generateRay()
{
	int bigrand = (rand() % 10000)*10000 + (rand() % 10000);
	int theta = bigrand % 18000000;
	double theta_rad = double(theta)/50000*M_PI / 180;
	bigrand = (rand() % 10000) * 10000 + (rand() % 10000);
	int phi = rand() % 18000001;
	double phi_rad = double(phi)/100000*M_PI / 180;
	Vector3 vx = Vector3(1, 0, 0);
	Vector3 vy = Vector3(0, 1, 0);
	Vector3 vz = Vector3(0, 0, 1);
	Vector3 ans = vz*cos(phi_rad) + vx*sin(phi_rad)*cos(theta_rad) + vy*sin(phi_rad)*sin(theta_rad);
	return ray(origin, ans.normalize());
}