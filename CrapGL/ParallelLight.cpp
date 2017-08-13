#include "stdafx.h"
#include "ParallelLight.h"


ParallelLight::ParallelLight()
{
	direction = Vector3::zeros;
	lumin = myColor::myBlack;
}

ParallelLight::ParallelLight(Vector3 d, myColor lu)
{
	direction = d;
	lumin = lu;
}

ParallelLight::~ParallelLight()
{
}

bool ParallelLight::isAccessible(scene *sc, Vector3 p)
{
	IntersectInfo info = sc->intersection(ray(p,direction.negative()));
	return (info.geometry == nullptr);
}

LightSample ParallelLight::sample(scene *sc, Vector3 p)
{
	if (isAccessible(sc, p)) return (LightSample(direction.negative(), lumin));
	return LightSample();
}

ray ParallelLight::generateRay()
{
	return ray();
}