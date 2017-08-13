#include "stdafx.h"
#include "PhongMaterial.h"
#include <algorithm>

PhongMaterial::PhongMaterial()
{
	diffuse = myColor(0,0,0);
	specular = myColor(0, 0, 0);
	shininess = 0;
	alt_reflectiveness = 0;
	reflectiveness = 0;
	refractiveness = 0;
	transparency = 0;
	absorbance = myColor::myBlack;
}

PhongMaterial::PhongMaterial(myColor d, myColor sp, int sh, double ref)
{
	diffuse = d;
	specular = sp;
	shininess = sh;
	alt_reflectiveness = 1-ref;
	reflectiveness = ref;
	refractiveness = 0;
	transparency = 0;
	absorbance = myColor::myBlack;
}

PhongMaterial::PhongMaterial(myColor d, myColor sp, int sh, double a_ref, double ref, double refra, double trans, myColor absorb)
{
	diffuse = d;
	specular = sp;
	shininess = sh;
	alt_reflectiveness = a_ref;
	reflectiveness = ref;
	refractiveness = refra;
	transparency = trans;
	absorbance = absorb;
}

myColor PhongMaterial::sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular)
{
	double NdotL = n.dot(LightDir);
	double HdotN = (LightDir - v.direction).normalize().dot(n);

	myColor DiffuseTerm = diffuse*myColor::myMax(NdotL,0);
	myColor SpecularTerm = specular*pow(HdotN, shininess);
	if (isSpecular == false) 
		SpecularTerm = myColor::myBlack;
	return c.modulate(DiffuseTerm + SpecularTerm);
}