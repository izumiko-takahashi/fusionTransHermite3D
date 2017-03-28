#pragma once

#include <iostream>
#include <vector>

#include "vtkImageData.h"
#include "vtkSmartPointer.h"

#include "matrixC.h"
#include "boost/multi_array.hpp"
//La clase Hermite provee los métodos para obtener los valores de los vtkImageData 
//y esos datos procesarlos mediante la Discrete Hermite Transform, la Inverse Discrete 
//Hermite Transform así como las funciones para proyectar coeficientes de 3D a 1D , 
//llenar matrices con filtros y la visualización de esos datos procesados para vtkImageData.
class Hermite
{
	typedef boost::multi_array<int, 3> iMatrix3D;//definicion de la matriz de 3 dimensiones de ints
	typedef iMatrix3D::index iMatrix3DIndex;//definicion de los indices para la matriz

	typedef boost::multi_array<float, 3> fMatrix3D;//definicion de la matriz de 3 dimensiones de floats
	typedef fMatrix3D::index fMatrix3DIndex;//definicion de los indices para la matriz

	typedef boost::multi_array<float, 2> fMatrix2D;//definicion de la matriz de 2 dimensiones de floats
	typedef fMatrix2D::index fMatrix2DIndex;//definicion de los indices para la matriz

	typedef boost::multi_array<float, 1> fVector;//definicion de un arreglo unidimensional de floats
	typedef fVector::index fVectorIndex;//definicion de los indices para la matriz

	std::vector<matrixC*> Matrices;//vector de instancias de matrixC, correspondientes a cada nivel de resolucion de la transformada
	vtkSmartPointer<vtkImageData> OriginalData;//imagen 3d de vtk que tiene el volumen original
	vtkSmartPointer<vtkImageData> volumeResult;//imagen 3d de vtk donde se guarda la antitransformada de hermite (se usara para el volumen fusionado)

	int Levels;//niveles de resolucion

	int extent[6];//extents de vtk de la imagen 3d del volumen original
	double spacing[3];//tamaño en x, y ,z de los voxels de los volumenes
	double origin[3];//origen de los volumenes en el mundo 3d de visualizacion
	int dimensions[3];//dimensiones de los volumenes 

	//visualization
	double MC_vis[18], MR_vis[9][640], MT_vis[36][480][640], L_vis[64];//arreglos auxiliares para la visualizacion de la transformada hermite

public:
	//constructor de hermite para un volumen con un vtkImageData construido de la lectura de datos
	Hermite(vtkSmartPointer<vtkImageData> originalData,//vtkImageData con el volumen original
		int levels//niveles de resolucion 
		);
	//constructor de hermite para el volumen fusionado resultante. se especifican las dimensiones para construir las matrices necesarias
	Hermite(int row,//numero de filas
				int column, //numero de columnas
				int slice, //numero de cortes
				int levels//niveles de resolucion
				);
	//destructor
	~Hermite(void);
	//Funcion que lleva a cabo la transformacion de hermite del volumen
	vtkSmartPointer<vtkImageData> HermiteTransform(void);
	//regresa: vtkImageData con los datos originales del volumen

	//funcion para construir matrices sin hacer la transformada (solo para probar visualizacion)
	vtkSmartPointer<vtkImageData> TestHermiteTransform(void);
	//regresa vtkImageData con los datos originales del volumen

	//
	void Proy3Dto1D(matrixC* mC);

	//funcion para antitransformar el volumen
	vtkSmartPointer<vtkImageData> HermiteInverseTransform(void);

	//funcion auxiliar para visualizar el proceso de antitransformacion en el nivel dado por level y el coeficiente dado por coef
	vtkSmartPointer<vtkImageData> GetResultData(int level,//nivel donde esta el coeficiente que se quiere visualizar
												int coef//indice del coeficiente que se quiere visualizar
												);
	//Funcion para llenar  la matriz M a partir de los valores de 
	//la matriz de coeficientes “Matrices” del nivel de resolución “m_level”, y en la posición “m_row”,”m_column” 
	//y “m_slice”  en proceso en sus 18 elementos y multiplicados por un factor de normalización.
	fMatrix2D* fillMA(fMatrix2D* M,//matriz a llenar
						int m_row,//fila
						int m_column,//columna
						int m_slice, //corte
						int m_level//nivel
						);
	//regresa: matriz M llena con sus valores correspondientes

	//Esta función devuelve un apuntador a una matriz boost de dos dimensiones con sus 18 elementos con cero y dependiendo de 
	//los valores que reciba de renglón, columna, corte y nivel de resolución en proceso.
	fVector* fillMtmpLikeMA(fVector* M,
							int m_row,//matriz a llenar
							int m_column,
							int m_slice,
							int m_level//columna
							);
	//regresa: matriz M llena con sus valores correspondientes
	
	//Esta función  devuelve un apuntador a una matriz boost de 2 dimensiones. Se llena a partir de los valores de la matriz .
	//de coeficientes “Matrices” del nivel de resolución “m_level”, y en la posición “m_row”,”m_column” y “m_slice” en sus 
	//27 elementos y multiplicados por un factor de normalización. 
	fMatrix2D* fillMS(fMatrix2D* M,//matriz a llenar
							int m_row,//fila
							int m_row2,
							int m_column,//columna
							int m_column2, //el otro valor
							int m_slice,// corte
							int m_slice2,
							int m_level//nivel
							);
	//regresa: matriz M llena con sus valores correspondientes

	//Esta función devuelve un apuntador a una matriz boost de 2 dimensiones. Se llena a partir de los valores de la matriz 
	//de coeficientes “Matrices” del nivel de resolución “m_level”, y en la posición “m_row”,”m_column” y “m_slice” en sus 
	//27 elementos y multiplicados por un factor de normalización. Es una redefinición de la función fillMS ya que no considera 
	//la suma o resta del siguiente elemento (m_column + 1)

	fVector* fillMtmpZeroMS(fVector* M,int m_column);//nivel

	//funcion para llenar a la matriz M con ceros
	fVector* fillMtmpLikeMS(fVector* M,//matriz
							int m_row,//fila
							int m_row2,
							int m_column,//columna
							int m_column2, //el otro valor
							int m_slice,// corte
							int m_slice2,
							int m_level//nivel
							);
	//regresa: matriz M llena con sus valores correspondientes
	fVector* fillMtmpLast(fVector* M,//matriz a llenar
							int m_row,//fila
							int m_column,//columna
							int m_slice, //corte
							int m_level);//nivel
	fMatrix2D* fillLastMS(fMatrix2D* M,//matriz a llenar
							int m_row,//fila
							int m_column,//columna
							int m_slice, //corte
							int m_level);//nivel

	//funcion que implementa la transformada hermite sin multiresolucion con fines solo de visualizacion
	unsigned short trHKernel(unsigned short value,
								int i,//coordenada en x (filas)
								int j,//coordenada en y (columnas)
								int k,//coordenada en z (cortes)
								int coef//coeficiente
								);
	//regresa el valor de gris convertido en la coordenada i, j, k, del coeficiente coef

	//funcion para obtener el vtkImageData correspondiente de la transformada hermite en el coeficiente coef (solo para visualizacion)
	vtkSmartPointer<vtkImageData> GetImageData(int coef//coeficiente
		);
	//regresa:vtkImageData de la transformada hermite sin multi resolucion  en el coeficiente coef

	vtkSmartPointer<vtkImageData> GenerateImageDataFromMC(int coef,//coeficiente
															int level//nivel
		);
	//regresa:vtkImageData del coeficiente dado por coef en MatrizC

	//funcion para obtener el vtkImageData del volumen original
	vtkSmartPointer<vtkImageData> GetOriginalData(void);
	//regresa: vtkImageData del volumen original

	//funcion para obtener la informacion del nivel dado por level
	matrixC* GetMatrixC(int level//nivel
		);
	//regresa: instancia de matrixC correspondiente al nivel level

	void PrintCoefMC(int coef);
	
};
