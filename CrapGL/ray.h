#pragma once
#include <math.h>
#include "Vector3.h"

class ray {
public:
	Vector3 point, direction;
	
	ray();
	ray(const Vector3 &p, const Vector3 &d);

	Vector3 GetPoint(double t);
};
