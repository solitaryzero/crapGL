#pragma once
#include <opencv2\flann.hpp>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <vector>
#include "Vector3.h"
#include "myColor.h"
#include "scene.h"
#include "LightSource.h"
#include "myKDTree.h"
#include "photons.h"

using namespace cv;

class PhotonMapping
{
public:
	std::vector<CameraRayPoint> crosses;
	myKDTree *root;

	PhotonMapping(std::vector<CameraRayPoint> cross);
	~PhotonMapping();
	Vector3 calRefract(Vector3 l, Vector3 n, double refractiveness);
	void map(scene *sc, LightSource *light, int times, Mat &m, double radius = 0.02);
};

