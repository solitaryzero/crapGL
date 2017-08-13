#pragma once

class myColor {
public:
	double r, g, b;
	myColor();
	myColor(double _r, double _g, double _b);
	myColor operator+(myColor _c);
	myColor operator*(double s);
	myColor modulate(myColor _c);
	myColor check();
	static double myMin(double a, double b);
	static double myMax(double a, double b);
	static const myColor myBlack;
	static const myColor myWhite;
	static const myColor myRed;
	static const myColor myBlue;
	static const myColor myGreen;
};