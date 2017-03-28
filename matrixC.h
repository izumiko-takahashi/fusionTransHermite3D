#pragma once

#include <iostream>
#include <vector>

#include "vtkImageData.h"
//!	Class MatrixC
/*!
	\brief Description of MatrixC
	La clase matrixC implementa un vector de la STL para almacenar los 27 
	coeficientes de la DHT para cada uno de los niveles de resolución con
	los que se va a trabajar la transformada.

*/
#include "vtkSmartPointer.h"

#include "boost/multi_array.hpp"

class matrixC
{
public:
	typedef boost::multi_array<int, 3> iMatrix3D;	/*!< Definicion de la matriz de 3 dimensiones de enteros*/
	typedef iMatrix3D::index iMatrix3DIndex;		/*!< Definicion de los indices para la matriz */

	typedef boost::multi_array<float, 3> fMatrix3D;	/*!< Definicion de la matriz de 3 dimensiones de floats*/
	typedef fMatrix3D::index fMatrix3DIndex;		/*!< Definicion de los indices para la matriz*/
private:
	std::vector<fMatrix3D*> Coef;	/*!< Vector de matrices 3D para los 27 coeficientes de la transformada*/
	fMatrix3D* mH;					/*!< Matriz para guardar los coeficientes rotados*/
	int dimensions[3];				/*!< Dimensiones de las matrices */


public:
	matrixC(int sizeX, 
			int sizeY, 
			int sizeZ
			);
	//! Constructor de MatrixC
	/*!
		\param sizeX Tamaño en x para construir las matrices
		\param sizeY Tamaño en y para construir las matrices
		\param sizeZ Tamaño en z para construir las matrices
	*/
	~matrixC(void);
	//! Destructor
	
	fMatrix3D* GetCoef(int iCoef);
	//! GetCoef Funcion para obtener la matriz correspondiente al coeficiente dado por iCoef
	/*!
		\param Coeficiente que se quiere obtener
		\return La matriz correspondiente al coeficiente dado por iCoef
	*/
	fMatrix3D* GetMH();
	//! GetMH Funcion para obtener la matriz de coeficientes rotados
	/*!
		\return La matriz de coeficientes rotados
	*/
	void SetCoef(fMatrix3D* coef, 
				 int iCoef
				 );
	//! SetCoef Funcion para igualar el contenido de coef en el vector de matrices en
	/*!   el coef iCoef
		\param coef Matriz que se quiere copiar.
		\param iCoef Indice que se quiere igualar.
	*/
	int* GetDimensions(void);
	//! Funcion para obtener las dimensiones de las matrices
	/*!
		\return Un arreglo de 3 enteros con las dimensiones de las matrices 
		0:dimX, 1:dimY, 2:dimZ
	*/
};