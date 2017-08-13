// CrapGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define NOMINMAX
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <random>
#include <string>
#include "Geometry.h"
#include "sphere.h"
#include "plane.h"
#include "IntersectInfo.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "Vector3.h"
#include "scene.h"
#include "ChessBoard.h"
#include "material.h"
#include "PhongMaterial.h"
#include "RayTracer.h"
#include "LightSource.h"
#include "ParallelLight.h"
#include "PointLight.h"
#include "PhotonMapping.h"
#include "BezierGeometry.h"
#include "ImgMaterial.h"

using namespace cv;

void on_mouse(int event, int x, int y, int flags, void* img)
{
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		IplImage *timg = cvCloneImage((IplImage *)img);
		CvPoint pt = cvPoint(x, y);
		char temp[16];
		sprintf(temp, "(%d,%d)", x, y);
		cvPutText(timg, temp, pt, &font, CV_RGB(250, 0, 0));
		cvCircle(timg, pt, 2, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		cvShowImage("src", timg);
		cvReleaseImage(&timg);
	}
}

int main()
{
	int height, width;
	double x, y;
	ray ray_;
	IntersectInfo info;

	height = 1000;
	width = 1000;
	Mat m = Mat(height,width,CV_8UC4);
	Mat trace = Mat(height, width, CV_64FC4);
	Mat photon = Mat(height, width, CV_64FC4);
	srand((unsigned)time(0));

	RayTracer rt;
	PerspectiveCamera camera = PerspectiveCamera(Vector3(0, -0.6, 0.5), Vector3(0, 1, 0).normalize(), Vector3(-1, 0, 0).normalize(), 90);
	PhongMaterial *mat1 = new PhongMaterial(myColor::myWhite, myColor::myWhite, 20, 1, 0, 2, 0, myColor::myWhite);
	PhongMaterial *mat2 = new PhongMaterial(myColor::myBlue, myColor::myWhite, 20, 0.1, 0.5, 2, 0.4, myColor::myWhite);
	ChessBoard *mat3 = new ChessBoard(0.1);
	PhongMaterial *mat4 = new PhongMaterial(myColor::myWhite, myColor::myWhite, 20, 0, 0, 2, 1, myColor::myWhite);
	PhongMaterial *mat5 = new PhongMaterial(myColor::myWhite, myColor::myBlack, 20, 1, 0, 2, 0, myColor::myWhite);
	PhongMaterial *mat6 = new PhongMaterial(myColor(double(254) / double(255), double(67) / double(255), double(101) / double(255)), myColor::myBlack, 20, 1, 0, 2, 0, myColor::myWhite);
	PhongMaterial *mat7 = new PhongMaterial(myColor(double(131) / double(255), double(175)/double(255), double(155)/double(255)), myColor::myBlack, 20, 1, 0, 2, 0, myColor::myWhite);
	ImgMaterial *mat8 = new ImgMaterial("mat.bmp");
	PhongMaterial *mat9 = new PhongMaterial(myColor::myWhite, myColor::myBlack, 20, 0.5, 0.5, 2, 0, myColor::myWhite);
	sphere *sph1 = new sphere(Vector3(-0.8, 0.8, 0.2), 0.1, mat1);
	sphere *sph2 = new sphere(Vector3(0.6, 0.6, 0.5), 0.1, mat2);
	sphere *sph3 = new sphere(Vector3(-0.5, 0.2, 0.12), 0.1, mat4);
	plane *pl1 = new plane(Vector3(0, 0, 1), 0, mat5);
	plane *pl2 = new plane(Vector3(0, -1, 0), -1, mat6);
	plane *pl3 = new plane(Vector3(1, 0, 0), -1, mat7);
	plane *pl4 = new plane(Vector3(-1, 0, 0), -1, mat7);
	plane *pl5 = new plane(Vector3(0, 1, 0), -1, mat5);
	plane *pl6 = new plane(Vector3(0, 0, -1), -1.5, mat9);
	BezierCurve curve(Vector3(0, 0, 0), Vector3(0.2, 0, 0.2), Vector3(0, 0, 0.4));
	ray axis = ray(Vector3(0, 0, 0), Vector3(0, 0, 1));
	BezierGeometry *bz = new BezierGeometry(curve, axis, mat8);

	//bz->outputAsObj();
	//return 0;

	scene *sc = new scene;
	sc->addObject(sph1);
	sc->addObject(sph2);
	sc->addObject(sph3);
	sc->addObject(bz);
	sc->addObject(pl1);
	sc->addObject(pl2);
	sc->addObject(pl3);
	sc->addObject(pl4);
	sc->addObject(pl5);
	sc->addObject(pl6);
	vector<LightSource*> lights;
	lights.clear();
	ParallelLight *lt1 = new ParallelLight(Vector3(0, 0, -1).normalize(), myColor::myWhite);
	myColor ptColor = myColor::myWhite;
	PointLight *lt2 = new PointLight(Vector3(0, 0.2, 0.8), ptColor);
	PointLight *lt3 = new PointLight(Vector3(0, -0.8, 0.5), ptColor);
	//lights.push_back(lt1);
	lights.push_back(lt2);
	//lights.push_back(lt3);

	printf("scene set\n");

	std::vector<CameraRayPoint> rayPoints;
	rayPoints.clear();

	for (int i = 0; i < height; i++)
	{
		y = (double)i / (double)height;
		for (int j = 0; j < width; j++)
		{
			//printf("%d/%d lines %d/%d rows\n",i,height,j,width);
			trace.at<Vec4d>(i, j) = Vec4d(0, 0, 0, 255);
			photon.at<Vec4d>(i, j) = Vec4d(0, 0, 0, 255);
			x = (double)j / (double)width;
			ray_ = camera.GenerateRay(x, y);

			myColor color = rt.RayTracing(sc, lights, ray_, 5, rayPoints, i, j, 1,bz);
			trace.at<Vec4d>(i, j) += Vec4d(color.b, color.g, color.r, 255);
		}
	}
	
	PhotonMapping pm(rayPoints);
	printf("tree set %f %f %f\n",pm.root->point.cameraRay.direction.x, pm.root->point.cameraRay.direction.y, pm.root->point.cameraRay.direction.z);
	
	double radius = 0.02;
	for (int i = 1; i < 100; i++)
	{
		photon = photon*(i - 1);
		pm.map(sc, lt2, 150000, photon, radius);
		//pm.map(sc, lt3, 10000000, photon, radius);
		//radius = radius * 0.95;
		photon = photon / double(i);

		std::stringstream ss;
		std::string str;
		ss << i+20;
		ss >> str;

		for (int k = 0; k < height; k++)
			for (int j = 0; j < width; j++)
			{
				m.at<Vec4b>(k, j)[0] = std::min(int(photon.at<Vec4d>(k, j)[0] * 255),255);
				m.at<Vec4b>(k, j)[1] = std::min(int(photon.at<Vec4d>(k, j)[1] * 255),255);
				m.at<Vec4b>(k, j)[2] = std::min(int(photon.at<Vec4d>(k, j)[2] * 255),255);
				m.at<Vec4b>(k, j)[3] = 255;
			}

		printf("pic%d\n", i);
		imwrite("photon" + str + ".png", m);
	}

	photon = trace;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			m.at<Vec4b>(i, j)[0] = int(photon.at<Vec4d>(i, j)[0] * 255);
			m.at<Vec4b>(i, j)[1] = int(photon.at<Vec4d>(i, j)[1] * 255);
			m.at<Vec4b>(i, j)[2] = int(photon.at<Vec4d>(i, j)[2] * 255);
			m.at<Vec4b>(i, j)[3] = 255;
		}

	IplImage *img = &IplImage(m);
	cvShowImage("src", img);
	cvSetMouseCallback("src", on_mouse, img);

	imwrite("result.png", m);
	waitKey(0);
	
    return 0;
}

