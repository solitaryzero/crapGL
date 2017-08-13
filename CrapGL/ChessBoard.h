#pragma once
#include "material.h"

class ChessBoard : public material
{
public:
	double scale;

	ChessBoard();
	ChessBoard(double sc);
	ChessBoard(double sc, double ref);
	virtual myColor sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular = true);
};

