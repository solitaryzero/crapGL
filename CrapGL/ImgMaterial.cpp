#include "stdafx.h"
#include "ImgMaterial.h"
#define M_PI 3.1415926535894932

using namespace cv;

ImgMaterial::ImgMaterial(std::string s)
{
	alt_reflectiveness = 1;
	reflectiveness = 0;
	refractiveness = 0;
	transparency = 0;
	absorbance = myColor::myWhite;
	diffuse = myColor::myWhite;
	m = imread(s);
}


ImgMaterial::~ImgMaterial()
{
}

myColor ImgMaterial::sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular)
{
	double tu = p.z / 0.401;
	double tv = atan2(p.y,p.x)/M_PI/2;
	if (tv < 0) tv = tv+1;
	Vec3b tmp = m.at<Vec3b>((int)(tu*m.rows), int(tv*m.cols));
	myColor matc = myColor((double)tmp[2] / (double)255, (double)tmp[1] / (double)255 , (double)tmp[0] / (double)255);
	matc = matc*myColor::myMax(n.dot(LightDir), 0);
	return c.modulate(matc);
}