#include "matrixC.h"

matrixC::matrixC(int sizeX, int sizeY, int sizeZ)
{
	dimensions[0] = sizeX;
	dimensions[1] = sizeY;
	dimensions[2] = sizeZ;

	for(int i=0; i!=27; i++)
	{
		fMatrix3D *C = new fMatrix3D(boost::extents[dimensions[0]][dimensions[1]][dimensions[2]]);
		Coef.push_back(C);
	}
	mH = new fMatrix3D(boost::extents[dimensions[0]][dimensions[1]][dimensions[2]]);
}

void matrixC::SetCoef(fMatrix3D* coef, int iCoef)
{
	Coef[iCoef] = coef;
}

matrixC::fMatrix3D* matrixC::GetCoef(int iCoef)
{
	return Coef[iCoef];
}

matrixC::fMatrix3D* matrixC::GetMH(void)
{
	return mH;
}

int* matrixC::GetDimensions(void)
{
	return dimensions;
}

matrixC::~matrixC(void)
{
}
