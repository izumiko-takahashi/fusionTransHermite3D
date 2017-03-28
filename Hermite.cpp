#include "Hermite.h"


Hermite::Hermite(vtkSmartPointer<vtkImageData> originalData, int levels)
{
	OriginalData = originalData;
	Levels = levels;

	OriginalData->GetExtent(extent);
	OriginalData->GetSpacing(spacing);
	OriginalData->GetOrigin(origin);
	OriginalData->GetDimensions(dimensions);

}

Hermite::Hermite(int row, int column, int slice, int levels)
{
	for(int i=0; i<levels; i++)
	{
		matrixC* C = new matrixC(row,column,slice);
		Matrices.push_back(C);

		row		*= 0.5;
		column	*= 0.5;
		slice	*= 0.5;
	}
}
matrixC* Hermite::GetMatrixC(int level)
{
	return this->Matrices[level];
}

Hermite::~Hermite(void)
{
}

vtkSmartPointer<vtkImageData> Hermite::GetOriginalData(void)
{
	return OriginalData;
}

vtkSmartPointer<vtkImageData> Hermite::GenerateImageDataFromMC(int coef, int level)
{
	int dims[3];

	dims[0] = dimensions[0];
	dims[1] = dimensions[1];
	dims[2] = dimensions[2];

	for(int i=0; i<=level; i++)
	{
		dims[0] *= 0.5;
		dims[1] *= 0.5;
		dims[2] *= 0.5;
	}

	vtkSmartPointer<vtkImageData> resultingData = vtkSmartPointer<vtkImageData>::New();

	resultingData->SetDimensions(dims);
	resultingData->SetSpacing(spacing);
	resultingData->SetOrigin(origin);
	resultingData->SetScalarTypeToUnsignedShort();

	for(int k = 1; k < dims[2]; k++)
	{
		for(int j = 0; j < dims[1]; j++)
		{
			for(int i = 0; i < dims[0]; i++)
			{
				unsigned short *scalarPointerR = (unsigned short *)resultingData->GetScalarPointer(i,j,k); 
				scalarPointerR[0] = (unsigned short) (* this->GetMatrixC(level)->GetCoef(coef))[i][j][k];
				
			}
		}
	}
	

	resultingData->Update();
	return resultingData;
}

vtkSmartPointer<vtkImageData> Hermite::GetImageData(int coef)
{
	if(coef == 0)
		return OriginalData;

	vtkSmartPointer<vtkImageData> resultingData = vtkSmartPointer<vtkImageData>::New();

	resultingData->SetExtent(extent);
	resultingData->SetSpacing(spacing);
	resultingData->SetOrigin(origin);
	//resultingData->SetScalarTypeToUnsignedShort();
	resultingData->SetScalarTypeToUnsignedChar();

	for(int k = OriginalData->GetExtent()[4]; k <= OriginalData->GetExtent()[5]; k++)
	{
		for(int j = OriginalData->GetExtent()[2]; j <= OriginalData->GetExtent()[3]; j++)
		{
			for(int i = OriginalData->GetExtent()[0]; i <= OriginalData->GetExtent()[1]; i++)
			{
				unsigned char *scalarPointer = (unsigned char *)OriginalData->GetScalarPointer(i,j,k); 
				unsigned char *scalarPointerR = (unsigned char *)resultingData->GetScalarPointer(i,j,k); 
				scalarPointerR[0] =	(unsigned char) trHKernel((unsigned short)scalarPointer[0], i,j,k,coef);
			}
		}
	}

	resultingData->Update();
	return resultingData;
}

void Hermite::Proy3Dto1D(matrixC* mC)
{
	int r = mC->GetDimensions()[0];
	int c = mC->GetDimensions()[1];
	int s = mC->GetDimensions()[2];

	fMatrix3D* C1 = mC->GetCoef(1);
	fMatrix3D* C3 = mC->GetCoef(3);
	fMatrix3D* C6 = mC->GetCoef(6);
	

	for(int t=0; t!=s; t++)
	{
		for(int i=0; i!=r; i++)
		{
			for(int j=0; j!=c; j++)
			{
				double theta = 0;
				if((*C6)[i][j][t] != 0)
					atan((*C3)[i][j][t] / (*C6)[i][j][t]);

				double phi = 0;
					if((*C1)[i][j][t] != 0)
						atan(sqrt((*C6)[i][j][t] * (*C6)[i][j][t]  +  (*C3)[i][j][t] * (*C3)[i][j][t])
								/
								(*C1)[i][j][t]);

				float r = (float) (cos(phi) * (*C1)[i][j][t] + 
							sin(theta) * sin(phi) * (*C3)[i][j][t] + 
								cos(theta) * sin(phi) * (*C6)[i][j][t]);

				(*(mC->GetMH()))[i][j][t] = r;
			
			}
		}
	}
}

unsigned short Hermite::trHKernel(unsigned short value,int i, int j, int k, int coef)
{
	unsigned short F[3][3][3];
	unsigned short res;

	L_vis[1] = value + MR_vis[0][j];
    L_vis[2] = value - MR_vis[0][j];
    L_vis[3] = L_vis[1] + MC_vis[0];
    L_vis[4] = L_vis[1] - MC_vis[0]; 
    L_vis[5] = L_vis[2] + MC_vis[1];

    L_vis[7] = L_vis[3] + MT_vis[0][i][j];
    L_vis[8] = L_vis[3] - MT_vis[0][i][j];
    L_vis[9] = L_vis[4] + MT_vis[1][i][j];
    L_vis[11] = L_vis[5] + MT_vis[2][i][j];

    L_vis[15] = L_vis[7] + MR_vis[1][j];
    L_vis[16] = L_vis[7] - MR_vis[1][j]; 
    L_vis[17] = L_vis[8] + MR_vis[2][j];
    L_vis[19] = L_vis[9] + MR_vis[3][j];

    L_vis[24] = L_vis[11] - MR_vis[5][j];

    L_vis[31] = L_vis[15] + MC_vis[2];
    L_vis[32] = L_vis[15] - MC_vis[2];
    L_vis[33] = L_vis[16] + MC_vis[3];
    L_vis[34] = L_vis[16] - MC_vis[3];
    L_vis[35] = L_vis[17] + MC_vis[4]; 
    L_vis[36] = L_vis[17] - MC_vis[4];
    L_vis[40] = L_vis[19] - MC_vis[6];
    L_vis[49] = L_vis[24] + MC_vis[11];

    MR_vis[0][j] = value;

    MC_vis[0] = L_vis[1];
    MC_vis[1] = L_vis[2];

    MT_vis[0][i][j] = L_vis[3];
    MT_vis[1][i][j] = L_vis[4]; 
    MT_vis[2][i][j] = L_vis[5];

	//----------
	/* Se obtienen los coeficientes de la transformada de Hermite*/

	F[0][0][0] = (L_vis[31] + MT_vis[4][i][j])/64; //	000

	//		1er. orden
	F[1][0][0] = (L_vis[32] + MT_vis[5][i][j])/64 ;  //	100   (010)
	F[0][1][0] = (L_vis[33] + MT_vis[6][i][j])/64 ;  //	010   (100)
	F[0][0][1] = (L_vis[31] - MT_vis[4][i][j])/64 ;  //	001 

	//		2o. orden
	F[1][1][0] = (L_vis[34] + MT_vis[7][i][j])/64 ;  //	110	  (110)
	F[1][0][1] = (L_vis[32] - MT_vis[5][i][j])/64 ;  //	101   (011)
	F[0][1][1] = (L_vis[33] - MT_vis[6][i][j])/64 ;  //	011   (101)

	F[2][0][0] = (L_vis[40] + MT_vis[13][i][j])/64 ; //	200   (020)
    F[0][2][0] = (L_vis[49] + MT_vis[22][i][j])/64 ; //	020   (200)
	F[0][0][2] = (L_vis[35] - MT_vis[8][i][j])/64  ; //	002   (002)
    	
	//---------- 
	//Los datos actuales se guardan para usarlos como retraso
    MR_vis[1][j] = L_vis[7];
    MR_vis[2][j] = L_vis[8];
	MR_vis[3][j] = L_vis[9];
	MR_vis[5][j] = L_vis[11];

	MC_vis[2] = L_vis[15];
	MC_vis[3] = L_vis[16];
	MC_vis[4] = L_vis[17];
	MC_vis[6] = L_vis[19];
	MC_vis[11] = L_vis[24];

	MT_vis[4][i][j] = L_vis[31];
	MT_vis[5][i][j] = L_vis[32];
	MT_vis[6][i][j] = L_vis[33];
	MT_vis[7][i][j] = L_vis[34];
	MT_vis[8][i][j] = L_vis[35]; 
    MT_vis[9][i][j] = L_vis[36];
    MT_vis[13][i][j] = L_vis[40];
    MT_vis[22][i][j] = L_vis[49];

	switch( coef )
	{
		case 1:
			res = F[0][0][0];			//coeficiente 000
			break;
		case 2:
			res = F[1][0][0];			//coeficiente en X 010
			break;
		case 3:
			res = F[0][1][0];			//coeficiente en Y 100
			break;
		case 4:
			res = F[0][0][1];			//coeficiente en Z 001
			break;
		case 5:
			res = sqrt(  pow((float)F[1][0][0], 2) + pow((float)F[0][1][0], 2) + pow((float)F[0][0][1], 2) );//gradiente
			break;
		case 6:
			res = F[1][1][0];			//coeficiente 110
			break;
		case 7:
			res = F[1][0][1];			//coeficiente 101
			break;
		case 8:
			res = F[0][1][1];			//coeficiente 011
			break;
		case 9:
			res = F[2][0][0];			//coeficiente 200
			break;
		case 10:
			res = F[0][2][0];			//coeficiente 020
			break;
		case 11:
			res = F[0][0][2];			//coeficiente 002	
			break;
	}

	return res;
}

vtkSmartPointer<vtkImageData> Hermite::TestHermiteTransform (void)
{
	
	return OriginalData;
}

vtkSmartPointer<vtkImageData> Hermite::HermiteTransform(void)
{
	int counter = 0;
	
	while(pow(2.0f,counter) < dimensions[0])
		counter++;
	int rows = pow(2.0f,counter)+2;
	counter = 0;
	
	while(pow(2.0f,counter) < dimensions[1])
		counter++;

	int columns = pow(2.0f,counter)+2;
	counter = 0;

	while(pow(2.0f,counter) < dimensions[2])
		counter++;

	int slides = pow(2.0f,counter)+2;

	fMatrix3D *d = new fMatrix3D(boost::extents[rows][columns][slides]);

	//copiar valores del volumen original en data
	for(int k = OriginalData->GetExtent()[4]; k <= OriginalData->GetExtent()[5]; k++)
	{
		for(int i = OriginalData->GetExtent()[0]; i <= OriginalData->GetExtent()[1]; i++)
		{
			for(int j = OriginalData->GetExtent()[2]; j <= OriginalData->GetExtent()[3]; j++)
			{
			
				unsigned char *scalarPointer = (unsigned char *)OriginalData->GetScalarPointer(i,j,k); 
				float value = (float) scalarPointer[0];

				(*d)[i][j][k] = value;
				
			}
		}
	}
	
	int nRows = rows;
	int nColumns = columns;
	int nSlides = slides;
	
	for(int level=0; level < Levels; level++)
	{
		int MC[18];
		for(int i=0; i<18; i++)
			MC[i] = 0;

		fMatrix2D MR(boost::extents[9][columns]);

		fMatrix3D MT(boost::extents[36][rows][columns]);
		
		int L[62]; 
		for(int i=0; i!=62; i++)
			L[i] = 0.0;

		nRows		*= 0.5;
		nColumns	*= 0.5;
		nSlides		*= 0.5;
				
		matrixC* C = new matrixC(nRows,nColumns,nSlides);
		
		int sCounter = 0;
		for(int s = 0; s< slides; s++)
		{
			int rCounter = 0;
			for(int r = 0; r< rows; r++)
			{
				int cCounter = 0;
				for(int c = 0; c< columns; c++)
				{
					L[0] = (*d)[r][c][s] + MR[0][c]; //nivel 1 renglones
					L[1] = (*d)[r][c][s] - MR[0][c];
					
					L[2] = L[0] + MC[0];  //nivel 1 columnas
					L[3] = L[0] - MC[0];
					L[4] = L[1] + MC[1];
					L[5] = L[1] - MC[1];
					L[6] = L[2] + MT[0][r][c];  //nivel 1 cortes
					L[7] = L[2] - MT[0][r][c];
					L[8] = L[3] + MT[1][r][c];
					L[9] = L[3] - MT[1][r][c];
					L[10] = L[4] + MT[2][r][c];
					L[11] = L[4] - MT[2][r][c];
					L[12] = L[5] + MT[3][r][c];
					L[13] = L[5] - MT[3][r][c];

					///nivel 2 renglones
					L[14] = L[6] + MR[1][c];
					L[15] = L[6] - MR[1][c];
					L[16] = L[7] + MR[2][c];
					L[17] = L[7] - MR[2][c];
					L[18] = L[8] + MR[3][c];
					L[19] = L[8] - MR[3][c];
					L[20] = L[9] + MR[4][c];
					L[21] = L[9] - MR[4][c];
					L[22] =L[10] + MR[5][c];
					L[23] =L[10] - MR[5][c];
					L[24] =L[11] + MR[6][c];
					L[25] =L[11] - MR[6][c];
					L[26] =L[12] + MR[7][c];
					L[27] =L[12] - MR[7][c];
					L[28] =L[13] + MR[8][c];
					L[29] =L[13] - MR[8][c];
					
					///nivel 2 columnas
					L[30] = L[14] + MC[2];
					L[31] = L[14] - MC[2];
					L[32] = L[15] + MC[3];
					L[33] = L[15] - MC[3];
					L[34] = L[16] + MC[4];
					L[35] = L[16] - MC[4];
					L[36] = L[17] + MC[5];
					L[37] = L[17] - MC[5];
					L[38] = L[18] + MC[6];
					L[39] = L[18] - MC[6];
					L[40] = L[19] + MC[7];
					L[41] = L[19] - MC[7];
					L[42] = L[20] + MC[8];
					L[43] = L[20] - MC[8];
					L[44] = L[21] + MC[9];
					L[45] = L[21] - MC[9];
					L[46] = L[22] + MC[10];
					L[47] = L[22] - MC[10];
					L[48] = L[23] + MC[11];
					L[49] = L[23] - MC[11];
					L[50] = L[24] + MC[12];
					L[51] = L[24] - MC[12];
					L[52] = L[25] + MC[13];
					L[53] = L[25] - MC[13];
					L[54] = L[26] + MC[14];
					L[55] = L[26] - MC[14];
					L[56] = L[27] + MC[15];
					L[57] = L[27] - MC[15];
					L[58] = L[28] + MC[16];
					L[59] = L[28] - MC[16];
					L[60] = L[29] + MC[17];
					L[61] = L[29] - MC[17];

					MR[0][c] = (*d)[r][c][s]; //nivel 1 renglones
					MC[0] = L[0];  ///nivel 1 columnas
					MC[1] = L[1];
					MT[0][r][c] = L[2]; //nivel 1 corte
					MT[1][r][c] = L[3];
					MT[2][r][c] = L[4];
					MT[3][r][c] = L[5];

					MR[1][c] = L[6];
					MR[2][c] = L[7];
					MR[3][c] = L[8];
					MR[4][c] = L[9];
					MR[5][c] = L[10];
					MR[6][c] = L[11];
					MR[7][c] = L[12];
					MR[8][c] = L[13];

					MC[2] = L[14];
					MC[3] = L[15];
					MC[4] = L[16];
					MC[5] = L[17];
					MC[6] = L[18];
					MC[7] = L[19];
					MC[8] = L[20];
					MC[9] = L[21];
					MC[10]= L[22];
					MC[11]= L[23];
					MC[12]= L[24];
					MC[13]= L[25];
					MC[14]= L[26];
					MC[15]= L[27];
					MC[16]= L[28];
					MC[17]= L[29];

					if((r%2) != 0 && (c%2) != 0 && (s%2) != 0)
					{
						(*(C->GetCoef(0)))[rCounter][cCounter][sCounter] =	L[30] + MT[4][r][c];	//C000
						(*(C->GetCoef(1)))[rCounter][cCounter][sCounter] =	L[30] - MT[4][r][c];	//C001
						(*(C->GetCoef(2)))[rCounter][cCounter][sCounter] =	L[34] - MT[8][r][c];	//C002
						(*(C->GetCoef(3)))[rCounter][cCounter][sCounter] =	L[31] + MT[5][r][c];	//C010
						(*(C->GetCoef(4)))[rCounter][cCounter][sCounter] =	L[31] - MT[5][r][c];	//C011
						(*(C->GetCoef(5)))[rCounter][cCounter][sCounter] =	L[35] - MT[9][r][c];	//C012
						(*(C->GetCoef(6)))[rCounter][cCounter][sCounter] =	L[32] + MT[6][r][c];	//C100
						(*(C->GetCoef(7)))[rCounter][cCounter][sCounter] =	L[32] - MT[6][r][c];	//C101
						(*(C->GetCoef(8)))[rCounter][cCounter][sCounter] =	L[36] - MT[10][r][c];	//C102
						(*(C->GetCoef(9)))[rCounter][cCounter][sCounter] =	L[39] + MT[13][r][c];	//C020
						(*(C->GetCoef(10)))[rCounter][cCounter][sCounter] =	L[39] - MT[13][r][c];	//C021
						(*(C->GetCoef(11)))[rCounter][cCounter][sCounter] = L[43] - MT[17][r][c];	//C022
						(*(C->GetCoef(12)))[rCounter][cCounter][sCounter] = L[33] + MT[7][r][c];	//C110
						(*(C->GetCoef(13)))[rCounter][cCounter][sCounter] = L[33] - MT[7][r][c];	//C111
						(*(C->GetCoef(14)))[rCounter][cCounter][sCounter] = L[37] - MT[11][r][c];	//C112
						(*(C->GetCoef(15)))[rCounter][cCounter][sCounter] = L[48] + MT[22][r][c];	//C200
						(*(C->GetCoef(16)))[rCounter][cCounter][sCounter] = L[48] - MT[22][r][c];	//C201
						(*(C->GetCoef(17)))[rCounter][cCounter][sCounter] = L[52] - MT[26][r][c];	//C202
						(*(C->GetCoef(18)))[rCounter][cCounter][sCounter] = L[41] + MT[15][r][c];	//C120
						(*(C->GetCoef(19)))[rCounter][cCounter][sCounter] = L[59] + MT[33][r][c];	//C121
						(*(C->GetCoef(20)))[rCounter][cCounter][sCounter] = L[59] - MT[33][r][c];	//C122
						(*(C->GetCoef(21)))[rCounter][cCounter][sCounter] = L[49] + MT[23][r][c];	//C210
						(*(C->GetCoef(22)))[rCounter][cCounter][sCounter] = L[60] + MT[34][r][c];	//C211
						(*(C->GetCoef(23)))[rCounter][cCounter][sCounter] = L[60] - MT[34][r][c];	//C212
						(*(C->GetCoef(24)))[rCounter][cCounter][sCounter] = L[57] + MT[31][r][c];	//C220
						(*(C->GetCoef(25)))[rCounter][cCounter][sCounter] = L[61] + MT[35][r][c];	//C221
						(*(C->GetCoef(26)))[rCounter][cCounter][sCounter] = L[61] - MT[35][r][c];	//C222

						/*std::cout<<" cValue000 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(0)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue001 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(1)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue002 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(2)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue010 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(3)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue011 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(4)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue012 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(5)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue100 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(6)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue101 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(7)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue102 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(8)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue020 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(9)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue021 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(10)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue022 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(11)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue110 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(12)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue111 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(13)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue112 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(14)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue200 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(15)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue201 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(16)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue202 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(17)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue120 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(18)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue121 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(19)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue122 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(20)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue210 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(21)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue211 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(22)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue212 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(23)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue220 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(24)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue221 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(25)))[rCounter][cCounter][sCounter]<<std::endl;
						std::cout<<" cValue222 en r: "<<rCounter<<" c: "<<cCounter<<" s: "<<sCounter<<" es value: "<<(*(C->GetCoef(26)))[rCounter][cCounter][sCounter]<<std::endl;
						std::system("pause");
*/
						cCounter++; 
					}

					MT[4][r][c] = L[30];
					MT[5][r][c] = L[31];
					MT[6][r][c] = L[32];
					MT[7][r][c] = L[33];
					MT[8][r][c] = L[34];
					MT[9][r][c] = L[35];
					MT[10][r][c]= L[36];
					MT[11][r][c]= L[37];
					MT[12][r][c]= L[38];
					MT[13][r][c]= L[39];
					MT[14][r][c]= L[40];
					MT[15][r][c]= L[41];
					MT[16][r][c]= L[42];
					MT[17][r][c]= L[43];
					MT[18][r][c]= L[44];
					MT[19][r][c]= L[45];
					MT[20][r][c]= L[46];
					MT[21][r][c]= L[47];
					MT[22][r][c]= L[48];
					MT[23][r][c]= L[49];
					MT[24][r][c]= L[50];
					MT[25][r][c]= L[51];
					MT[26][r][c]= L[52];
					MT[27][r][c]= L[53];
					MT[28][r][c]= L[54];
					MT[29][r][c]= L[55];
					MT[30][r][c]= L[56];
					MT[31][r][c]= L[57];
					MT[32][r][c]= L[58];
					MT[33][r][c]= L[59];
					MT[34][r][c]= L[60];
					MT[35][r][c]= L[61];

					/*-------------------------------------------------------------------------------------------------------------------------*/

						/*std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C000  L[30]  ("<<L[30]<<")  +  MT[4][r][c] ("<<MT[4][r][c]<<" = "<<L[30]+MT[4][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C001  L[30]  ("<<L[30]<<")  -  MT[4][r][c] ("<<MT[4][r][c]<<" = "<<L[30]-MT[4][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C002  L[34]  ("<<L[34]<<")  -  MT[8][r][c] ("<<MT[8][r][c]<<" = "<<L[34]-MT[8][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C010  L[31]  ("<<L[31]<<")  +  MT[5][r][c] ("<<MT[5][r][c]<<" = "<<L[31]+MT[5][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C011  L[31]  ("<<L[31]<<")  -  MT[5][r][c] ("<<MT[5][r][c]<<" = "<<L[31]-MT[5][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C012  L[35]  ("<<L[35]<<")  -  MT[9][r][c] ("<<MT[9][r][c]<<" = "<<L[35]-MT[9][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C100  L[32]  ("<<L[32]<<")  +  MT[6][r][c] ("<<MT[6][r][c]<<" = "<<L[32]+MT[6][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C101  L[32]  ("<<L[32]<<")  -  MT[6][r][c] ("<<MT[6][r][c]<<" = "<<L[32]-MT[6][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C102  L[36]  ("<<L[36]<<")  -  MT[10][r][c] ("<<MT[10][r][c]<<" = "<<L[36]-MT[10][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C020  L[39]  ("<<L[39]<<")  +  MT[13][r][c] ("<<MT[13][r][c]<<" = "<<L[39]+MT[13][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C021  L[39]  ("<<L[39]<<")  -  MT[13][r][c] ("<<MT[13][r][c]<<" = "<<L[39]-MT[13][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C022  L[43]  ("<<L[43]<<")  -  MT[17][r][c] ("<<MT[17][r][c]<<" = "<<L[43]-MT[17][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C110  L[33]  ("<<L[33]<<")  +  MT[7][r][c] ("<<MT[7][r][c]<<" = "<<L[33]+MT[7][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C111  L[33]  ("<<L[33]<<")  -  MT[7][r][c] ("<<MT[7][r][c]<<" = "<<L[33]-MT[7][r][c]<<std::endl;
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C112  L[37]  ("<<L[37]<<")  -  MT[11][r][c] ("<<MT[11][r][c]<<" = "<<L[37]-MT[11][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C200  L[48]  ("<<L[48]<<")  +  MT[22][r][c] ("<<MT[22][r][c]<<" = "<<L[48]+MT[22][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C201  L[48]  ("<<L[48]<<")  -  MT[22][r][c] ("<<MT[22][r][c]<<" = "<<L[48]-MT[22][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C202  L[52]  ("<<L[52]<<")  -  MT[26][r][c] ("<<MT[26][r][c]<<" = "<<L[52]-MT[26][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C120  L[41]  ("<<L[41]<<")  +  MT[15][r][c] ("<<MT[15][r][c]<<" = "<<L[41]+MT[15][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C121  L[59]  ("<<L[59]<<")  +  MT[33][r][c] ("<<MT[33][r][c]<<" = "<<L[59]+MT[33][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C122  L[59]  ("<<L[59]<<")  -  MT[33][r][c] ("<<MT[33][r][c]<<" = "<<L[59]-MT[33][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C210  L[49]  ("<<L[49]<<")  +  MT[23][r][c] ("<<MT[23][r][c]<<" = "<<L[49]+MT[23][r][c]<<std::endl;
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C211  L[60]  ("<<L[60]<<")  +  MT[34][r][c] ("<<MT[34][r][c]<<" = "<<L[60]+MT[34][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C212  L[60]  ("<<L[60]<<")  -  MT[34][r][c] ("<<MT[34][r][c]<<" = "<<L[60]-MT[34][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C220  L[57]  ("<<L[57]<<")  +  MT[31][r][c] ("<<MT[31][r][c]<<" = "<<L[57]+MT[31][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C221  L[61]  ("<<L[61]<<")  +  MT[35][r][c] ("<<MT[35][r][c]<<" = "<<L[61]+MT[35][r][c]<<std::endl; 
						std::cout<<"Indices r: "<<r<<" c: "<<c<<" s: "<<s<<" C222  L[61]  ("<<L[61]<<")  -  MT[35][r][c] ("<<MT[35][r][c]<<" = "<<L[61]-MT[35][r][c]<<" == "<<(*(C->GetCoef(26)))[rCounter][cCounter][sCounter]<<std::endl; 

					std::system("pause");*/

					/*---------------------------------------------------------------------------------------------------------------------------- */
				}
				if((r%2) != 0)
				{
					rCounter++;
				}
			}
			if((s%2) != 0)
			{
					sCounter++;
			}
		}
		//Proy3Dto1D(C);
		Matrices.push_back(C);
		
		d = Matrices[level]->GetCoef(0);
	}
	
	return OriginalData;
}

/////----------------------------------------------------------------------------------------------------------------------
vtkSmartPointer<vtkImageData> Hermite::GetResultData(int level,int coef)
{
	int* dims = this->Matrices[0]->GetDimensions();

	vtkSmartPointer<vtkImageData> resultingData = vtkSmartPointer<vtkImageData>::New();
	resultingData->SetDimensions(dims);
	resultingData->SetSpacing(spacing);
	resultingData->SetOrigin(origin);
	resultingData->SetScalarTypeToUnsignedChar();

	for(int k=0;k <dims[2];k++)
	{
		for(int i=0; i <dims[0];i++)
		{
			for(int j=0; j<dims[1];j++)
			{
				unsigned char *scalarPointerR = (unsigned char *)resultingData->GetScalarPointer(i,j,k); //
				scalarPointerR[0] = (unsigned char) (* this->GetMatrixC(0)->GetCoef(coef))[i][j][k];
				//std::cout<<"Valor del Coef: "<<coef<<" x: "<<i<<" y: "<<j<<" z: "<<k<< " Val: "<<(*this->GetMatrixC(0)->GetCoef(coef))[i][j][k]<<std::endl;
			}
		}
	}

	resultingData->Update();
	return resultingData;
}

Hermite::fMatrix2D* Hermite::fillMA(fMatrix2D* M,int m_row,int m_column,int m_slice, int m_level)
{
	
	(*M)[0][m_column]  = ((*(Matrices[m_level]->GetCoef(0))) [m_row][m_column][m_slice])*2;
	(*M)[1][m_column]  = ((*(Matrices[m_level]->GetCoef(1))) [m_row][m_column][m_slice])*4;
	(*M)[2][m_column]  = ((*(Matrices[m_level]->GetCoef(2))) [m_row][m_column][m_slice])*2;
	(*M)[3][m_column]  = ((*(Matrices[m_level]->GetCoef(6))) [m_row][m_column][m_slice])*4;
	(*M)[4][m_column]  = ((*(Matrices[m_level]->GetCoef(7))) [m_row][m_column][m_slice])*8;
	(*M)[5][m_column]  = ((*(Matrices[m_level]->GetCoef(8))) [m_row][m_column][m_slice])*4;
	(*M)[6][m_column]  = ((*(Matrices[m_level]->GetCoef(9))) [m_row][m_column][m_slice])*2;
	(*M)[7][m_column]  = ((*(Matrices[m_level]->GetCoef(10)))[m_row][m_column][m_slice])*4;
	(*M)[8][m_column]  = ((*(Matrices[m_level]->GetCoef(11)))[m_row][m_column][m_slice])*2;
	(*M)[9][m_column]  = ((*(Matrices[m_level]->GetCoef(15)))[m_row][m_column][m_slice])*2;
	(*M)[10][m_column] = ((*(Matrices[m_level]->GetCoef(16)))[m_row][m_column][m_slice])*4;
	(*M)[11][m_column] = ((*(Matrices[m_level]->GetCoef(17)))[m_row][m_column][m_slice])*2;
	(*M)[12][m_column] = ((*(Matrices[m_level]->GetCoef(18)))[m_row][m_column][m_slice])*4;
	(*M)[13][m_column] = ((*(Matrices[m_level]->GetCoef(19)))[m_row][m_column][m_slice])*8;
	(*M)[14][m_column] = ((*(Matrices[m_level]->GetCoef(20)))[m_row][m_column][m_slice])*4;
	(*M)[15][m_column] = ((*(Matrices[m_level]->GetCoef(24)))[m_row][m_column][m_slice])*2;
	(*M)[16][m_column] = ((*(Matrices[m_level]->GetCoef(25)))[m_row][m_column][m_slice])*4;
	(*M)[17][m_column] = ((*(Matrices[m_level]->GetCoef(26)))[m_row][m_column][m_slice])*2;

	/*std::cout<<"Aqui se imprime MA"<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[0][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[1][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[2][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[3][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[4][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[5][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[6][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[7][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[8][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[9][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[10][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[11][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[12][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[13][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[14][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[15][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[16][m_column]<<std::endl;
	std::cout<<"FillMA en i: "<<m_row<<"  j: "<<m_column<<"  k: "<<m_slice<<" = "<<(*M)[17][m_column]<<std::endl;
	std::system("pause");*/
		
	return M;
	
}

Hermite::fMatrix2D* Hermite::fillMS(fMatrix2D* M,int m_row,int m_row2,int m_column,int m_column2,int m_slice,int m_slice2, int m_level)
{	
	(*M)[0][m_column]  = (*(Matrices[m_level]->GetCoef(0)))		[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(0)))[m_row2][m_column2][m_slice2];
	(*M)[1][m_column]  = ((*(Matrices[m_level]->GetCoef(1)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(1)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[2][m_column]  = (*(Matrices[m_level]->GetCoef(2)))		[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(2)))[m_row2][m_column2][m_slice2];
	(*M)[3][m_column]  = ((*(Matrices[m_level]->GetCoef(3)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(3)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[4][m_column]  = ((*(Matrices[m_level]->GetCoef(4)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(4)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[5][m_column]  = ((*(Matrices[m_level]->GetCoef(5)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(5)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[6][m_column]  = ((*(Matrices[m_level]->GetCoef(6)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(6)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[7][m_column]  = ((*(Matrices[m_level]->GetCoef(7)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(7)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[8][m_column]  = ((*(Matrices[m_level]->GetCoef(8)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(8)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[9][m_column]  = (*(Matrices[m_level]->GetCoef(9)))		[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(9)))[m_row2][m_column2][m_slice2];
	(*M)[10][m_column]  = ((*(Matrices[m_level]->GetCoef(10)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(10)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[11][m_column]  = (*(Matrices[m_level]->GetCoef(11)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(11)))[m_row2][m_column2][m_slice2];
	(*M)[12][m_column]  = ((*(Matrices[m_level]->GetCoef(12)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(12)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[13][m_column]  = ((*(Matrices[m_level]->GetCoef(13)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(13)))[m_row2][m_column2][m_slice2]) * 8.0f;
	(*M)[14][m_column]  = ((*(Matrices[m_level]->GetCoef(14)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(14)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[15][m_column]  = (*(Matrices[m_level]->GetCoef(15)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(15)))[m_row2][m_column2][m_slice2];
	(*M)[16][m_column]  = ((*(Matrices[m_level]->GetCoef(16)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(16)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[17][m_column]  = (*(Matrices[m_level]->GetCoef(17)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(17)))[m_row2][m_column2][m_slice2];
	(*M)[18][m_column]  = ((*(Matrices[m_level]->GetCoef(18)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(18)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[19][m_column]  = ((*(Matrices[m_level]->GetCoef(19)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(19)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[20][m_column]  = ((*(Matrices[m_level]->GetCoef(20)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(20)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[21][m_column]  = ((*(Matrices[m_level]->GetCoef(21)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(21)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[22][m_column]  = ((*(Matrices[m_level]->GetCoef(22)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(22)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[23][m_column]  = ((*(Matrices[m_level]->GetCoef(23)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(23)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[24][m_column]  = (*(Matrices[m_level]->GetCoef(24)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(24)))[m_row2][m_column2][m_slice2];
	(*M)[25][m_column]  = ((*(Matrices[m_level]->GetCoef(25)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(25)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[26][m_column]  = (*(Matrices[m_level]->GetCoef(26)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(26)))[m_row2][m_column2][m_slice2];

	/*std::cout<<"Aqui se imprime MS normal"<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[0][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[1][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[2][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[3][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[4][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[5][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[6][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[7][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[8][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[9][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[10][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[11][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[12][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[13][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[14][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[15][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[16][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[17][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[18][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[19][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[20][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[21][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[22][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[23][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[24][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[25][m_column]<<std::endl;
	std::cout<<"FillMs en column1"<<m_column<<"  column2: "<<m_column2<<" = "<<(*M)[26][m_column]<<std::endl;
	
	std::system("pause");*/
			
		
	return M;
	
}
Hermite::fMatrix2D* Hermite::fillLastMS(fMatrix2D* M,int m_row,int m_column,int m_slice, int m_level)
{
	(*M)[0][m_column]  = (*(Matrices[m_level]->GetCoef(0)))	[m_row][m_column][m_slice]  ;
	(*M)[1][m_column]  = (*(Matrices[m_level]->GetCoef(1)))	[m_row][m_column][m_slice]*2;
	(*M)[2][m_column]  = (*(Matrices[m_level]->GetCoef(2)))	[m_row][m_column][m_slice]  ;
	(*M)[3][m_column]  = (*(Matrices[m_level]->GetCoef(3)))	[m_row][m_column][m_slice]*2;
	(*M)[4][m_column]  = (*(Matrices[m_level]->GetCoef(4)))	[m_row][m_column][m_slice]*4;
	(*M)[5][m_column]  = (*(Matrices[m_level]->GetCoef(5)))	[m_row][m_column][m_slice]*2;
	(*M)[6][m_column]  = (*(Matrices[m_level]->GetCoef(6)))	[m_row][m_column][m_slice]*2;
	(*M)[7][m_column]  = (*(Matrices[m_level]->GetCoef(7)))	[m_row][m_column][m_slice]*4;
	(*M)[8][m_column]  = (*(Matrices[m_level]->GetCoef(8)))	[m_row][m_column][m_slice]*2;
	(*M)[9][m_column]  = (*(Matrices[m_level]->GetCoef(9)))	[m_row][m_column][m_slice] ;
	(*M)[10][m_column] = (*(Matrices[m_level]->GetCoef(10)))[m_row][m_column][m_slice] *2;
	(*M)[11][m_column] = (*(Matrices[m_level]->GetCoef(11)))[m_row][m_column][m_slice]  ;
	(*M)[12][m_column] = (*(Matrices[m_level]->GetCoef(12)))[m_row][m_column][m_slice] *4;
	(*M)[13][m_column] = (*(Matrices[m_level]->GetCoef(13)))[m_row][m_column][m_slice] *8;
	(*M)[14][m_column] = (*(Matrices[m_level]->GetCoef(14)))[m_row][m_column][m_slice] *4;
	(*M)[15][m_column] = (*(Matrices[m_level]->GetCoef(15)))[m_row][m_column][m_slice]  ;
	(*M)[16][m_column] = (*(Matrices[m_level]->GetCoef(16)))[m_row][m_column][m_slice] *2;
	(*M)[17][m_column] = (*(Matrices[m_level]->GetCoef(17)))[m_row][m_column][m_slice]  ;
	(*M)[18][m_column] = (*(Matrices[m_level]->GetCoef(18)))[m_row][m_column][m_slice] *2;
	(*M)[19][m_column] = (*(Matrices[m_level]->GetCoef(19)))[m_row][m_column][m_slice] *4;
	(*M)[20][m_column] = (*(Matrices[m_level]->GetCoef(20)))[m_row][m_column][m_slice] *2;
	(*M)[21][m_column] = (*(Matrices[m_level]->GetCoef(21)))[m_row][m_column][m_slice] *2;
	(*M)[22][m_column] = (*(Matrices[m_level]->GetCoef(22)))[m_row][m_column][m_slice] *4;
	(*M)[23][m_column] = (*(Matrices[m_level]->GetCoef(23)))[m_row][m_column][m_slice] *2;
	(*M)[24][m_column] = (*(Matrices[m_level]->GetCoef(24)))[m_row][m_column][m_slice] ;
	(*M)[25][m_column] = (*(Matrices[m_level]->GetCoef(25)))[m_row][m_column][m_slice] *2;
	(*M)[26][m_column] = (*(Matrices[m_level]->GetCoef(26)))[m_row][m_column][m_slice] ;

	/*std::cout<<"Se muestra MS para el ultimo elemento"<<std::endl;
	system("pause");*/
	
	return M;
	
}

Hermite::fVector* Hermite::fillMtmpLikeMA(fVector* M,int m_row,int m_column,int m_slice, int m_level)
{
	(*M)[0]  = ((*(Matrices[m_level]->GetCoef(0))) [m_row][m_column][m_slice])*2;
	(*M)[1]  = ((*(Matrices[m_level]->GetCoef(1))) [m_row][m_column][m_slice])*4;
	(*M)[2]  = ((*(Matrices[m_level]->GetCoef(2))) [m_row][m_column][m_slice])*2;
	(*M)[3]  = ((*(Matrices[m_level]->GetCoef(6))) [m_row][m_column][m_slice])*4;
	(*M)[4]  = ((*(Matrices[m_level]->GetCoef(7))) [m_row][m_column][m_slice])*8;
	(*M)[5]  = ((*(Matrices[m_level]->GetCoef(8))) [m_row][m_column][m_slice])*4;
	(*M)[6]  = ((*(Matrices[m_level]->GetCoef(9))) [m_row][m_column][m_slice])*2;
	(*M)[7]  = ((*(Matrices[m_level]->GetCoef(10)))[m_row][m_column][m_slice])*4;
	(*M)[8]  = ((*(Matrices[m_level]->GetCoef(11)))[m_row][m_column][m_slice])*2;
	(*M)[9]  = ((*(Matrices[m_level]->GetCoef(15)))[m_row][m_column][m_slice])*2;
	(*M)[10] = ((*(Matrices[m_level]->GetCoef(16)))[m_row][m_column][m_slice])*4;
	(*M)[11] = ((*(Matrices[m_level]->GetCoef(17)))[m_row][m_column][m_slice])*2;
	(*M)[12] = ((*(Matrices[m_level]->GetCoef(18)))[m_row][m_column][m_slice])*4;
	(*M)[13] = ((*(Matrices[m_level]->GetCoef(19)))[m_row][m_column][m_slice])*8;
	(*M)[14] = ((*(Matrices[m_level]->GetCoef(20)))[m_row][m_column][m_slice])*4;
	(*M)[15] = ((*(Matrices[m_level]->GetCoef(24)))[m_row][m_column][m_slice])*2;
	(*M)[16] = ((*(Matrices[m_level]->GetCoef(25)))[m_row][m_column][m_slice])*4;
	(*M)[17] = ((*(Matrices[m_level]->GetCoef(26)))[m_row][m_column][m_slice])*2;

	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[0]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[1]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[2]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[3]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[4]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[5]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[6]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[7]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[8]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[9]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[10]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[11]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[12]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[13]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[14]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[15]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[16]<<std::endl;
	std::cout<<"FillMtmp MA en j: "<<m_column<<" = "<<(*M)[17]<<std::endl;
	std::system("pause");

	return M;
}
Hermite::fVector* Hermite::fillMtmpLikeMS(fVector* M,int m_row,int m_row2,int m_column,int m_column2,int m_slice,int m_slice2, int m_level)
{
	(*M)[0]	  =	(*(Matrices[m_level]->GetCoef(0)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(0))) [m_row2][m_column2][m_slice2];
	(*M)[1]	  = ((*(Matrices[m_level]->GetCoef(1)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(1))) [m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[2]	  = (*(Matrices[m_level]->GetCoef(2)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(2))) [m_row2][m_column2][m_slice2];
	(*M)[3]	  = ((*(Matrices[m_level]->GetCoef(3)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(3))) [m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[4]	  = ((*(Matrices[m_level]->GetCoef(4)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(4))) [m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[5]	  = ((*(Matrices[m_level]->GetCoef(5)))	[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(5))) [m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[6]	  = ((*(Matrices[m_level]->GetCoef(6)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(6))) [m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[7]	  = ((*(Matrices[m_level]->GetCoef(7)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(7))) [m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[8]	  = ((*(Matrices[m_level]->GetCoef(8)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(8))) [m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[9]	  = (*(Matrices[m_level]->GetCoef(9)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(9))) [m_row2][m_column2][m_slice2];
	(*M)[10]  = ((*(Matrices[m_level]->GetCoef(10)))[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(10)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[11]  = (*(Matrices[m_level]->GetCoef(11)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(11)))[m_row2][m_column2][m_slice2];
	(*M)[12]  = ((*(Matrices[m_level]->GetCoef(12)))[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(12)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[13]  = ((*(Matrices[m_level]->GetCoef(13)))[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(13)))[m_row2][m_column2][m_slice2]) * 8.0f;
	(*M)[14]  = ((*(Matrices[m_level]->GetCoef(14)))[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(14)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[15]  = (*(Matrices[m_level]->GetCoef(15)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(15)))[m_row2][m_column2][m_slice2];
	(*M)[16]  = ((*(Matrices[m_level]->GetCoef(16)))[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(16)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[17]  = (*(Matrices[m_level]->GetCoef(17)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(17)))[m_row2][m_column2][m_slice2];
	(*M)[18]  = ((*(Matrices[m_level]->GetCoef(18)))[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(18)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[19]  = ((*(Matrices[m_level]->GetCoef(19)))[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(19)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[20]  = ((*(Matrices[m_level]->GetCoef(20)))[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(20)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[21]  = ((*(Matrices[m_level]->GetCoef(21)))[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(21)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[22]  = ((*(Matrices[m_level]->GetCoef(22)))[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(22)))[m_row2][m_column2][m_slice2]) * 4.0f;
	(*M)[23]  = ((*(Matrices[m_level]->GetCoef(23)))[m_row][m_column][m_slice] - (*(Matrices[m_level]->GetCoef(23)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[24]  = (*(Matrices[m_level]->GetCoef(24)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(24)))[m_row2][m_column2][m_slice2];
	(*M)[25]  = ((*(Matrices[m_level]->GetCoef(25)))[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(25)))[m_row2][m_column2][m_slice2]) * 2.0f;
	(*M)[26]  = (*(Matrices[m_level]->GetCoef(26)))	[m_row][m_column][m_slice] + (*(Matrices[m_level]->GetCoef(26)))[m_row2][m_column2][m_slice2];

	std::cout<<"Aqui se imprime Mtmp como MS"<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[0]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[1]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[2]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[3]<<std::endl;

	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[4]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[5]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[6]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[7]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[8]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[9]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[10]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[11]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[12]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[13]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[14]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[15]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[16]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[17]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[18]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[19]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[20]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[21]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[22]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[23]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[24]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[25]<<std::endl;
	std::cout<<"FillMtmp MS en j1: "<<m_column<<" j2: "<<m_column2<<" = "<<(*M)[26]<<std::endl;
	std::system("pause");


	return M;
	
		
}
Hermite::fVector* Hermite::fillMtmpLast(fVector* M,int m_row,int m_column,int m_slice,int m_level)
{
	(*M)[0] = (*(Matrices[m_level]->GetCoef(0)))	[m_row][m_column][m_slice]  ;
	(*M)[1]  = (*(Matrices[m_level]->GetCoef(1)))	[m_row][m_column][m_slice]*2;
	(*M)[2] = (*(Matrices[m_level]->GetCoef(2)))	[m_row][m_column][m_slice]  ;
	(*M)[3] = (*(Matrices[m_level]->GetCoef(3)))	[m_row][m_column][m_slice]*2;
	(*M)[4] = (*(Matrices[m_level]->GetCoef(4)))	[m_row][m_column][m_slice]*4;
	(*M)[5] = (*(Matrices[m_level]->GetCoef(5)))	[m_row][m_column][m_slice]*2;
	(*M)[6] = (*(Matrices[m_level]->GetCoef(6)))	[m_row][m_column][m_slice]*2;
	(*M)[7] = (*(Matrices[m_level]->GetCoef(7)))	[m_row][m_column][m_slice]*4;
	(*M)[8] = (*(Matrices[m_level]->GetCoef(8)))	[m_row][m_column][m_slice]*2;
	(*M)[9] = (*(Matrices[m_level]->GetCoef(9)))	[m_row][m_column][m_slice] ;
	(*M)[10] = (*(Matrices[m_level]->GetCoef(10)))[m_row][m_column][m_slice] *2;
	(*M)[11] = (*(Matrices[m_level]->GetCoef(11)))[m_row][m_column][m_slice]  ;
	(*M)[12]= (*(Matrices[m_level]->GetCoef(12)))[m_row][m_column][m_slice] *4;
	(*M)[13]= (*(Matrices[m_level]->GetCoef(13)))[m_row][m_column][m_slice] *8;
	(*M)[14]= (*(Matrices[m_level]->GetCoef(14)))[m_row][m_column][m_slice] *4;
	(*M)[15]= (*(Matrices[m_level]->GetCoef(15)))[m_row][m_column][m_slice]  ;
	(*M)[16] = (*(Matrices[m_level]->GetCoef(16)))[m_row][m_column][m_slice] *2;
	(*M)[17] = (*(Matrices[m_level]->GetCoef(17)))[m_row][m_column][m_slice]  ;
	(*M)[18]= (*(Matrices[m_level]->GetCoef(18)))[m_row][m_column][m_slice] *2;
	(*M)[19]= (*(Matrices[m_level]->GetCoef(19)))[m_row][m_column][m_slice] *4;
	(*M)[20]= (*(Matrices[m_level]->GetCoef(20)))[m_row][m_column][m_slice] *2;
	(*M)[21]= (*(Matrices[m_level]->GetCoef(21)))[m_row][m_column][m_slice] *2;
	(*M)[22]= (*(Matrices[m_level]->GetCoef(22)))[m_row][m_column][m_slice] *4;
	(*M)[23]= (*(Matrices[m_level]->GetCoef(23)))[m_row][m_column][m_slice] *2;
	(*M)[24]= (*(Matrices[m_level]->GetCoef(24)))[m_row][m_column][m_slice] ;
	(*M)[25]= (*(Matrices[m_level]->GetCoef(25)))[m_row][m_column][m_slice] *2;
	(*M)[26]= (*(Matrices[m_level]->GetCoef(26)))[m_row][m_column][m_slice] ;
	
	return M;
}
Hermite::fVector* Hermite::fillMtmpZeroMS(fVector* M, int m_column)
{
	M = new fVector(boost::extents[m_column]);
}


vtkSmartPointer<vtkImageData> Hermite::HermiteInverseTransform(void)
{

	//int level = Levels; ///Los valores de Matrices serán 0 y 1.
	int nRow;
	int nColumn;
	int nSlice;
	int i,j,k,r,c,s,p,aux;

	volumeResult = vtkSmartPointer<vtkImageData>::New();
	
	
	volumeResult->SetDimensions(dimensions);
	//std::cout<<"dimensions: "<<dimensions[0]<<" "<<dimensions[1]<<" "<<dimensions[2]<<std::endl;
	//volumeResult->SetDimensions(256,256,64);
	volumeResult->SetWholeExtent(extent);
	volumeResult->SetSpacing(spacing);
	volumeResult->SetOrigin(origin);
	volumeResult->SetScalarTypeToUnsignedShort();

	//int dim[3];
	//volumeResult->GetDimensions(dim);
	//std::cout<<OriginalData->GetExtent()[4]<<"++++"<<OriginalData->GetExtent()[5]<<std::endl;
	//std::cout<<OriginalData->GetExtent()[0]<<"++++"<<OriginalData->GetExtent()[1]<<std::endl;
	//std::cout<<OriginalData->GetExtent()[2]<<"++++"<<OriginalData->GetExtent()[3]<<std::endl;
	
	fMatrix3D *imageAux;// = new fMatrix3D(boost::extents[dim[0]][dim[1]][dim[2]]);
	//fMatrix3D *imageAux = new fMatrix3D(boost::extents[256][256][64]);
	
	for(int l = Levels-1; l >= 0; l--)
	{
		nRow    = Matrices[l]->GetDimensions()[0]-1 ;
		nColumn = Matrices[l]->GetDimensions()[1]-1 ;
		nSlice  = Matrices[l]->GetDimensions()[2]-1 ;

		std::cout<<"DIMENSIONS ITRANSFORM :"<<nRow<<" "<<nColumn<<" "<<nSlice<<std::endl;

		
		fVector *Mtmp	  = new fVector(boost::extents[27]);
		fMatrix2D *MA	  = new fMatrix2D(boost::extents[18][nColumn+1]);	
		fMatrix2D *MS	  = new fMatrix2D(boost::extents[27][nColumn+1]);
		fMatrix2D *MAtmp  = new fMatrix2D(boost::extents[18][nColumn+1]);
		fMatrix2D *MStmp  = new fMatrix2D(boost::extents[27][nColumn+1]);
		fMatrix3D *MZA	  = new fMatrix3D(boost::extents[18][nRow+1][nColumn+1]);//???????????????????????
		fMatrix3D *MZS	  = new fMatrix3D(boost::extents[27][nRow+1][nColumn+1]);//???????????????????????
		fMatrix3D *image  = new fMatrix3D(boost::extents[nRow*2][nColumn*2][nSlice*2]);
		fMatrix2D *MZAtmp = new fMatrix2D(boost::extents[18][nColumn+1]);
		fMatrix2D *MZStmp = new fMatrix2D(boost::extents[27][nColumn+1]);
				
		if(l != Levels-1)
		{
			Matrices[l]->SetCoef(image, 0);
		}

		p=0, r=0, c=0, s=0; //Primer corte, corte par
		i=0,k=0;
		nRow--;
		nColumn--;
		nSlice--;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////Se comienza llenando las matrices MA y MS con el primer renglón completo///////////////////////////////////
		for(j=0;j <= (nColumn+1);j++)
		{
			fillMA(MA,i,j,k,l);
			/*std::cout<<"FillMA con "<<i<<"  "<<j<<"   "<<k<<" = "<<(*MA)[i][j]<<std::endl;
			system("pause");*/
			if(j != nColumn+1)
				fillMS(MS,i,i,j,j+1,k,k,l);
			else
				fillMS(MS,i,i+1,j,0,k,k,l);
			
			/*std::cout<<"FillMS con "<<i<<"  "<<j<<"   "<<k<<" = "<<(*MS)[i][j]<<std::endl;
			system("pause");*/
			for(p = 0;p <= 17;p++)
			{
				(*MZA)[p][0][j] = (*MA)[p][j];
			}
			//std::cout<<"MZA[p][0][j] "<<p<<"  "<<"0"<<"   "<<j<<std::endl;
			
			for(p = 0;p<=26;p++)
			{
				(*MZS)[p][0][j] = (*MS)[p][j];
			}
			//std::cout<<"MZS[p][0][j] "<<p<<"  "<<"0"<<"   "<<j<<std::endl;
		}
		//////////////////////////////////////////////////////////////////////////////////////////
		/////Primer corte, primer renglon//////////////////////////////////////////////////////
		for(j = 0;j <= (nColumn);j++)
		{								
			(*image)[r][c][s] = ((*MA)[0][j]-(*MA)[2][j]-(*MA)[6][j]+(*MA)[8][j]
								-(*MA)[9][j]+(*MA)[11][j]+(*MA)[15][j]-(*MA)[17][j]) / 128; //Caso 1
			/*std::cout<<"MA[0]["<<j<<"]  = "<<(*MA)[0][j]<<std::endl;
			std::cout<<"MA[2]["<<j<<"]  = "<<(*MA)[2][j]<<std::endl;
			std::cout<<"MA[6]["<<j<<"]  = "<<(*MA)[6][j]<<std::endl;
			std::cout<<"MA[8]["<<j<<"]  = "<<(*MA)[8][j]<<std::endl;
			std::cout<<"MA[9]["<<j<<"]  = "<<(*MA)[9][j]<<std::endl;
			std::cout<<"MA[11]["<<j<<"]  = "<<(*MA)[11][j]<<std::endl;
			std::cout<<"MA[15]["<<j<<"]  = "<<(*MA)[15][j]<<std::endl;
			std::cout<<"MA[17]["<<j<<"]  = "<<(*MA)[17][j]<<std::endl;*/
			std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
			system("pause");
			c++;
			(*image)[r][c][s] =  ((*MS)[0][j]  - (*MS)[2][j]  + (*MS)[9][j]  - (*MS)[11][j]
								- (*MS)[15][j] + (*MS)[17][j] - (*MS)[24][j] + (*MS)[26][j]
								+ (*MS)[3][j]  - (*MS)[5][j]  - (*MS)[21][j] + (*MS)[23][j]) / 128; //Caso 2
			std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
			c++;
		}//fin de j hasta nColumn
		r++;
		///////////
		//Ciclo iterativo para llenar el resto del primer corte del volumen y guardar todos los valores para MZ
		//std::cout<<"Primer corte, primer renglon init OK"<<std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for(i = 1;i <= (nRow+1);i++)
		{
			/*std::cout<<i<<std::endl;
			std::cout<<"Resto del renglon init"<<std::endl;*/
			c=0;
			for(j = 0;j <= (nColumn);j++)
			{
				///Guardar en Mtmp(0..17) la asignación MA (MA no se actualiza en este paso) 
				///En las matrices de coeficientes se inicia desde el segundo renglón ya que con el primer renglón se llenó el ciclo anterior
				///Diferencias entre renglones del corte central (filtros verde y lila)
				fillMtmpLikeMA(Mtmp,i,j,k,l);
				(*image)[r][c][s] =  ((*MA)[0][j]  + (*Mtmp)[0]  - (*MA)[2][j]  - (*Mtmp)[2]
									+ (*MA)[3][j]  - (*Mtmp)[3]  - (*MA)[5][j]  + (*Mtmp)[5]
									- (*MA)[6][j]  - (*Mtmp)[6]  + (*MA)[8][j]  + (*Mtmp)[8]
									+ (*MA)[9][j]  + (*Mtmp)[9]  - (*MA)[11][j] - (*Mtmp)[11]
									- (*MA)[12][j] + (*Mtmp)[12] + (*MA)[14][j] - (*Mtmp)[14]
									- (*MA)[15][j] - (*Mtmp)[15] + (*MA)[17][j] + (*Mtmp)[17]) /256; ///Caso 3
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;

				c++;
				for(p = 0;p <= 17;p++)
				{
					(*MA)[p][j] = (*Mtmp)[p];
					(*MZA)[p][i][j] = (*Mtmp)[p]; //?????????????????????????????????
					
				}
				
			if(j != (nColumn+1))
			{
				/*std::cout<<"Entra cuando j != nColumn"<<std::endl;*/
				fillMtmpLikeMS(Mtmp,i,i,j,j+1,k,k,l);
			}
			else
				if(i!=nRow)
				{
					/*std::cout<<"Entra al else si i != nRow"<<std::endl;*/
					fillMtmpLikeMS(Mtmp,i,i+1,j,0,k,k,l);
				}
				else
				{
					/*std::cout<<"Entra al ultimo else"<<std::endl;*/
					fillMtmpLikeMS(Mtmp,i,i,j,j+1,k+1,k+1,l);
				}
			/*std::cout<<"FillMS con "<<i<<"  "<<j<<"   "<<k<<std::endl;*/
				//std::cout<<"Llena MS para el resto de los renglones"<<std::endl;
				//if(i == 63)
				//		std::cout<<"salio"<<std::endl;
				///Diferencias entre columnas del corte central (son 4 elementos, 
				///diferencia entre dos columnas del renglón anterior y del actual) Filtros verde, azul claro, cyan y lila
				(*image)[r][c][s] = ((*MS)[0][j]  + (*Mtmp)[0]  - (*MS)[2][j]  - (*Mtmp)[2]
									+(*MS)[3][j]  + (*Mtmp)[3]  - (*MS)[5][j]  - (*Mtmp)[5]
									+(*MS)[6][j]  - (*Mtmp)[6]  - (*MS)[8][j]  + (*Mtmp)[8]
									+(*MS)[9][j]  + (*Mtmp)[9]  - (*MS)[11][j] - (*Mtmp)[11]
									+(*MS)[12][j] - (*Mtmp)[12] - (*MS)[14][j] + (*Mtmp)[14]
									+(*MS)[15][j] + (*Mtmp)[15] - (*MS)[17][j] - (*Mtmp)[17]
									+(*MS)[18][j] - (*Mtmp)[18] - (*MS)[20][j] + (*Mtmp)[20]
									+(*MS)[21][j] + (*Mtmp)[21] - (*MS)[23][j] - (*Mtmp)[23]
									+(*MS)[24][j] + (*Mtmp)[24] - (*MS)[26][j] - (*Mtmp)[26]) / 256; ////Caso 4
			
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
				c++;
				///Guardar MS y MZS con los valores de Mtmp:
				for(p = 0;p <= 26;p++)
				{
					(*MS)[p][j] = (*Mtmp)[p];
					(*MZS)[p][i][j] = (*Mtmp)[p]; //????????????????????????????????'
				}
				//if(i == 63)
			}//fin de j hasta nColumn iterativo de Columnas
			r++;
			
			
		/////La siguiente condicional es necesaria porque primero se recupera solo una fila, y como tenemos dimensiones pares,
		///esta parte del ciclo iterativo no se realizará cuando estemos en el penúltimo renglón, esto aplicará también para
		///los demás cortes más adelante
		if(i != (nRow+1))
		{
			c=0;
			for(j=0;j<=(nColumn);j++)
			{
				(*image)[r][c][s] = ((*MA)[0][j] - (*MA)[2][j]  - (*MA)[6][j]  + (*MA)[8][j]
									-(*MA)[9][j] + (*MA)[11][j] + (*MA)[15][j] - (*MA)[17][j]) / 128;  ///Caso 1
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;			
				c++;
				(*image)[r][c][s] = ((*MS)[0][j]  - (*MS)[2][j]  + (*MS)[9][j]  - (*MS)[11][j]
									-(*MS)[15][j] + (*MS)[17][j] - (*MS)[24][j] + (*MS)[26][j]
									+(*MS)[3][j]  - (*MS)[5][j]  - (*MS)[21][j] + (*MS)[23][j]) / 128;   ///Caso 2
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
				c++;
			}//Fin del for j hasta nColumn
			r++;
		}//Fin del if i diferente de nRow condicional
	}//Fin del i hasta renglones -1
	
		//std::cout<<"Aquí termina el primer corte"<<std::endl;
//////////////////////////////////////////////////////////////////////////////////////////////////
	s++;  ///los demás cortes, a partir de aquí se alternan los 8 casos.
	

	for(k = 1;k <= (nSlice+1);k++)
	{	
		r=0,c=0;  ///Corte Impar
		//std::cout<<"Entra al ciclo"<<std::endl;
		for(j = 0;j <= (nColumn);j++)
		{
			///Guardar MA, MS con los valores de k+1,0,j actuales
			fillMA(MA,0,j,k,l);
			/*if(j != nColumn)
				fillMS(MS,0,0,j,j+1,k,k,l);
			else
				fillMS(MS,0,1,j,0,k,k,l);*/
			if(j != nColumn+1)//////////////
				fillMS(MS,0,0,j,j+1,k,k,l);
			else
					if(k != (nSlice+1))
						fillMS(MS,0,0,j,j+1,k+1,k+1,l);
					else
						fillLastMS(MS,0,j,k,l);
			//std::cout<<"FillMS con "<<i<<"  "<<j<<"   "<<k<<std::endl;
			///Solo importan los pixeles centrales de los dos cortes Filtros verdes y anaranjados 
			(*image)[r][c][s] = ((*MZA)[0][0][j]  + (*MA)[0][j]  + (*MZA)[1][0][j]  - (*MA)[1][j]
								+(*MZA)[2][0][j]  + (*MA)[2][j]  - (*MZA)[6][0][j]  - (*MA)[6][j]
								-(*MZA)[7][0][j]  + (*MA)[7][j]  - (*MZA)[8][0][j]  - (*MA)[8][j]
								-(*MZA)[9][0][j]  - (*MA)[9][j]  - (*MZA)[10][0][j] + (*MA)[10][j]
								-(*MZA)[11][0][j] - (*MA)[11][j] + (*MZA)[15][0][j] + (*MA)[15][j]
								+(*MZA)[16][0][j] - (*MA)[16][j] + (*MZA)[17][0][j] + (*MA)[17][j]) / 256; ////Caso 5
			std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
			c++;
			///Diferencias entre columnas de los dos cortes, renglón central, MS enfrente, MZS atrás. Filtros verdes, anaranjados, cyan, gris
			(*image)[r][c][s] =   ((*MZS)[0][0][j]  + (*MS)[0][j]  + (*MZS)[1][0][j]  - (*MS)[1][j]
									+(*MZS)[2][0][j]  + (*MS)[2][j]  + (*MZS)[3][0][j]  + (*MS)[3][j]
									+(*MZS)[4][0][j]  - (*MS)[4][j]  + (*MZS)[5][0][j]  + (*MS)[5][j]
									+(*MZS)[9][0][j]  + (*MS)[9][j]  + (*MZS)[10][0][j] - (*MS)[10][j]
									+(*MZS)[11][0][j] + (*MS)[11][j] - (*MZS)[15][0][j] - (*MS)[15][j]
									-(*MZS)[16][0][j] + (*MS)[16][j] - (*MZS)[17][0][j] - (*MS)[17][j]
									-(*MZS)[21][0][j] - (*MS)[21][j] - (*MZS)[22][0][j] + (*MS)[22][j]
									-(*MZS)[23][0][j] - (*MS)[23][j] - (*MZS)[24][0][j] - (*MS)[24][j]
									-(*MZS)[25][0][j] + (*MS)[25][j] - (*MZS)[26][0][j] - (*MS)[26][j]) / 256; ////Caso 6
			std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
			c++;
		}//Fin del for j hasta nColumn
		//std::cout<<"Tercer ciclo"<<std::endl;
		r++;
				
///*---------------------------------------------------------------*///////////////////
		
		for(aux = 0;aux <= (nColumn);aux++)
		{
			for(p = 0;p <= 17;p++)
			{
				(*MZAtmp)[p][aux] = (*MZA)[p][0][aux];
				(*MZA)[p][0][aux] = (*MA)[p][aux];
			}//fin del ciclo para llenar mis matrices MZAtmp MZA MA
			
		}
		
		for(aux = 0;aux <= (nColumn);aux++)
		{
			for(p = 0;p <= 26;p++)
			{
				(*MZStmp)[p][aux] = (*MZS)[p][0][aux];
				(*MZS)[p][0][aux] = (*MS)[p][aux];
			}// fin del ciclo de llenado MS MZS MZStmp
		}
		
		for(i = 0;i <= (nRow);i++)//<<<for(i = 0;i <= (nRow-1);i++)>>>
		{
			c=0;
			///Guardar MAtmp y MStmp con MZA y MZS respectivamente:
			
			for(aux = 0;aux <= (nColumn);aux++)
			{
				for(p = 0;p <= 17;p++)
				{
					(*MAtmp)[p][aux] = (*MZA)[p][i+1][aux];
				}
			}
			for(aux = 0; aux <= (nColumn);aux++)
			{
				for(p = 0;p <= 26;p++)
				{

					(*MStmp)[p][aux] = (*MZS)[p][i+1][aux];//??????????????????????????????????????????????????????????????????

				}
			}
			for(j = 0;j <= (nColumn);j++)//<<<for(j = 0;j <= (nColumn-1);j++)>>>//
			{
				//std::cout<<"Renglon i_"<<i<<"_Columna j_"<<j<<std::endl;
				///Guardar Mtmp(0..17) como MA (MA no modifica sus valores)
				fillMtmpLikeMA(Mtmp,i+1,j,k,l);
				///Diferencias entre renglones de los dos cortes(filtros verdes, anaranjados,lila,rosa)
				(*image)[r][c][s] =   ((*MZAtmp)[0][j]  + (*MZA)[0][i+1][j]  + (*MA)[0][j]  + (*Mtmp)[0]
										+ (*MZAtmp)[1][j]  + (*MZA)[1][i+1][j]  - (*MA)[1][j]  - (*Mtmp)[1]
										+ (*MZAtmp)[2][j]  + (*MZA)[2][i+1][j]  + (*MA)[2][j]  + (*Mtmp)[2]
										+ (*MZAtmp)[3][j]  - (*MZA)[3][i+1][j]  + (*MA)[3][j]  - (*Mtmp)[3]
										+ (*MZAtmp)[4][j]  - (*MZA)[4][i+1][j]  - (*MA)[4][j]  + (*Mtmp)[4]
										+ (*MZAtmp)[5][j]  - (*MZA)[5][i+1][j]  + (*MA)[5][j]  - (*Mtmp)[5]
										- (*MZAtmp)[6][j]  - (*MZA)[6][i+1][j]  - (*MA)[6][j]  - (*Mtmp)[6]
										- (*MZAtmp)[7][j]  - (*MZA)[7][i+1][j]  + (*MA)[7][j]  + (*Mtmp)[7]
										- (*MZAtmp)[8][j]  - (*MZA)[8][i+1][j]  - (*MA)[8][j]  - (*Mtmp)[8]
										+ (*MZAtmp)[9][j]  + (*MZA)[9][i+1][j]  + (*MA)[9][j]  + (*Mtmp)[9]
										+ (*MZAtmp)[10][j] + (*MZA)[10][i+1][j] - (*MA)[10][j] - (*Mtmp)[10]
										+ (*MZAtmp)[11][j] + (*MZA)[11][i+1][j] + (*MA)[11][j] + (*Mtmp)[11]
										- (*MZAtmp)[12][j] + (*MZA)[12][i+1][j] - (*MA)[12][j] + (*Mtmp)[12]
										- (*MZAtmp)[13][j] + (*MZA)[13][i+1][j] + (*MA)[13][j] - (*Mtmp)[13]
										- (*MZAtmp)[14][j] + (*MZA)[14][i+1][j] - (*MA)[14][j] + (*Mtmp)[14]
										- (*MZAtmp)[15][j] - (*MZA)[15][i+1][j] - (*MA)[15][j] - (*Mtmp)[15]
										- (*MZAtmp)[16][j] - (*MZA)[16][i+1][j] + (*MA)[16][j] + (*Mtmp)[16]
										- (*MZAtmp)[17][j] - (*MZA)[17][i+1][j] - (*MA)[17][j] - (*Mtmp)[17]) / 512; ///Caso 7
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
				c++;
				//std::cout<<"Renglon_"<<r<<"_Columna_"<<c<<std::endl;
				for(p = 0;p <= 17;p++)
				{
					///Guardar MA con los valores de Mtmp
					(*MA)[p][j] = (*Mtmp)[p];
					///Guardar MZAtmp con los valores de MZA
					(*MZAtmp)[p][j] = (*MZA)[p][i+1][j];//??????????????????????????????????????????????????????????????????????????
					///Guardar MZA con los valores de MA
					(*MZA)[p][i+1][j] = (*MA)[p][j];//??????????????????????????????????????????????????????????????????????????
				}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*	if(j != nColumn)
					fillMSZero(Mtmp,i,i,j,j+1,k,k,l);
				else
					fillMSZero(Mtmp,i,i+1,j,0,k,k,l);*/
				if(j != nColumn+1)////////////////////////////
					fillMtmpLikeMS(Mtmp,i+1,i+1,j,j+1,k,k,l);
			    else
					if(i != (nRow+1))
						fillMtmpLikeMS(Mtmp,i+1,i+2,j,0,k,k,l);
					else
						if(k != (nSlice+1))
							fillMtmpLikeMS(Mtmp,i+1,i+1,j,j+1,k+1,k+1,l);
						else
							fillMtmpLast(Mtmp,i+1,j,k,l);

				//std::cout<<"FillMS con "<<i<<"  "<<j<<"   "<<k<<std::endl;
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
				///Diferencias entre columnas de los dos cortes, en renglón
				///superior e inferior(filtros verdes, anaranjados, cyan, gris, 
				///lila, rosa, azul claro, azul fuerte)
				(*image)[r][c][s] =  ((*MZStmp)[0][j]  + (*MZS)[0][i+1][j]  + (*MS)[0][j]  + (*Mtmp)[0] 
									+ (*MZStmp)[1][j]  + (*MZS)[1][i+1][j]  - (*MS)[1][j]  - (*Mtmp)[1]
									+ (*MZStmp)[2][j]  + (*MZS)[2][i+1][j]  + (*MS)[2][j]  + (*Mtmp)[2]
									+ (*MZStmp)[3][j]  + (*MZS)[3][i+1][j]  + (*MS)[3][j]  + (*Mtmp)[3]
									+ (*MZStmp)[4][j]  + (*MZS)[4][i+1][j]  - (*MS)[4][j]  - (*Mtmp)[4]
									+ (*MZStmp)[5][j]  + (*MZS)[5][i+1][j]  + (*MS)[5][j]  + (*Mtmp)[5]
									+ (*MZStmp)[6][j]  - (*MZS)[6][i+1][j]  + (*MS)[6][j]  - (*Mtmp)[6]
									+ (*MZStmp)[7][j]  - (*MZS)[7][i+1][j]  - (*MS)[7][j]  + (*Mtmp)[7]
									+ (*MZStmp)[8][j]  - (*MZS)[8][i+1][j]  + (*MS)[8][j]  - (*Mtmp)[8]
									+ (*MZStmp)[9][j]  + (*MZS)[9][i+1][j]  + (*MS)[9][j]  + (*Mtmp)[9]
									+ (*MZStmp)[10][j] + (*MZS)[10][i+1][j] - (*MS)[10][j] - (*Mtmp)[10]
									+ (*MZStmp)[11][j] + (*MZS)[11][i+1][j] + (*MS)[11][j] + (*Mtmp)[11]
									+ (*MZStmp)[12][j] - (*MZS)[12][i+1][j] + (*MS)[12][j] - (*Mtmp)[12] 
									+ (*MZStmp)[13][j] - (*MZS)[13][i+1][j] - (*MS)[13][j] + (*Mtmp)[13]
									+ (*MZStmp)[14][j] - (*MZS)[14][i+1][j] + (*MS)[14][j] - (*Mtmp)[14]
									+ (*MZStmp)[15][j] + (*MZS)[15][i+1][j] + (*MS)[15][j] + (*Mtmp)[15]
									+ (*MZStmp)[16][j] + (*MZS)[16][i+1][j] - (*MS)[16][j] - (*Mtmp)[16] 
									+ (*MZStmp)[17][j] + (*MZS)[17][i+1][j] + (*MS)[17][j] + (*Mtmp)[17]
									+ (*MZStmp)[18][j] - (*MZS)[18][i+1][j] + (*MS)[18][j] - (*Mtmp)[18]
									+ (*MZStmp)[19][j] - (*MZS)[19][i+1][j] - (*MS)[19][j] + (*Mtmp)[19]
									+ (*MZStmp)[20][j] - (*MZS)[20][i+1][j] + (*MS)[20][j] - (*Mtmp)[20]
									+ (*MZStmp)[21][j] + (*MZS)[21][i+1][j] + (*MS)[21][j] + (*Mtmp)[21]
									+ (*MZStmp)[22][j] + (*MZS)[22][i+1][j] - (*MS)[22][j] - (*Mtmp)[22]
									+ (*MZStmp)[23][j] + (*MZS)[23][i+1][j] + (*MS)[23][j] + (*Mtmp)[23] 
									+ (*MZStmp)[24][j] + (*MZS)[24][i+1][j] + (*MS)[24][j] + (*Mtmp)[24] 
									+ (*MZStmp)[25][j] + (*MZS)[25][i+1][j] - (*MS)[25][j] - (*Mtmp)[25]
									+ (*MZStmp)[26][j] + (*MZS)[26][i+1][j] + (*MS)[26][j] + (*Mtmp)[26]) / 512;  ////Caso 8
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
				c++;
				
				for(p = 0;p <= 26;p++)
				{
					///Guardar MS con los valores de Mtmp:
					(*MS)[p][j] = (*Mtmp)[p];
					///Guardar MZStmp con los valores de MZS:
					(*MZStmp)[p][j] = (*MZS)[p][i+1][j];
					///Guardar MZS con los valores de Mtmp:
					(*MZS)[p][i+1][j] = (*MS)[p][j];
				}
			}///Fin de j hasta nColumn
			
			r++;

			if(i != (nRow))
			{
				c=0;
				
				for(j = 0;j <= (nColumn);j++)
				{
					(*image)[r][c][s] =    ((*MAtmp)[0][j]  + (*MA)[0][j]  + (*MAtmp)[1][j]  - (*MA)[1][j] 
											+ (*MAtmp)[2][j]  + (*MA)[2][j]  - (*MAtmp)[6][j]  - (*MA)[6][j] 
											- (*MAtmp)[7][j]  + (*MA)[7][j]  - (*MAtmp)[8][j]  - (*MA)[8][j]
											- (*MAtmp)[9][j]  - (*MA)[9][j]  - (*MAtmp)[10][j] + (*MA)[10][j]
											- (*MAtmp)[11][j] - (*MA)[11][j] + (*MAtmp)[15][j] + (*MA)[15][j]
											+ (*MAtmp)[16][j] - (*MA)[16][j] + (*MAtmp)[17][j] + (*MA)[17][j]) / 256; ///Caso 5
					std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
										
					c++;

					(*image)[r][c][s] =  ((*MStmp)[0][j]  + (*MS)[0][j]  + (*MStmp)[1][j]  - (*MS)[1][j]
										+ (*MStmp)[2][j]  + (*MS)[2][j]  + (*MStmp)[3][j]  + (*MS)[3][j]
										+ (*MStmp)[4][j]  - (*MS)[4][j]  + (*MStmp)[5][j]  + (*MS)[5][j] 
										+ (*MStmp)[9][j]  + (*MS)[9][j]  + (*MStmp)[10][j] - (*MS)[10][j] 
										+ (*MStmp)[11][j] + (*MS)[11][j] - (*MStmp)[15][j] - (*MS)[15][j]
										- (*MStmp)[16][j] + (*MS)[16][j] - (*MStmp)[17][j] - (*MS)[17][j]
										- (*MStmp)[21][j] - (*MS)[21][j] - (*MStmp)[22][j] + (*MS)[22][j] 
										- (*MStmp)[23][j] - (*MS)[23][j] - (*MStmp)[24][j] - (*MS)[24][j]
										- (*MStmp)[25][j] + (*MS)[25][j] - (*MStmp)[26][j] - (*MS)[26][j]) / 256; ///Caso 6
					std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
					c++;
				}
				r++;
			}///Fin de la condicional i diferente de nRow

		
		}///Fin de i hasta renglones


////*---------------------------------------------------------------------------------------*/////////////
		//std::cout<<"%%%%%%%%"<<std::endl;
		s++;

		//std::cout<<"Renglon_"<<r<<"_Columna_"<<c<<"_Slice_"<<s<<std::endl;
		if(k != (nSlice+1))
		{
			//std::cout<<"Renglon_"<<r<<"_Columna_"<<c<<"_Slice_"<<s<<std::endl;
			r=0,c=0; ///Corte par
			for(j = 0;j <= (nColumn);j++)
			{
				//std::cout<<"_Columna j_"<<j<<std::endl;
				(*image)[r][c][s] = ((*MZA)[0][0][j]-(*MZA)[2][0][j] -(*MZA)[6][0][j] +(*MZA)[8][0][j]
									-(*MZA)[9][0][j]+(*MZA)[11][0][j]+(*MZA)[15][0][j]-(*MZA)[17][0][j])/128;  ///Caso 1
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
								
				c++;
				(*image)[r][c][s] =  ((*MZS)[0][0][j]  - (*MZS)[2][0][j]  + (*MZS)[9][0][j]  - (*MZS)[11][0][j] 
									- (*MZS)[15][0][j] + (*MZS)[17][0][j] - (*MZS)[24][0][j] + (*MZS)[26][0][j]
									+ (*MZS)[3][0][j]  - (*MZS)[5][0][j]  - (*MZS)[21][0][j] + (*MZS)[23][0][j])/128; ///Caso 2
				std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
				
				c++;
			}

			r++;

			for(i = 0;i <= (nRow);i++)
			{
				c=0;
				for(j = 0;j <= (nColumn);j++)
				{
					(*image)[r][c][s] =  ((*MZA)[0][i][j]  + (*MZA)[0][i+1][j]  - (*MZA)[2][i][j]  - (*MZA)[2][i+1][j]  + (*MZA)[3][i][j]  - (*MZA)[3][i+1][j]
										- (*MZA)[5][i][j]  + (*MZA)[5][i+1][j]  - (*MZA)[6][i][j]  - (*MZA)[6][i+1][j]  + (*MZA)[8][i][j]  + (*MZA)[8][i+1][j]
										+ (*MZA)[9][i][j]  + (*MZA)[9][i+1][j]  - (*MZA)[11][i][j] - (*MZA)[11][i+1][j] - (*MZA)[12][i][j] + (*MZA)[12][i+1][j]
										+ (*MZA)[14][i][j] - (*MZA)[14][i+1][j] - (*MZA)[15][i][j] - (*MZA)[15][i+1][j] + (*MZA)[17][i][j] + (*MZA)[17][i+1][j])/256; ///Caso 3
					std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
					
					
					c++;
					(*image)[r][c][s] = ((*MZS)[0][i][j]  + (*MZS)[0][i+1][j]  - (*MZS)[2][i][j]  - (*MZS)[2][i+1][j]
										+(*MZS)[3][i][j]  + (*MZS)[3][i+1][j]  - (*MZS)[5][i][j]  - (*MZS)[5][i+1][j]
										+(*MZS)[6][i][j]  - (*MZS)[6][i+1][j]  - (*MZS)[8][i][j]  + (*MZS)[8][i+1][j]
										+(*MZS)[9][i][j]  + (*MZS)[9][i+1][j]  - (*MZS)[11][i][j] - (*MZS)[11][i+1][j]
										+(*MZS)[12][i][j] - (*MZS)[12][i+1][j] - (*MZS)[14][i][j] + (*MZS)[14][i+1][j]
										+(*MZS)[15][i][j] + (*MZS)[15][i+1][j] - (*MZS)[17][i][j] - (*MZS)[17][i+1][j]
										+(*MZS)[18][i][j] - (*MZS)[18][i+1][j] - (*MZS)[20][i][j] + (*MZS)[20][i+1][j]
										+(*MZS)[21][i][j] + (*MZS)[21][i+1][j] - (*MZS)[23][i][j] - (*MZS)[23][i+1][j]
										+(*MZS)[24][i][j] + (*MZS)[24][i+1][j] - (*MZS)[26][i][j] - (*MZS)[26][i+1][j])/256; ////Caso 4
					std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
					
					c++;
				}
				 
				r++;
				 
				//std::cout<<"Renglon_"<<r<<"_Columna_"<<c<<"_Slice_"<<s<<std::endl;
				if(i!=(nRow))
				{
					c=0;
					for(j = 0;j <= (nColumn);j++)
					{
						(*image)[r][c][s] = ((*MZA)[0][i+1][j]-(*MZA)[2][i+1][j] -(*MZA)[6][i+1][j] +(*MZA)[8][i+1][j]
											-(*MZA)[9][i+1][j]+(*MZA)[11][i+1][j]+(*MZA)[15][i+1][j]-(*MZA)[17][i+1][j]) / 128; ////Caso 1
						std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
						c++;
						
						(*image)[r][c][s] = ((*MZS)[0][i+1][j]  - (*MZS)[2][i+1][j]  + (*MZS)[9][i+1][j]  - (*MZS)[11][i+1][j]
											-(*MZS)[15][i+1][j] + (*MZS)[17][i+1][j] - (*MZS)[24][i+1][j] + (*MZS)[26][i+1][j]
											+(*MZS)[3][i+1][j]  - (*MZS)[5][i+1][j]  - (*MZS)[21][i+1][j] + (*MZS)[23][i+1][j]) / 128; ////Caso 2
						std::cout<<"Volumen generado "<<r<<" "<<c<<" "<<s<<" Valor: "<< (*image)[r][c][s]<<std::endl;
											
						c++;
					}
					r++;
				} ////Fin de la condicional i diferente de nRow-1
			} ///Fin del ciclo iterativo para renglones
			s++;
		}///fin de la condicional k diferente de nSlice-1


	//std::cout<<"Sale de la condicional"<<std::endl;
	}//fin del for k hasta nSlice
	std::cout<<"Sale de los cortes renglo: "<<r<<"  columna: "<<c<<" corte: "<<s<<std::endl;
	imageAux = image;
} 
		for(int i = volumeResult->GetExtent()[0]; i <= volumeResult->GetExtent()[1]; i++)
			{
				for(int j = volumeResult->GetExtent()[2]; j <= volumeResult->GetExtent()[3]; j++)
				{
					for(int k = volumeResult->GetExtent()[4]; k <= volumeResult->GetExtent()[5]; k++)
					{
						unsigned short *scalarPointerR = (unsigned short *)volumeResult->GetScalarPointer(i,j,k); 
						//unsigned short *scalarPointerR = (unsigned short *)volumeResult->GetScalarPointer(i,j,k); 
						scalarPointerR[0] =	(unsigned short)(*imageAux)[i][j][k];
					}
				}
			}

		//std::cout<<"Salio del ciclo (n.n) _"<<std::endl;
		volumeResult->Update();
		return volumeResult;

}

void Hermite::PrintCoefMC(int coef)
{
	int dimX = this->GetMatrixC(0)->GetDimensions()[0];
	int dimY = this->GetMatrixC(0)->GetDimensions()[1];
	int dimZ = this->GetMatrixC(0)->GetDimensions()[2];

	//std::cout<<"dimX "<<dimX <<"dimY "<<dimY<< "dimZ "<<dimZ<<std::endl;
	for(int k=0; k<dimZ; k++)
	{
		for(int i=0; i<dimX; i++)
		{
			for(int j=0; j<dimY; j++)
				std::cout<<"["<<i<<"]"<<"["<<j<<"]"<<"["<<k<<"]"<< (*(this->GetMatrixC(0)->GetCoef(coef)))[i][j][k]<<std::endl;
		}
	}
}