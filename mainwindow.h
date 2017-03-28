//! Clase Mainwindow.
/*!
	\class Mainwindow mainwindow.h
	\file mainwindow.h
	\brief Descripci�n de Mainwindow.

	Detalles.

	La clase Mainwindow es una clase derivada de QMainWindow la cual contiene la interfaz principal del proyecto de visualizaci�n
	conteniendo en ella barra de herramientas, pantalla de visualizaci�n, docks.
	Tambi�n se encarga de conjuntan los elementos de la interfaz usando Qt y las funciones de visualizaci�n de la librer�a VTK.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QtGui>
#include "projectwizard.h"
#include "RangeSelector.h"
#include <QMainWindow>
#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDockWidget>
#include <string>
#include "ui_mainwindow.h"
#include "selectorCoefDHT.h"
#include "RGBSegment.h"
#include <iostream>
#include "ColorSegment.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkCollectionIterator.h>
#include <vtkImageData.h>
#include <vtkSmartVolumeMapper.h>

//lectura de datos
#include <vtkDICOMImageReader.h>
#include <vtkImageReader2Factory.h>
#include <vtkVolume16Reader.h>

#include "vtkBoxWidgetCallback.h"

#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkProperty.h>
#include <vtkTransform.h>

#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>


//algoritmos
#include "Fusion.h"

class ProjectWizard;
class RangeSelector;
class selectorCoefDHT;
class RGBSegment;
/*!
	\code{.cpp}
*/
class Mainwindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
	
	QLabel *label;
public:
	//! Constructor de la clase Mainwindow
	/*!
	Construye una ventana principal dado el QWidget parent y las flags espec�ficas. Esta Mainwindow configura a Qt::Window y
	siempre se crear� como un top-level widget (el widget independiente del manejador de widgets). 
	*/
	Mainwindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	//! Destructor de la clase Mainwindow
	/*!
	Destruye el Mainwindow
	*/
	~Mainwindow();
	
public slots:
	//! slotDataLoad Crea una instancia de ProjectWizard
	/*!
		Crea una instancia de ProjectWizard, la muestra cuando se presiona la opci�n "Cargar datos" del men� "Proyecto".
		Conecta la se�al fileReady (de ProjectWizard) con la funci�n slotFileReady (de Mainwindow).
		\sa slotFileReady(const QString &file) and ProjectWizard().
	*/
	void slotDataLoad();
	//! slotAbout Muestra los cr�ditos del proyecto.
	/*!
		Muestra una ventana con los cr�ditos del proyecto cuando se presiona la opci�n "Acerca de" del men� "Ayuda".
		\sa setActions()
	*/
	void slotAbout();
	//! slotFileReady Parsea el archivo que contiene los datos de las im�genes a visualizar.
	/*!
		Obtiene el archivo .txt (file es obtenido por referencia) que contiene los par�metros de las im�genes para formar los vol�menes, 
		todo a trav�s de un parser sencillo que de acuerdo al tipo de imagen manda a llamar a la funci�n LoadVolume.
		\param file Es la referencia al archivo que obtiene de ProjectWizard que contiene los par�metros necesarios para crear los vol�menes
					a partir de un conjunto de im�genes dicom, raw o bmp.
	*/
	void slotFileReady(const QString &file);
	//! slotLoadProject Abre una ventana de di�logo para buscar un proyecto existente.
	/*!
		Obtiene el archivo .txt usando un QFileDialog para elegir un archivo .txt ya existente que contiene los par�metros para formar los vol�menes.
		Una vez obtenido el archivo, llama a la funci�n slotDataLoad para leer el contenido y realizar la carga con LoadVolume.
		\sa slotDataLoad()
	*/
	void slotLoadProject();
	//! setSliceCube Conmuta la rotaci�n de los vol�menes ya cargados en pantalla o mostrar cubo de cortes.
	/*!
		Conmuta las acciones activeRotate y activeCube. Si est� activa la opci�n activeRotate deshabilita el vtkBoxWidget y permite la rotaci�n de los
		modelos. Si est� activa la opci�n activeCube habilita el vtkBoxWidget y se encarga de realizar cortes en los planos, espec�ficar regiones o establecer 
		segmentos.
	*/
	void setSliceCube(bool checked);
	//! slotFusion Realiza la fusi�n de datos mediante la transformada Hermite
	/*!
		Esta funci�n establece las funciones Fusion a partir de Hermite
		\sa Fusion(vtkSmartPointer<vtkImageData> imageDataV1, vtkSmartPointer<vtkImageData> imageDataV2) and Hermite(vtkSmartPointer<vtkImageData> originalData, int levels)
	*/
	void slotFusion();
	//! slotSetGrayInterval Define los rangos de valores de gris para la visualizaci�n
	/*!
		Obtiene los valores de range y mean de dockWinRangeSelector().
		\param opacityMean	Es un int que contiene el valor del nivel de gris medio que el usuario quiere visualizar en el volumen
		\param opacityRange	Es un int que contiene el tama�o entre dos intervalos, los cuales establecen el rango de niveles de gris a visualizar en el volumen.
	*/
	void slotSetGrayInterval(int opacityMean, int opacityRange);
	//! slotSetRGBSegment Lee los segmentos de color para la visualizaci�n de los vol�menes
	/*!
		Obtiene un std::vector de ColorSegment a partir de la ventana creada por la clase RGBSegment.
		Aqu� puede establecerse la funci�n - vtkSmartPointer<vtkVolumeProperty> CreateProperty() - 
		\param colors Es un vector de ColorSegment's que contiene los datos para crear los distintos bloques de color en la visualizaci�n del volumen.
	*/
	void slotSetRGBSegment(std::vector<ColorSegment> *colors);
	//! slotChangeBackground  Cambia el color de fondo del espacio de visualizaci�n de los vol�menes.
	/*!
		Manda a llamar un QColorDialog, en esta ventana se mostrar� una paleta de colores que el usuario elegir� para determinar el color de fondo.
	*/
	void slotChangeBackground();
	//! slotShowRGBSegment Crea una instancia de RGBSegment
	/*!
		Crea una instancia de RGBSegment, la muestra en pantalla independiente de la ventana principal Mainwindow y establece la conexi�n entre
		la se�al segment de la clase RGBSegment al slot slotSetRGBSegment de la clase Mainwindow.
	*/
	void slotShowRGBSegment();
	//! slotLoadCoefDHT Conmuta las opciones para ver los distintos coeficientes de la Transformada Hermite.
	/*!
		A partir de la variable option esta funci�n muestra el coeficiente elegido DHT. El valor lo recibe cuando se emite la se�al
		sendOption de la clase SelectorCoefDHT. Cuando option es:
		1- Coeficiente 000
		2- Coeficiente 010
		3- Coeficiente 100
		4- Coeficiente 001
		5- Gradiente
		6- Coeficiente 110
		7- Coeficiente 101
		8- Coeficiente 011
		9- Coeficiente 200
		10-Coeficiente 020
		11-Coeficiente 002
		12-Regresar al volumen original
		\param coef Es un const QString que elige la opci�n de un conjunto de QRadioButton.
		\sa dockCoefSelector()
	*/
	void slotLoadCoefDHT(const QString coef);
	//! LoadVolume Toma dos argumentos, carga un conjunto de im�genes tipo DICOM.
	/*!
	\param name	es un string que contiene la direcci�n del conjunto de im�genes.
	\param op	es un entero que me indica si se carga el volumen A(0) o el volumen B(1).
	\sa	LoadVolume(std::string name, float spaceX, float spaceY, float spaceZ,int imaX,int imaY,int first, int last,int op),
		LoadVolume(std::string dir, std::string file,std::string pfx,std::string ptr,int xBegin, int xEnd, int yBegin, int yEnd,int imgB, int imgE,int op)
		and slotFileReady(const QString &file)
	*/
	void LoadVolume(std::string name,int op);
	//! LoadVolume toma nueve argumentos, carga un conjunto de im�genes tipo RAW.
	/*!
	\param name		es un string que contiene el texto de tipo carpeta\\nombreArchivo%d.raw .
	\param spaceX	es un float que representa el tama�o del voxel al momento de crearse el volumen sobre el eje X.
	\param spaceY	es un floar que representa el tama�o del voxel al momento de crearse el volumen sobre el eje Y.
	\param spaceZ	es un floar que representa el tama�o del voxel al momento de crearse el volumen sobre el eje Z.
	\param imaX		es un int que representa el tama�o en pixeles de largo de la imagen.
	\param imaY		es un int que representa el tama�o en pixeles de ancho de la imagen.
	\param first	es un int que representa el n�mero indicado en el nombre de la imagen para comenzar la carga.
	\param last		es un int que representa el n�mero indicado en el nombre de la imagen para terminar la carga.
	\param op		es un int que representa la opci�n a cargar, volumen A (0) o volumen B(1).
	*/
	void LoadVolume(std::string name, float spaceX, float spaceY, float spaceZ,int imaX,int imaY,int first, int last,int op);
	//! LoadVolume toma once argumentos, carga un conjunto de im�genes tipo BMP.
	/*!
	\param dir		es un string que contiene la direcci�n del conjunto de im�genes.
	\param file		es un string que contiene la direcci�n de la primera imagen del conjunto.
	\param pfx		es un string que contiene el texto prefijo que es com�n en el nombre del conjunto de im�genes.
	\param ptr		es un string que contiene el texto patr�n nombreArchivo%d.bmp.
	\param xBegin	es un int que representa el tama�o en pixeles de largo de la imagen empezando en cero.
	\param xEnd		es un int que representa el tama�o en pixeles de largo de la imagen menos un pixel.
	\param yBegin	es un int que representa el tama�o en pixeles de ancho de la imagen empezando en cero.
	\param yEnd		es un int que representa el tama�o en pixeles de ancho de la imagen menos un pixel.
	\param imgB     es un int que indica con que entero comenzar� la carga de acuerdo al sufijo indicado en el nombre de la imagen.
	\param imgE		es un int que indica con que entero terminar� la carga de acuerdo al sufijo indicado en el nombre de la imagen.
	\param op		es un int que representa la opci�n a cargar, volumen A(0) o volumen B(1).
	*/
	void LoadVolume(std::string dir, std::string file,std::string pfx,std::string ptr,int xBegin, int xEnd, int yBegin, int yEnd,int imgB, int imgE,int op);

	vtkSmartPointer<vtkVolumeProperty> CreateProperty(int opacityMean, int opacityRange, std::vector<ColorSegment> colorSegments);
	void SetPropertyToActiveVolumes();

private:
	int sizeX;					/*!< sizeX es un int que guarda el tama�o en pixeles del largo de la imagen*/				
	int sizeY;					/*!< sizeY es un int que guarda el tama�o en pixeles del ancho de la imagen*/
	int firstImageIndex;		/*!< firstImageIndex es un int que contiene el n�mero inicial para la carga de RAW*/
	int lastImageIndex;			/*!< lastImageIndex es un int que contiene el n�mero final para la carga de RAW*/
	float dataSpacingX;			/*!< dataSpacingX es un float que indica el tama�o del voxel en la direcci�n X*/
	float dataSpacingY;			/*!< dataSpacingY es un float que indica el tama�o del voxel en la direcci�n Y*/
	float dataSpacingZ;			/*!< dataSpacingZ es un float que indica el tama�o del voxel en la direcci�n Z*/
	std::string filePattern;	/*!< filePattern es un string que guarda el patr�n para la carga de im�genes RAW */
	std::string directory;		/*!< directory es un string que guarda la direcci�n absoluta de la carpeta donde se ubican las im�genes*/
	std::string bmpfile;		/*!< bmpfile es un string que guarda la direcci�n absoluta de la primera imagen BMP a carga */
	std::string prefix;			/*!< prefix es un string que guarda el prefijo que se repite en los nombres de las im�genes de bmp*/
	std::string dir;			/*!< dir es un string que guarda la direcci�n absoluta de la carpeta donde se ubican las im�genes bmp*/
	std::string pattern;		/*!< pattern es un string que guarda el patr�n en el nombre de las im�genes bmp */
	QMenu *menu;				/*!< menu es la barra de men� principal "Proyecto"  */
	QMenu *view;				/*!< view es la barra de men� "Ver"*/
	QMenu *help;				/*!< help es la barra de men� "Ayuda"*/
	QMenu *visualization;		/*!< visualization es la barra de men� "Visualizaci�n"*/
	QAction *acFuse;			/*!< acFuse es una acci�n ubicada en "Proyecto" y llama a slotFusion()*/
	QAction *acAbout;			/*!< acAbout es una acci�n ubicada en "Ayuda" y muestra los cr�ditos*/
	QAction *acDataLoad;		/*!< acDataLoad es una acci�n ubicada en "Proyecto" y llama a slotDataLoad() */
	QAction *acLoadProject;		/*!< acLoadProject es una acci�n ubicada en "Proyecto" y llama a slotLoadProject()*/
	QAction *acColorSegment;	/*!< acColorSegment es una acci�n ubicada en "Visualizaci�n" y llama a slotShowRGBSegment()*/
	QDockWidget *dock;			/*!< dock es un QDockWidget que se usa para la ventana del Selector de rango y Selector de coeficientes*/
	ProjectWizard *lw;			/*!< lw es un apuntador a un objeto de tipo ProjectWizard*/
	RangeSelector *dwRangeS;	/*!< dwRangeS es un apuntador a un objeto de tipo RangeSelector*/
	SelectorCoefDHT *dhtCoef;	/*!< dhtCoef es un apuntador a un objeto de tipo SelectorCoefDHT*/
	RGBSegment *rgbS;			/*!< rgbS es un apuntador a un objeto de tipo RGBSegment*/
	int OpacityMean;
	int OpacityRange;
	std::vector<ColorSegment> Colors;
	
	//! setupMenuBar Configura la barra de men� de la ventana principal 
	/*!
		Define a los QMenu utilizados en Mainwindow (ventana principal top-level widget). Tambi�n agrega las acciones que estar�n asociadas a esos
		men�s. 
		Conecta la se�al triggered() de la acci�n "Salir" al slot close() de la clase Mainwindow.
		Conecta la se�al triggered() de la acci�n "Sobre Qt" al slot aboutQt() de la macro qApp de la clase QApplication.
		\sa setActions()
	*/
	void setupMenuBar();
	//! setActions Configura las acciones de la barra de men�
	/*!
		Define a los QAction utilizados en Mainwindow
		\sa setupMenuBar()
	*/
	void setActions();
	//! dockWinRangeSelector  Configura la ventana para la selecci�n de rango y valor medio.
	/*!
		Define dock para agregar una instancia de la clase RangeSelector, es agregada al men� "Ver" y conecta la se�al mean_Range(int,int) de
		la clase RangeSelector al slot slotSetGrayInterval(int,int) de la clase Mainwindow.
		\sa slotSetGrayInterval(int opacityMean, int opacityRange)
	*/
	void dockWinRangeSelector();
	//! dockCoefSelector Configura la ventana que contiene los selectores de rango
	/*!
		Redefine dock para agregar una instancia de la clase selectorCoefDHT, es agregada al men� "Ver" y conecta la se�al
		sendOption(int) de la clase selectorCoefDHT al slot slotLoadCoefDHT(int) de la clase Mainwindow.
		\sa slotLoadCoefDHT(int option)
	*/
	void dockCoefSelector();
	//! dockSetBackgroundColor Crea un widget encargado del color de fondo
	/*!
		Define dockB, agrega un bot�n y un label los cuales indicar�n al usuario que color van a cambiar al background de la ventana de visualizaci�n,
		lo muestra en pantalla y esta funci�n realiza la conexi�n de la se�al clicked() de pushButtonColor al slot slotChangeBackground() de la clase
		Mainwindow.
		\sa slotChangeBackground()
	*/
	void dockSetBackgroundColor();
	//vtkSmartPointer<vtkRenderWindow>			renderWindow;			/*!< renderWindow es un apuntador inteligente de VTK para la clase vtkRenderWindow */
 	//vtkSmartPointer<vtkRenderWindowInteractor>	renderWindowInteractor; /*!< renderWindowInteractor es un apuntador inteligente de VTK para la clase vtkRenderWindowInteractor*/

	//��������������������������������������������������������������������������������������������������������
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//��������������������������������������������������������������������������������������������������������
	vtkSmartPointer<vtkRenderer>				rendererV1;				/*!< renderer para el volumen 1*/
	vtkSmartPointer<vtkVolumeRayCastMapper>		mapperV1;				/*!< mapper para el volumen 1*/
	vtkSmartPointer<vtkRenderer>				rendererV2;				/*!< renderer para el volumen 2*/
	vtkSmartPointer<vtkVolumeRayCastMapper>		mapperV2;				/*!< mapper para el volumen 2*/
	vtkSmartPointer<vtkRenderer>				rendererF;				/*!< renderer para el volumen fusionado*/
	vtkSmartPointer<vtkVolumeRayCastMapper>		mapperF;				/*!< mapper para el volumen fusionado*/

	vtkSmartPointer<vtkImageData>				imageDatV1;				/*!< imagen 3D con los datos en voxels del volumen 1*/				
	vtkSmartPointer<vtkImageData>				imageDatV2;				/*!< imagen 3D con los datos en voxels del volumen 2*/				
	vtkSmartPointer<vtkImageData>				imageDatF;				/*!< imagen 3D con los datos en voxels del volumen fusionado*/	

	Fusion										*f;					/*!< instancia de Fusion, que implementa la fusion de los dos volumenes*/	

	vtkSmartPointer<vtkVolume>					volume1;
	vtkSmartPointer<vtkVolume>					volume2;
	vtkSmartPointer<vtkVolume>					volumeF;

	vtkBoxWidget								*box;
	bool										cubeActive;
	bool										volume1Active;
	bool										volume2Active;
	bool										volumeFActive;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

signals:
	//! \note Las se�ales en Qt s�lo se declaran, pero no se definen por el usuario. Al momento de compilar, qmake se encarga de definir la se�al.
	void backgroundChanged(QColor color); 
};
/*!
	\endcode
*/
#endif 