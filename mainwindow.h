//! Clase Mainwindow.
/*!
	\class Mainwindow mainwindow.h
	\file mainwindow.h
	\brief Descripción de Mainwindow.

	Detalles.

	La clase Mainwindow es una clase derivada de QMainWindow la cual contiene la interfaz principal del proyecto de visualización
	conteniendo en ella barra de herramientas, pantalla de visualización, docks.
	También se encarga de conjuntan los elementos de la interfaz usando Qt y las funciones de visualización de la librería VTK.
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
	Construye una ventana principal dado el QWidget parent y las flags específicas. Esta Mainwindow configura a Qt::Window y
	siempre se creará como un top-level widget (el widget independiente del manejador de widgets). 
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
		Crea una instancia de ProjectWizard, la muestra cuando se presiona la opción "Cargar datos" del menú "Proyecto".
		Conecta la señal fileReady (de ProjectWizard) con la función slotFileReady (de Mainwindow).
		\sa slotFileReady(const QString &file) and ProjectWizard().
	*/
	void slotDataLoad();
	//! slotAbout Muestra los créditos del proyecto.
	/*!
		Muestra una ventana con los créditos del proyecto cuando se presiona la opción "Acerca de" del menú "Ayuda".
		\sa setActions()
	*/
	void slotAbout();
	//! slotFileReady Parsea el archivo que contiene los datos de las imágenes a visualizar.
	/*!
		Obtiene el archivo .txt (file es obtenido por referencia) que contiene los parámetros de las imágenes para formar los volúmenes, 
		todo a través de un parser sencillo que de acuerdo al tipo de imagen manda a llamar a la función LoadVolume.
		\param file Es la referencia al archivo que obtiene de ProjectWizard que contiene los parámetros necesarios para crear los volúmenes
					a partir de un conjunto de imágenes dicom, raw o bmp.
	*/
	void slotFileReady(const QString &file);
	//! slotLoadProject Abre una ventana de diálogo para buscar un proyecto existente.
	/*!
		Obtiene el archivo .txt usando un QFileDialog para elegir un archivo .txt ya existente que contiene los parámetros para formar los volúmenes.
		Una vez obtenido el archivo, llama a la función slotDataLoad para leer el contenido y realizar la carga con LoadVolume.
		\sa slotDataLoad()
	*/
	void slotLoadProject();
	//! setSliceCube Conmuta la rotación de los volúmenes ya cargados en pantalla o mostrar cubo de cortes.
	/*!
		Conmuta las acciones activeRotate y activeCube. Si está activa la opción activeRotate deshabilita el vtkBoxWidget y permite la rotación de los
		modelos. Si está activa la opción activeCube habilita el vtkBoxWidget y se encarga de realizar cortes en los planos, específicar regiones o establecer 
		segmentos.
	*/
	void setSliceCube(bool checked);
	//! slotFusion Realiza la fusión de datos mediante la transformada Hermite
	/*!
		Esta función establece las funciones Fusion a partir de Hermite
		\sa Fusion(vtkSmartPointer<vtkImageData> imageDataV1, vtkSmartPointer<vtkImageData> imageDataV2) and Hermite(vtkSmartPointer<vtkImageData> originalData, int levels)
	*/
	void slotFusion();
	//! slotSetGrayInterval Define los rangos de valores de gris para la visualización
	/*!
		Obtiene los valores de range y mean de dockWinRangeSelector().
		\param opacityMean	Es un int que contiene el valor del nivel de gris medio que el usuario quiere visualizar en el volumen
		\param opacityRange	Es un int que contiene el tamaño entre dos intervalos, los cuales establecen el rango de niveles de gris a visualizar en el volumen.
	*/
	void slotSetGrayInterval(int opacityMean, int opacityRange);
	//! slotSetRGBSegment Lee los segmentos de color para la visualización de los volúmenes
	/*!
		Obtiene un std::vector de ColorSegment a partir de la ventana creada por la clase RGBSegment.
		Aquí puede establecerse la función - vtkSmartPointer<vtkVolumeProperty> CreateProperty() - 
		\param colors Es un vector de ColorSegment's que contiene los datos para crear los distintos bloques de color en la visualización del volumen.
	*/
	void slotSetRGBSegment(std::vector<ColorSegment> *colors);
	//! slotChangeBackground  Cambia el color de fondo del espacio de visualización de los volúmenes.
	/*!
		Manda a llamar un QColorDialog, en esta ventana se mostrará una paleta de colores que el usuario elegirá para determinar el color de fondo.
	*/
	void slotChangeBackground();
	//! slotShowRGBSegment Crea una instancia de RGBSegment
	/*!
		Crea una instancia de RGBSegment, la muestra en pantalla independiente de la ventana principal Mainwindow y establece la conexión entre
		la señal segment de la clase RGBSegment al slot slotSetRGBSegment de la clase Mainwindow.
	*/
	void slotShowRGBSegment();
	//! slotLoadCoefDHT Conmuta las opciones para ver los distintos coeficientes de la Transformada Hermite.
	/*!
		A partir de la variable option esta función muestra el coeficiente elegido DHT. El valor lo recibe cuando se emite la señal
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
		\param coef Es un const QString que elige la opción de un conjunto de QRadioButton.
		\sa dockCoefSelector()
	*/
	void slotLoadCoefDHT(const QString coef);
	//! LoadVolume Toma dos argumentos, carga un conjunto de imágenes tipo DICOM.
	/*!
	\param name	es un string que contiene la dirección del conjunto de imágenes.
	\param op	es un entero que me indica si se carga el volumen A(0) o el volumen B(1).
	\sa	LoadVolume(std::string name, float spaceX, float spaceY, float spaceZ,int imaX,int imaY,int first, int last,int op),
		LoadVolume(std::string dir, std::string file,std::string pfx,std::string ptr,int xBegin, int xEnd, int yBegin, int yEnd,int imgB, int imgE,int op)
		and slotFileReady(const QString &file)
	*/
	void LoadVolume(std::string name,int op);
	//! LoadVolume toma nueve argumentos, carga un conjunto de imágenes tipo RAW.
	/*!
	\param name		es un string que contiene el texto de tipo carpeta\\nombreArchivo%d.raw .
	\param spaceX	es un float que representa el tamaño del voxel al momento de crearse el volumen sobre el eje X.
	\param spaceY	es un floar que representa el tamaño del voxel al momento de crearse el volumen sobre el eje Y.
	\param spaceZ	es un floar que representa el tamaño del voxel al momento de crearse el volumen sobre el eje Z.
	\param imaX		es un int que representa el tamaño en pixeles de largo de la imagen.
	\param imaY		es un int que representa el tamaño en pixeles de ancho de la imagen.
	\param first	es un int que representa el número indicado en el nombre de la imagen para comenzar la carga.
	\param last		es un int que representa el número indicado en el nombre de la imagen para terminar la carga.
	\param op		es un int que representa la opción a cargar, volumen A (0) o volumen B(1).
	*/
	void LoadVolume(std::string name, float spaceX, float spaceY, float spaceZ,int imaX,int imaY,int first, int last,int op);
	//! LoadVolume toma once argumentos, carga un conjunto de imágenes tipo BMP.
	/*!
	\param dir		es un string que contiene la dirección del conjunto de imágenes.
	\param file		es un string que contiene la dirección de la primera imagen del conjunto.
	\param pfx		es un string que contiene el texto prefijo que es común en el nombre del conjunto de imágenes.
	\param ptr		es un string que contiene el texto patrón nombreArchivo%d.bmp.
	\param xBegin	es un int que representa el tamaño en pixeles de largo de la imagen empezando en cero.
	\param xEnd		es un int que representa el tamaño en pixeles de largo de la imagen menos un pixel.
	\param yBegin	es un int que representa el tamaño en pixeles de ancho de la imagen empezando en cero.
	\param yEnd		es un int que representa el tamaño en pixeles de ancho de la imagen menos un pixel.
	\param imgB     es un int que indica con que entero comenzará la carga de acuerdo al sufijo indicado en el nombre de la imagen.
	\param imgE		es un int que indica con que entero terminará la carga de acuerdo al sufijo indicado en el nombre de la imagen.
	\param op		es un int que representa la opción a cargar, volumen A(0) o volumen B(1).
	*/
	void LoadVolume(std::string dir, std::string file,std::string pfx,std::string ptr,int xBegin, int xEnd, int yBegin, int yEnd,int imgB, int imgE,int op);

	vtkSmartPointer<vtkVolumeProperty> CreateProperty(int opacityMean, int opacityRange, std::vector<ColorSegment> colorSegments);
	void SetPropertyToActiveVolumes();

private:
	int sizeX;					/*!< sizeX es un int que guarda el tamaño en pixeles del largo de la imagen*/				
	int sizeY;					/*!< sizeY es un int que guarda el tamaño en pixeles del ancho de la imagen*/
	int firstImageIndex;		/*!< firstImageIndex es un int que contiene el número inicial para la carga de RAW*/
	int lastImageIndex;			/*!< lastImageIndex es un int que contiene el número final para la carga de RAW*/
	float dataSpacingX;			/*!< dataSpacingX es un float que indica el tamaño del voxel en la dirección X*/
	float dataSpacingY;			/*!< dataSpacingY es un float que indica el tamaño del voxel en la dirección Y*/
	float dataSpacingZ;			/*!< dataSpacingZ es un float que indica el tamaño del voxel en la dirección Z*/
	std::string filePattern;	/*!< filePattern es un string que guarda el patrón para la carga de imágenes RAW */
	std::string directory;		/*!< directory es un string que guarda la dirección absoluta de la carpeta donde se ubican las imágenes*/
	std::string bmpfile;		/*!< bmpfile es un string que guarda la dirección absoluta de la primera imagen BMP a carga */
	std::string prefix;			/*!< prefix es un string que guarda el prefijo que se repite en los nombres de las imágenes de bmp*/
	std::string dir;			/*!< dir es un string que guarda la dirección absoluta de la carpeta donde se ubican las imágenes bmp*/
	std::string pattern;		/*!< pattern es un string que guarda el patrón en el nombre de las imágenes bmp */
	QMenu *menu;				/*!< menu es la barra de menú principal "Proyecto"  */
	QMenu *view;				/*!< view es la barra de menú "Ver"*/
	QMenu *help;				/*!< help es la barra de menú "Ayuda"*/
	QMenu *visualization;		/*!< visualization es la barra de menú "Visualización"*/
	QAction *acFuse;			/*!< acFuse es una acción ubicada en "Proyecto" y llama a slotFusion()*/
	QAction *acAbout;			/*!< acAbout es una acción ubicada en "Ayuda" y muestra los créditos*/
	QAction *acDataLoad;		/*!< acDataLoad es una acción ubicada en "Proyecto" y llama a slotDataLoad() */
	QAction *acLoadProject;		/*!< acLoadProject es una acción ubicada en "Proyecto" y llama a slotLoadProject()*/
	QAction *acColorSegment;	/*!< acColorSegment es una acción ubicada en "Visualización" y llama a slotShowRGBSegment()*/
	QDockWidget *dock;			/*!< dock es un QDockWidget que se usa para la ventana del Selector de rango y Selector de coeficientes*/
	ProjectWizard *lw;			/*!< lw es un apuntador a un objeto de tipo ProjectWizard*/
	RangeSelector *dwRangeS;	/*!< dwRangeS es un apuntador a un objeto de tipo RangeSelector*/
	SelectorCoefDHT *dhtCoef;	/*!< dhtCoef es un apuntador a un objeto de tipo SelectorCoefDHT*/
	RGBSegment *rgbS;			/*!< rgbS es un apuntador a un objeto de tipo RGBSegment*/
	int OpacityMean;
	int OpacityRange;
	std::vector<ColorSegment> Colors;
	
	//! setupMenuBar Configura la barra de menú de la ventana principal 
	/*!
		Define a los QMenu utilizados en Mainwindow (ventana principal top-level widget). También agrega las acciones que estarán asociadas a esos
		menús. 
		Conecta la señal triggered() de la acción "Salir" al slot close() de la clase Mainwindow.
		Conecta la señal triggered() de la acción "Sobre Qt" al slot aboutQt() de la macro qApp de la clase QApplication.
		\sa setActions()
	*/
	void setupMenuBar();
	//! setActions Configura las acciones de la barra de menú
	/*!
		Define a los QAction utilizados en Mainwindow
		\sa setupMenuBar()
	*/
	void setActions();
	//! dockWinRangeSelector  Configura la ventana para la selección de rango y valor medio.
	/*!
		Define dock para agregar una instancia de la clase RangeSelector, es agregada al menú "Ver" y conecta la señal mean_Range(int,int) de
		la clase RangeSelector al slot slotSetGrayInterval(int,int) de la clase Mainwindow.
		\sa slotSetGrayInterval(int opacityMean, int opacityRange)
	*/
	void dockWinRangeSelector();
	//! dockCoefSelector Configura la ventana que contiene los selectores de rango
	/*!
		Redefine dock para agregar una instancia de la clase selectorCoefDHT, es agregada al menú "Ver" y conecta la señal
		sendOption(int) de la clase selectorCoefDHT al slot slotLoadCoefDHT(int) de la clase Mainwindow.
		\sa slotLoadCoefDHT(int option)
	*/
	void dockCoefSelector();
	//! dockSetBackgroundColor Crea un widget encargado del color de fondo
	/*!
		Define dockB, agrega un botón y un label los cuales indicarán al usuario que color van a cambiar al background de la ventana de visualización,
		lo muestra en pantalla y esta función realiza la conexión de la señal clicked() de pushButtonColor al slot slotChangeBackground() de la clase
		Mainwindow.
		\sa slotChangeBackground()
	*/
	void dockSetBackgroundColor();
	//vtkSmartPointer<vtkRenderWindow>			renderWindow;			/*!< renderWindow es un apuntador inteligente de VTK para la clase vtkRenderWindow */
 	//vtkSmartPointer<vtkRenderWindowInteractor>	renderWindowInteractor; /*!< renderWindowInteractor es un apuntador inteligente de VTK para la clase vtkRenderWindowInteractor*/

	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
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
	//! \note Las señales en Qt sólo se declaran, pero no se definen por el usuario. Al momento de compilar, qmake se encarga de definir la señal.
	void backgroundChanged(QColor color); 
};
/*!
	\endcode
*/
#endif 