#pragma once
#include <iostream>

class ColorSegment
{
public:

	int minGrayLevel;
	int maxGrayLevel;
	double redMin;
	double greenMin;
	double blueMin;
	double redMax;
	double greenMax;
	double blueMax;

	ColorSegment(int min, int max, double rMin, double gMin, double bMin, double rMax, double gMax, double bMax);
	~ColorSegment(void);
};

