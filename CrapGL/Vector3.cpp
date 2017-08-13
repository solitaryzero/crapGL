#include "stdafx.h"
#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
	x = 0; y = 0; z = 0;
}

Vector3::Vector3(double x_, double y_, double z_)
{
	x = x_; y = y_; z = z_;
}

Vector3::Vector3(const Vector3 &v)
{
	x = v.x; y = v.y; z = v.z;
}

Vector3 Vector3::operator+ (const Vector3 &v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator- (const Vector3 &v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator* (const double &f)
{
	return Vector3(x*f, y*f, z*f);
}

Vector3 Vector3::operator/ (const double &f)
{
	double tmp = 1 / f;
	return Vector3(x*tmp, y*tmp, z*tmp);
}

bool Vector3::operator== (const Vector3 &v)
{
	return ((x==v.x) && (y==v.y) && (z==v.z));
}

double Vector3::dot(const Vector3 &v)
{
	return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::cross (const Vector3 &v)
{
	return Vector3(-z*v.y+y*v.z,z*v.x-x*v.z,-y*v.x+x*v.y);
}

double Vector3::sqrLength()
{
	return x*x + y*y + z*z;
}

double Vector3::length()
{
	return double(sqrt(x*x + y*y + z*z));
}

Vector3 Vector3::normalize()
{
	double tmp = 1/length();
	return Vector3(x*tmp,y*tmp,z*tmp);
}

Vector3 Vector3::negative()
{
	return Vector3(-x, -y, -z);
}

const Vector3 Vector3::zeros = Vector3();