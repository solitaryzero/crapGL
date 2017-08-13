#pragma once

class Vector3 {
public:
	double x, y, z;
	Vector3();
	Vector3(double x_, double y_, double z_);
	Vector3(const Vector3 &v);

	Vector3 operator+ (const Vector3 &v);
	Vector3 operator- (const Vector3 &v);
	Vector3 operator* (const double &f);
	Vector3 operator/ (const double &f);
	bool operator== (const Vector3 &v);
	double dot (const Vector3 &v);
	Vector3 cross (const Vector3 &v);
	double sqrLength();
	double length();
	Vector3 normalize();
	Vector3 negative();
	static const Vector3 zeros;
};