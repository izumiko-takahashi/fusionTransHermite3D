#include "Fusion.h"


Fusion::Fusion(vtkSmartPointer<vtkImageData> imageDataV1, vtkSmartPointer<vtkImageData> imageDataV2, int levels)
{
	Levels = levels;
	hV1 = new Hermite(imageDataV1, Levels);
	hV2 = new Hermite(imageDataV2, Levels);
	
	std::cout<<"fusion constructor ok"<<std::endl;

	hV1->HermiteTransform();
	////hV1->TestHermiteTransform();
	//std::cout<<"Hermite transform v1 ok"<<std::endl;
	//hV2->HermiteTransform();
	//std::cout<<"Hermite transform v2 ok"<<std::endl;

	int dimensions[3];
	imageDataV2->GetDimensions(dimensions);

	int counter = 0;
	
	while(pow(2.0f,counter) < dimensions[0])
		counter++;
	int rows = pow(2.0f,counter);
	counter = 0;
	
	while(pow(2.0f,counter) < dimensions[1])
		counter++;

	int columns = pow(2.0f,counter);
	counter = 0;

	while(pow(2.0f,counter) < dimensions[2])
		counter++;

	int slides = pow(2.0f,counter);

	//hVF = new Hermite(rows,columns,slides,Levels);


	//hV1->GetImageData(0);
	//hV2->GetImageData(0);

}

vtkSmartPointer<vtkImageData> Fusion::GetImageDataV1(int coefIndex)
{
	return hV1->GetImageData(coefIndex);
	//return hV1->GenerateImageDataFromMC(coefIndex, 0);
}

vtkSmartPointer<vtkImageData> Fusion::GetImageDataV2(int coefIndex)
{
	return hV2->GetImageData(coefIndex);
}
Fusion::~Fusion(void)
{
}
void Fusion::MeanCBF(int nRow, int nColumn, int nSlice)
{
	for(int rCounter = 0; rCounter< nRow; rCounter++)
	{
		for(int cCounter = 0; cCounter< nColumn; cCounter++)
		{
			for(int sCounter = 0; sCounter< nSlice; sCounter++)
			{
				(*hVF->GetMatrixC(Levels-1)->GetCoef(0))[rCounter][cCounter][sCounter] = 
					(*hV1->GetMatrixC(Levels-1)->GetCoef(0))[rCounter][cCounter][sCounter]
					+ (*hV2->GetMatrixC(Levels-1)->GetCoef(0))[rCounter][cCounter][sCounter];
			}
		}
	}
}


Fusion::fMatrix3D* Fusion::FusionCAF(int level, int dim0, int dim1, int dim2)
{
	fMatrix3D* mapa = new fMatrix3D(boost::extents[dim0][dim1][dim2]);

	//***********************************
	for(int k=0; k<dim2;k++)
	{
		for(int i=0; i<dim0;i++)
		{
			for(int j=0; j<dim1;j++)
			{
				if((*hV1->GetMatrixC(level)->GetMH())[i][j][k] > (*hV2->GetMatrixC(level)->GetMH())[i][j][k])
					(*mapa)[i][j][k] = 1;
				else
					(*mapa)[i][j][k] = 0;
			}
		}
	}
	//************************************

	return mapa;
}

void Fusion::ChooseMax()
{
	for(int l=0; l<Levels; l++)
	{
		int inicio = 0;
		if(l == 0)
			inicio = 1;

		int* dimensions = hV1->GetMatrixC(l)->GetDimensions();
		fMatrix3D* mapa = FusionCAF(l,dimensions[0],dimensions[1],dimensions[2]);
		
		
		for(int coef=inicio; coef<27; coef++)
		{
			for(int k=0; k< dimensions[2]; k++)
			{
				for(int i=0; i< dimensions[0]; i++)
				{
					for(int j=0; j< dimensions[1]; j++)
					{
						float aux1V1 = (*hV1->GetMatrixC(l)->GetCoef(coef))[i][j][k];
						float aux2V1 = (*mapa)[i][j][k];

						float aux1V2 = (*hV1->GetMatrixC(l)->GetCoef(coef))[i][j][k];

						(*hVF->GetMatrixC(l)->GetCoef(coef))[i][j][k] = aux1V1 * aux2V1 +  aux1V2 * (1 - aux2V1);
					}
				}
			}
		}

	}

}
vtkSmartPointer<vtkImageData> Fusion::Fusionate(int option)
{
	//int* dimensions = hV1->GetMatrixC(Levels-1)->GetDimensions();
	switch(option)
	{
	case 0:
		/*std::cout<<"Entra al case"<<std::endl;
		MeanCBF(dimensions[0],dimensions[1],dimensions[2]);
		std::cout<<"Hizo promedio"<<std::endl;
		ChooseMax();
		std::cout<<"Eligio max"<<std::endl;*/
		//hV1->PrintCoefMC(0);
		return(hV1->HermiteInverseTransform());
		break;
	case 1:
		return(GenerateImageFusionbyMean());
		break;
	case 2:
		//hV1->PrintCoefMC(0);
		return(hV1->GetOriginalData());
	}
}

vtkSmartPointer<vtkImageData> Fusion::GenerateImageFusionbyMean()
{
	std::cout<<"entro"<<std::endl;
	vtkSmartPointer<vtkImageData> FusionImageData = vtkSmartPointer<vtkImageData>::New();
	FusionImageData->SetExtent(hV1->GetOriginalData()->GetExtent());
	FusionImageData->SetSpacing(hV1->GetOriginalData()->GetSpacing());
	FusionImageData->SetOrigin(hV1->GetOriginalData()->GetOrigin());
	FusionImageData->SetScalarTypeToUnsignedChar();
	
	for(int k = FusionImageData->GetExtent()[4]; k <= FusionImageData->GetExtent()[5]; k++)
	{
		for(int i = FusionImageData->GetExtent()[0]; i <= FusionImageData->GetExtent()[1]; i++)
		{
			for(int j = FusionImageData->GetExtent()[2]; j <= FusionImageData->GetExtent()[3]; j++)
			{
				unsigned char *scalarPointer1 = (unsigned char *)hV1->GetOriginalData()->GetScalarPointer(i,j,k); 
				unsigned char *scalarPointer2 = (unsigned char *)hV2->GetOriginalData()->GetScalarPointer(i,j,k); 
				unsigned char *scalarPointerF = (unsigned char *)FusionImageData->GetScalarPointer(i,j,k); 

				unsigned char value = (scalarPointer1[0] + scalarPointer2[0])/2;
				scalarPointerF[0] = value;
				
			}
		}
	}

	FusionImageData->Update();
	return FusionImageData;
}
