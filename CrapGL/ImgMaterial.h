#pragma once
#include "material.h"
#include <string>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>

class ImgMaterial :
	public material
{
public:
	cv::Mat m;
	ImgMaterial(std::string s);
	~ImgMaterial();
	virtual myColor sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular = true);
};

