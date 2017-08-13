#include "stdafx.h"
#include "BezierGeometry.h"
#define M_PI 3.1415926535897932354626

BezierGeometry::BezierGeometry()
{
	curve = BezierCurve();
	axis = ray(); 
	mat = nullptr;
}

BezierGeometry::BezierGeometry(BezierCurve curve_, ray axis_, material *m)
{
	curve = curve_;
	axis = axis_;
	mat = m;
}

BezierGeometry::~BezierGeometry()
{
}

Vector3 BezierGeometry::getPointbyuv(double u, double v)
{
	Vector3 cp = curve.getPoint(u);
	return Vector3(cp.x*cos(2 * M_PI * v), cp.x*sin(2 * M_PI *v), cp.z);
}

Vector3 BezierGeometry::getPointbyv(Vector3 p, double v)
{
	return Vector3(p.x*cos(2 * M_PI * v),p.x*sin(2 * M_PI *v),p.z);
}

Vector3 BezierGeometry::Newton(Vector3 paras, ray _ray)
{
	double t, u, v;
	Vector3 p10, p11, p20, delta, now_;
	Eigen::Vector3d xi, now;
	Eigen::Matrix3d m(3, 3), m_inv(3, 3);

	xi(0) = paras.x; xi(1) = paras.y; xi(2) = paras.z;
	for (int i=0;i<=15;i++)
	{
		t = xi(0); u = xi(1); v = xi(2);

		if ((t < -0.1) || (u < -1e-1) || (u > 1+1e-1)) return Vector3(-1, -1, -1);

		p10 = curve.p0*(1 - u) + curve.p1*u;
		p11 = curve.p1*(1 - u) + curve.p2*u;
		p20 = p10*(1 - u) + p11*u;
		delta = (p11 - p10) * 2;

		now_ = _ray.GetPoint(t) - getPointbyv(p20, v);
		if (now_.sqrLength() < 1e-6)
		{
			return Vector3(t, u, v);
		}

		m(0, 0) = _ray.direction.x;
		m(1, 0) = _ray.direction.y;
		m(2, 0) = _ray.direction.z;
		m(0, 1) = -delta.x * cos(v * 2 * M_PI);
		m(1, 1) = -delta.x * sin(v * 2 * M_PI);
		m(2, 1) = -delta.z;
		m(0, 2) = -p20.x * 2 * M_PI*(-sin(v * 2 * M_PI));
		m(1, 2) = -p20.x * 2 * M_PI*cos(v * 2 * M_PI);
		m(2, 2) = 0;

		now(0) = now_.x; now(1) = now_.y; now(2) = now_.z;
		m_inv = m.inverse().eval();
		xi = xi - m_inv*now;
	}

	return Vector3(-1,-1,-1);
}

IntersectInfo BezierGeometry::intersection(ray _ray)
{
	Vector3 para[500];
	int chosen = -1;
	bool flag = false;
	double t_now = 1000000000;
	double t, u, v;
	int times1, times2;
	times1 = 4;
	times2 = 4;
	for (int i = 0; i < times1; i++)
		for (int j = 0; j < times2; j++)
		{
			u = (double(i) + 0.5) / (double)times1;
			v = (double(j) + 0.5) / (double)times2;
			t = (_ray.point - getPointbyuv(u, v)).length();
			para[i*times2 +j] = Newton(Vector3(t, u, v), _ray);
			if ((para[i * times2 + j].x > 0) && (para[i*times2+j].y>-1e-3) && (para[i*times2 + j].y<1+1e-3) && (t_now > para[i * times2 + j].x))
			{
				if (para[i * times2 + j].x < 5e-3)
				{
					flag = true;
					continue;
				}

				chosen = i * times2 + j;
				t_now = para[i * times2 + j].x;
			}
		}

	if (chosen == -1) return IntersectInfo::noHit;

	Vector3 p10, p11, p20, delta, du,dv;

	t = para[chosen].x; u = para[chosen].y; v = para[chosen].z;
	p10 = curve.p0*(1 - u) + curve.p1*u;
	p11 = curve.p1*(1 - u) + curve.p2*u;
	p20 = p10*(1 - u) + p11*u;
	delta = (p11 - p10) * 2;

	du = Vector3(delta.x * cos(v * 2 * M_PI), delta.x * sin(v * 2 * M_PI), delta.z);
	dv = Vector3(p20.x * 2 * M_PI*(-sin(v * 2 * M_PI)), p20.x * 2 * M_PI*cos(v * 2 * M_PI), 0);

	IntersectInfo info;
	info.geometry = this;
	info.distance = t;
	info.position = _ray.GetPoint(t);
	info.normal = dv.cross(du).normalize();
	if (flag)
	{
		info.isOutside = -1;
		info.normal = info.normal.negative();
	}
	else
	{
		info.isOutside = 1;
	}

	return info;
}

struct int4
{
	int content[4];
};

void BezierGeometry::outputAsObj()
{
	freopen("bezier.obj", "w", stdout);

	std::vector<Vector3> points(0);          // 存储点
	std::vector<int4> meshes(0);            // 存储面
	double du = 0.1, dv = 0.1;             // 自定义密度
	int nu = 1 / du + 1, nv = 1 / dv + 1;   // 密度应该“除”得整

	int pid = 0;                            // 点序号
	for (double u = 0.0, i = 0; u <= 1.01; u += du, i++) {
		for (double v = 0.0, j = 0; v <= 1.01; v += dv, j++) {
			points.push_back(getPointbyuv(u,v));          // 写递归或者DP搞定函数P的计算
			pid++;                              // OBJ格式网格序号从1开始
			if (i != 0 && j != 0) {
				int4 a;
				a.content[0] = pid - nv - 1;
				a.content[1] = pid - nv;
				a.content[2] = pid;
				a.content[3] = pid - 1;
				meshes.push_back(a);
				a.content[0] = pid - nv - 1;
				a.content[1] = pid;
				a.content[2] = pid - 1;
				a.content[3] = pid - 1;
				meshes.push_back(a);
			}
		}
	}
	
	for (int i = 0; i < points.size(); i++)
	{
		printf("v %f %f %f\n",
			points[i].x, points[i].y, points[i].z);
	}

	for (int i = 0; i < meshes.size(); i++)
	{
		printf("f %d %d %d\n",
			meshes[i].content[0], meshes[i].content[1], meshes[i].content[2]);
	}

	fclose(stdout);
}