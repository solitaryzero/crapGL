#include "stdafx.h"
#include "RayTracer.h"

#define MATH_E 2.718281828459

RayTracer::RayTracer()
{
}

Vector3 RayTracer::calRefract(Vector3 l, Vector3 n, double refractiveness)
{
	double tmp = double(1) / refractiveness;
	double cosL = l.dot(n);
	double cosT = 1 - tmp*tmp*(1 - cosL*cosL);

	if (cosT <= 0) return Vector3::zeros;

	return (l*tmp - n*(cosL*tmp + std::sqrt(cosT))).normalize();
}

myColor RayTracer::RayTracing(scene *_scene, std::vector<LightSource*> lights, ray _ray, int maxReflection, std::vector<CameraRayPoint> &rayPoints, int x, int y, double modifier, Geometry *dst)
{
	if (maxReflection == 0) return myColor::myBlack;
	IntersectInfo info = _scene->intersection(_ray);

	if (info.geometry != nullptr)
	{
		double a_ref = info.geometry->mat->alt_reflectiveness;
		double ref = info.geometry->mat->reflectiveness;
		double refra = info.geometry->mat->refractiveness;
		double trans = info.geometry->mat->transparency;
		myColor absorbance = info.geometry->mat->absorbance;
		myColor color;
		myColor ans = myColor::myBlack;
		Vector3 r, r2;
		LightSample smp;

		if (info.isOutside == -1)
			modifier = modifier*exp(-info.distance*absorbance.r*0.01f);

		rayPoints.push_back(CameraRayPoint(x, y, modifier, _ray, info));

		for (unsigned int i = 0; i < lights.size(); i++)
		{
			smp = lights[i]->sample(_scene, info.position);
			color = info.geometry->mat->sample(_ray, info.position, info.normal, smp.c , smp.l);
			ans = ans+color*a_ref*info.normal.dot(smp.l);
			r = _ray.direction - (info.normal * 2 * (info.normal.dot(_ray.direction)));
			if ((info.isOutside == 1) && (info.geometry->mat->transparency > 1e-3))
			{
				r2 = calRefract(_ray.direction.normalize(), info.normal, refra);
			}
			else
			{
				r2 = calRefract(_ray.direction.normalize(), info.normal, double(1) / refra);
			}

			ray reflectRay(info.position, r.normalize());
			ray refractRay(info.position, r2);
			if (info.geometry->mat->reflectiveness > 1e-3)
				ans = ans + RayTracing(_scene, lights, reflectRay, maxReflection - 1, rayPoints, x, y, modifier*ref,dst);
			if (info.geometry->mat->transparency > 1e-3)
				ans = ans + RayTracing(_scene, lights, refractRay, maxReflection - 1, rayPoints, x, y, modifier*trans,dst);
		}

		return ans*modifier;
	}

	return myColor::myBlack;
}
