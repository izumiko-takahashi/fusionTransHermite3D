#pragma once

#include "Hermite.h"
#include <iostream>

//clase para fusion de volumenes
class Fusion
{
	typedef boost::multi_array<float, 3> fMatrix3D;//definicion de la matriz de 3 dimensiones de floats
	typedef fMatrix3D::index fMatrix3DIndex;//definicion de los indices para la matriz

	Hermite *hV1;//instancia de la transformada de hermite para el volumen 1
	Hermite *hV2;//instancia de la transformada de hermite para el volumen 2
	Hermite *hVF;//instancia de la transformada de hermite en la que se guardara el resultado de la fusion de V1 y V2
	int Levels;//niveles de submuestreo

	vtkSmartPointer<vtkImageData> ImageDataV1;//matriz donde estan los voxels del V1. Es usada para la visualizacion de V1 con VTK
	vtkSmartPointer<vtkImageData> ImageDataV2;//matriz donde estan los voxels del V2. Es usada para la visualizacion de V2 con VTK
	vtkSmartPointer<vtkImageData> FusionImageData;//matriz para la visualizacion con VTK del resultado de la fusion de V1 y V2 

public:
	//constructor para Fusion
	Fusion(vtkSmartPointer<vtkImageData> imageDataV1,//matriz 3D construida a partir de lectura de datos del V1
			vtkSmartPointer<vtkImageData> imageDataV2,//matriz 3D construida a partir de lectura de datos del V2
			 int levels//niveles de multiresolucion (submuestreo)
			 );

	//Funcion para construir el vtkImageData del coeficiente representado por coefIndex del V1
	vtkSmartPointer<vtkImageData> GetImageDataV1(int coefIndex//indice del coeficiente que se quiere visualizar
		);
	//regresa la matriz para la visualizacion de la transformada hermite del V1 con el coeficiente indicado por coefIndex

	//Funcion para construir el vtkImageData del coeficiente representado por coefIndex del V1
	vtkSmartPointer<vtkImageData> GetImageDataV2(int coefIndex//indice del coeficiente que se quiere visualizar
		);
	//regresa la matriz para la visualizacion de la transformada hermite del V1 con el coeficiente indicado por coefIndex

	//Realizar fusion con el metodo indicado por option
	vtkSmartPointer<vtkImageData> Fusionate(int option//0->seleccion del maximo
		);
	//regresa la matriz para la visualizacion del resultado en VTK

	//destructor
	~Fusion(void);

	//Funcion para promediar el coeficiente 000 de los dos volumenes en la coordenada nRowm nColumn, nSlice
	void MeanCBF(int nRow,//fila
					int nColumn, //columna
					int nSlice//corte
					);
	//regresa: void

	//Funcion para seleccionar los coeficientes de la fusion a partir de un mapa de seleccion y las matrices MH de V1 y V2
	void ChooseMax();
	//regresa: void

	//Funcion que implementa la fusion y construye la matriz resultado
	fMatrix3D* FusionCAF(int level, int dim0, int dim1, int dim2);
	//regresa: matriz 3d de floats que representa la fusion de los coeficientes de alta frecuencia de los volumenes

	vtkSmartPointer<vtkImageData> GenerateImageFusionbyMean();
};

