#pragma once
#include "myColor.h"
#include "ray.h"
#include "material.h"

class PhongMaterial :public material
{
public: 
	myColor specular;
	int shininess;

	PhongMaterial();
	PhongMaterial(myColor d, myColor sp, int sh, double ref);
	PhongMaterial(myColor d, myColor sp, int sh, double a_ref, double ref, double refra, double trans, myColor absorb);
	virtual myColor sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular = true);
};

