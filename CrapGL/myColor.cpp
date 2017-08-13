#include "stdafx.h"
#include "myColor.h"

double myColor::myMin(double a, double b)
{
	if (a < b) return a;
	return b;
}

double myColor::myMax(double a, double b)
{
	if (a > b) return a;
	return b;
}

myColor::myColor()
{
	r = 0;
	g = 0;
	b = 0;
}

myColor::myColor(double _r, double _g, double _b)
{
	r = _r;
	g = _g;
	b = _b;
}

myColor myColor::operator+(myColor _c)
{
	return myColor(myMin(1,r+_c.r), myMin(1, g + _c.g), myMin(1, b + _c.b));
}

myColor myColor::operator*(double s)
{
	return myColor(r*s, g*s, b*s);
}

myColor myColor::modulate(myColor _c)
{
	return(myColor(r*_c.r, g*_c.g, b*_c.b));
}

myColor myColor::check()
{
	return(myColor(myMin(r,1), myMin(g, 1), myMin(b, 1)));
}

const myColor myColor::myBlack = myColor(0, 0, 0);
const myColor myColor::myWhite = myColor(1, 1, 1);
const myColor myColor::myRed = myColor(1, 0, 0);
const myColor myColor::myGreen = myColor(0, 1, 0);
const myColor myColor::myBlue = myColor(0, 0, 1);