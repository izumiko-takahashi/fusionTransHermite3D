#include "ColorSegment.h"


ColorSegment::ColorSegment(int min, int max, double rMin, double gMin, double bMin, double rMax, double gMax, double bMax)
{
	minGrayLevel = min;
	maxGrayLevel = max;

	redMin = rMin;
	greenMin = gMin;
	blueMin = bMin;

	redMax = rMax;
	greenMax = gMax;
	blueMax = bMax;
}


ColorSegment::~ColorSegment(void)
{
}
