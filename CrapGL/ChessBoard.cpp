#include "stdafx.h"
#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	alt_reflectiveness = 0;
	reflectiveness = 0;
	refractiveness = 0;
	scale = 1;
	transparency = 0;
	absorbance = myColor::myBlack;

}

ChessBoard::ChessBoard(double sc)
{
	alt_reflectiveness = 1;
	reflectiveness = 0;
	refractiveness = 0;
	scale = sc;
	transparency = 0;
	absorbance = myColor::myBlack;
}

ChessBoard::ChessBoard(double sc, double ref)
{
	alt_reflectiveness = 1-ref;
	reflectiveness = ref;
	refractiveness = 0;
	scale = sc;
	transparency = 0;
	absorbance = myColor::myBlack;
}

myColor ChessBoard::sample(ray v, Vector3 p, Vector3 n, myColor c, Vector3 LightDir, bool isSpecular)
{
	if (((int)floor(p.x*scale) + (int)floor(p.y*scale)) % 2 == 0)
		return myColor::myBlack;
	else return c.modulate(myColor::myWhite);
}