#include "stdafx.h"
#include "PhotonMapping.h"
#define M_PI 3.1415926535

PhotonMapping::PhotonMapping(std::vector<CameraRayPoint> cross)
{
	crosses = cross;
	root = new myKDTree;
	myKDTree::bulidTree(cross, root);
}

PhotonMapping::~PhotonMapping()
{
}

Vector3 PhotonMapping::calRefract(Vector3 l, Vector3 n, double refractiveness)
{
	double tmp = 1 / refractiveness;
	double cosL = l.dot(n);
	double cosT = 1 - tmp*tmp*(1 - cosL*cosL);

	if (cosT <= 0) return Vector3::zeros;

	return (l*tmp - n*(cosL*tmp + std::sqrt(cosT))).normalize();
}

void PhotonMapping::map(scene *sc, LightSource *light, int times, Mat &m, double radius)
{
	for (int i = 0; i < times; i++)
	{
		ray ray_ = light->generateRay();
		myColor photonLumin = light->lumin*0.03;
		for (int j = 0; j < 5; j++)
		{
			IntersectInfo info = sc->intersection(ray_);
			if (info.geometry == nullptr) break;

			std::vector<CameraRayPoint> pts;

			double a_ref = info.geometry->mat->alt_reflectiveness;
			double ref = info.geometry->mat->reflectiveness;
			double refra = info.geometry->mat->refractiveness;
			double trans = info.geometry->mat->transparency;
			myColor absorbance = info.geometry->mat->absorbance;
			myColor color;
			Vector3 r, r2;

			if (info.isOutside == -1)
			{
				Vector3 r = calRefract(ray_.direction.normalize(), info.normal, double(1)/refra);
				ray_ = ray(info.position, r.normalize());
				photonLumin = photonLumin;
				continue;
			}

			double ran = double(rand()) / double(RAND_MAX);
			if (ran < a_ref)
			{
				root->getNeighbours(info.position, pts, radius, root);

				for (int j = 0; j < pts.size(); j++)
				{
					myColor tmpcolor = pts[j].info.geometry->mat->sample(pts[j].cameraRay, pts[j].info.position, pts[j].info.normal, photonLumin, ray_.direction.negative(), false);
					tmpcolor = tmpcolor * pts[j].modifier;

					m.at<Vec4d>(pts[j].x, pts[j].y)[0] += tmpcolor.b;
					m.at<Vec4d>(pts[j].x, pts[j].y)[1] += tmpcolor.g;
					m.at<Vec4d>(pts[j].x, pts[j].y)[2] += tmpcolor.r;
				}

				int bigrand = (rand() % 10000) * 10000 + (rand() % 10000);
				int theta = bigrand % 18000000;
				double theta_rad = double(theta)/double(50000)*double(M_PI) / (double)180;
				bigrand = (rand() % 10000) * 10000 + (rand() % 10000);
				int phi = bigrand % 18000000;
				double phi_rad = double(phi)/double(200000)*double(M_PI) / (double)180;

				Vector3 vt(1, 0, 0);
				if (info.normal == vt) vt = Vector3(0, 1, 0);
				Vector3 vx = info.normal.cross(vt);
				Vector3 vy = info.normal.cross(vx);
				Vector3 ans = info.normal*cos(phi_rad) + vx*sin(phi_rad)*cos(theta_rad) + vy*sin(phi_rad)*sin(theta_rad);
				ray_ = ray(info.position, ans.normalize());
				photonLumin = photonLumin.modulate(info.geometry->mat->diffuse);
			}
			else if (ran - a_ref < ref)
			{
				Vector3 r = ray_.direction - (info.normal * 2 * (info.normal.dot(ray_.direction)));
				ray_ = ray(info.position, r.normalize());
				photonLumin = photonLumin.modulate(info.geometry->mat->diffuse);
			}
			else if (ran - a_ref - ref < trans)
			{
				Vector3 r = calRefract(ray_.direction.normalize(), info.normal, refra);
				ray_ = ray(info.position, r.normalize());
				photonLumin = photonLumin.modulate(info.geometry->mat->diffuse);
			}
		}
	}
}
