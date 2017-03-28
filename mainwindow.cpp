//! Clase Mainwindow
/*! 
	
*/
#include "mainwindow.h"

#define HIGHQUALITY 1
int mode = HIGHQUALITY;

static const char * const message =
    "<p><b>El Visualizador de imágenes 3D </b></p>"
    "<p>Muestra un conjunto de imagenes de formato DICOM o RAW" 
	"de tipo médico, con el propósito de interactuar con ellas.<p>"
	"<p><tt>Formado con librerías VTK. </tt> </p>"
	"<p><tt>Entre ellas los cargadores DICOM y RAW</p><p> Como complemento al "
     "proyecto la interfaz se integró con<i> Qt.</i></p>";
//! \fn Mainwindow::Mainwindow(QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags)
/*!	
	\brief Inicializa la ventana principal, inicializa elementos que integran la ventana y renderer. 
*/

Mainwindow::Mainwindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
	/* !\note El constructor configura las distintas funciones que crean los elementos de la pantalla.
		Posteriormente inicializa el renderer, renderWindow y la camera para hacer 3 puertos de vista y
		una sola pantalla.
	*/
	this->setupUi(this);
	this->setWindowTitle(tr("Fusión 3D"));
	this->setCentralWidget(qVTK1);
	setActions();
	setupMenuBar();
	dockWinRangeSelector();
	dockCoefSelector();
	dockSetBackgroundColor();
	this->statusBar()->showMessage("....");

	cubeActive = false;

	this->volume1Active = false;
	this->volume2Active = false;
	this->volumeFActive = false;
	//! Creación de la propiedades de los futuros volumenes
	/*!
	   OpacityMean es el valor promedio default para la opacidad en los futuros volumenes.
	   OpacityRange es el rango default para la opacidad en los futuros volumenes.
	   c es mi instancia de ColorSegment para la creación de segmentos de color en los futuros volumenes.
	*/
	OpacityMean = 128;
	OpacityRange = 128;
	ColorSegment c = ColorSegment(	0,//minGrayLevel
									255,//maxGrayLevel
									0.0,//rMin
									0.0,//gMin
									0.0,//bMin
									1.0,//rMax
									1.0,//gMax
									1.0);//bMax
	Colors.push_back(c); //Se mete "c" en el vector de Colors
	//std::cout<<"out"<<std::endl;

	//renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
 //	renderWindowInteractor =	vtkSmartPointer<vtkRenderWindowInteractor>::New();		 
 //	renderWindowInteractor->SetRenderWindow(renderWindow);
	//vtkCamera* camera;

	////renderer V1
	//rendererV1 = vtkSmartPointer<vtkRenderer>::New();
	//renderWindow->AddRenderer(rendererV1);
	//camera = rendererV1->GetActiveCamera();
	//rendererV1->SetViewport(0,0.5,0.5,1);
	//rendererV1->SetBackground(0.5,0.5,0.5);
	//rendererV1->ResetCamera();
	//renderWindow->Render();

	////renderer V2
	//rendererV2 = vtkSmartPointer<vtkRenderer>::New();
 //
	//renderWindow->AddRenderer(rendererV2);
	//rendererV2->SetActiveCamera(camera);
	//rendererV2->SetViewport(0.5,0.5,1,1);
	//rendererV2->SetBackground(0.5,0.5,0.5);
	//rendererV2->ResetCamera();
	//renderWindow->Render();

	////renderer V3
	//rendererF = vtkSmartPointer<vtkRenderer>::New();
 //
	//renderWindow->AddRenderer(rendererF);
	//rendererF->SetActiveCamera(camera);
	//rendererF->SetViewport(0.0,0.0,1,0.5);
	//rendererF->SetBackground(0.5,0.5,0.5);
	//rendererF->ResetCamera();
	//renderWindow->Render();

	//

	//qVTK1->SetRenderWindow(renderWindow);

}
Mainwindow::~Mainwindow()
{
	/*!
		Destructor de la función
	*/
}
void Mainwindow::setActions()
{
	/*!
		\note Esta función inicializa las acciones de los menu's. Esta sección es exclusiva de la interfaz
	*/
	acDataLoad = new QAction(tr("Cargar datos..."),this);
	acDataLoad->setShortcut(tr("Ctrl+L"));
	connect(acDataLoad,SIGNAL(triggered()),this,SLOT(slotDataLoad()));
	acLoadProject = new QAction(tr("Cargar proyecto..."),this);
	acLoadProject->setShortcut(tr("Ctrl+S"));
	connect(acLoadProject,SIGNAL(triggered()),this,SLOT(slotLoadProject()));
	acFuse = new QAction(tr("Fusionar"),this);
	connect(acFuse,SIGNAL(triggered()),this,SLOT(slotFusion()));
	
	acColorSegment = new QAction(tr("Definir segmentos y color..."),this);
	connect(acColorSegment,SIGNAL(triggered()),this,SLOT(slotShowRGBSegment()));

	acAbout = new QAction(tr("Acerca de"),this);
	connect(acAbout,SIGNAL(triggered()),this,SLOT(slotAbout()));
}
void Mainwindow::setupMenuBar()
{
	/*!
		\note Esta funcion es exclusiva de la interfaz y se encarga de asignar las acciones en los menu's
	*/
	menu = menuBar()->addMenu(tr("&Proyecto"));
	menu->addAction(acDataLoad);
	menu->addAction(acLoadProject);
	menu->addSeparator();
	menu->addAction(acFuse);
	menu->addAction(tr("&Salir"),this,SLOT(close()));

	view = menuBar()->addMenu(tr("&Ver"));

	visualization = menuBar()->addMenu(tr("Visualización"));
	visualization->addAction(acColorSegment);

	help = menuBar()->addMenu(tr("Ayuda"));
	help->addAction(acAbout);
	help->addAction(tr("Sobre &Qt"),qApp,SLOT(aboutQt()));
}
void Mainwindow::slotDataLoad()
{
	/*!
		Genera una instancia de la clase ProjectWizard y muestra el wizard que cargar los volúmenes.
	*/
	ProjectWizard *lw = new ProjectWizard(this);
	lw->show();
	connect(lw,SIGNAL(fileReady(const QString)),this,SLOT(slotFileReady(const QString)));
}

void Mainwindow::slotFileReady(const QString &file)
{
	/*!
		Aquí se hace el parser para leer un txt que creo el Wizard para obtener los valores para la carga de las imágenes
		Y una vez que identifico que tipo de archivo leyó, manda a llamar a la función LoadVolume con los respectivos parámetros.
	*/
	QFile data(file);
	if (!data.open(QFile::ReadOnly | QFile::Text)) 
	{
         QMessageBox::warning(this, tr("Recent Files"),
                              tr("Cannot read file %1:\n%2.")
							  .arg(data.fileName())
                              .arg(data.errorString()));
		 return;
    }
	QString line;
	QTextStream out(&data);
	while(!out.atEnd())
	{
		line = out.readLine();
		if(line == "dicom")
		{
			for(int i=1;i<3;i++)
			{
				line = out.readLine();
				directory = line.toStdString();
				/*!
					Aquí llamo a la función para cargar el volumen dicom i( 1 o 2)
					los valores de directory e i van a cambiar en cada iteración. 
					\param directory es un StdString declarado globalmente.
					\param i es el volumen a cargar el primero(1) o segundo (2).
				*/
				LoadVolume(directory,i);
			}
			
		}
		else if(line == "raw")
		{
			for(int j=1;j<3;j++)
			{
				line =out.readLine();
				filePattern = line.toStdString();
				line = out.readLine();
				sizeX = line.toInt();
				line = out.readLine();
				sizeY = line.toInt();
				line = out.readLine();
				dataSpacingX = line.toFloat();
				line = out.readLine();
				dataSpacingY = line.toFloat();
				line = out.readLine();
				dataSpacingZ = line.toFloat();
				line =out.readLine();
				firstImageIndex = line.toInt();
				line = out.readLine();
				lastImageIndex = line.toInt();
				/*!
					Aquí se manda a llamar la función para raw y las variables son globales las cuales cambian en cada ciclo.
				*/
				LoadVolume(filePattern,dataSpacingX,dataSpacingY,dataSpacingZ,sizeX - 1,sizeY - 1,firstImageIndex,lastImageIndex,j);
			}
		}
		else if(line=="bmp")
		{
			for(int k=1;k<3;k++)
			{
				line = out.readLine();
				dir = line.toStdString();
				line = out.readLine();
				bmpfile = line.toStdString();
				line = out.readLine();
				prefix = line.toStdString();
				line = out.readLine();
				pattern = line.toStdString();
				line = out.readLine();
				sizeX = line.toInt();
				line = out.readLine();
				sizeY = line.toInt();
				line = out.readLine();
				lastImageIndex = line.toInt();
				/*!
					Aquí se manda a llamar la función para bmp y las variables son globales las cuales cambian en cada ciclo.
				*/
				LoadVolume(dir,bmpfile,prefix,pattern,0,sizeX -1, 0, sizeY - 1,1,lastImageIndex,k);

			}
		}
		break;
	}
	data.close();

	//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
	/*! La instancia de vtk para los renderers
		
	*/
	vtkCamera* camera;

	f = new Fusion(imageDatV1, imageDatV2, 1);

	/////////////////////////////////Propiedad para la iluminacion//////////////////////////
	vtkSmartPointer<vtkVolumeProperty> prop1 = vtkSmartPointer<vtkVolumeProperty>::New();
		prop1->SetAmbient(0.1);
		prop1->SetDiffuse(0.9);
		prop1->SetSpecular(0.4);
		prop1->SetSpecularPower(10.0);
		prop1->SetIndependentComponents(false);
		prop1->SetInterpolationTypeToLinear();
		prop1->ShadeOn();

	///////////////////////////////////////////////////////////////////////////////////////

	//renderer v1
	rendererV1 = vtkSmartPointer<vtkRenderer>::New();
 
	qVTK1->GetRenderWindow()->AddRenderer(rendererV1);
	camera = rendererV1->GetActiveCamera();
	rendererV1->SetViewport(0,0.5,0.5,1);

	volume1 = vtkSmartPointer<vtkVolume>::New();
	mapperV1 = vtkSmartPointer<vtkVolumeRayCastMapper>::New();

	vtkVolumeRayCastCompositeFunction *compositeFunction =  vtkVolumeRayCastCompositeFunction::New();
	//compositeFunction->SetCompositeMethodToClassifyFirst();
	compositeFunction->SetCompositeMethodToInterpolateFirst();

	mapperV1->SetVolumeRayCastFunction(compositeFunction);
	mapperV1->SetInput(f->GetImageDataV1(0));
	//std::cout<<"getImageDataV1OK"<<std::endl;
	volume1->SetMapper(mapperV1);
	//volume1->SetProperty(prop1);	
	mapperV1->SetSampleDistance(0.1);

	rendererV1->AddVolume(volume1);
	rendererV1->SetBackground(0.5,0.5,0.5);
	rendererV1->ResetCamera();
	qVTK1->GetRenderWindow()->Render();
	volume1Active = true;
	//

	//////////////////////Propiedades para el volume 2////////////////////////////
	vtkSmartPointer<vtkVolumeProperty> prop2 = vtkSmartPointer<vtkVolumeProperty>::New();
		prop2->SetAmbient(0.1);
		prop2->SetDiffuse(0.9);
		prop2->SetSpecular(0.4);
		prop2->SetSpecularPower(10.0);
		prop2->SetIndependentComponents(false);
		prop2->SetInterpolationTypeToLinear();
		prop2->ShadeOn();
	////////////////////////////////////////////////////////////////////////////

	//renderer v2
	rendererV2 = vtkSmartPointer<vtkRenderer>::New();
 
	qVTK1->GetRenderWindow()->AddRenderer(rendererV2);
	rendererV2->SetActiveCamera(camera);
	rendererV2->SetViewport(0.5,0.5,1,1);

	volume2 = vtkSmartPointer<vtkVolume>::New();
	mapperV2 = vtkSmartPointer<vtkVolumeRayCastMapper>::New();


	mapperV2->SetVolumeRayCastFunction(compositeFunction);
	mapperV2->SetInput(f->GetImageDataV2(0));
	volume2->SetMapper(mapperV2);
	//volume2->SetProperty(prop2);	
	mapperV2->SetSampleDistance(0.1);

	rendererV2->AddVolume(volume2);
	rendererV2->SetBackground(0.5,0.5,0.5);
	rendererV2->ResetCamera();
	qVTK1->GetRenderWindow()->Render();
	volume2Active = true;

	rendererF = vtkSmartPointer<vtkRenderer>::New();
 
    qVTK1->GetRenderWindow()->AddRenderer(rendererF);
	rendererF->SetViewport(0.0,0.0,1,0.5);
	rendererF->SetBackground(0.5,0.5,0.5);
	
	box = vtkBoxWidget::New();
	box->SetInteractor(qVTK1->GetInteractor());
	box->SetPlaceFactor(1.01);

	vtkSmartPointer<vtkImageData> input = f->GetImageDataV1(0);

	box->SetInput(input);
	box->PlaceWidget();

	box->SetDefaultRenderer(rendererV1);
	box->InsideOutOn();
	box->PlaceWidget();
	
	box->EnabledOff();
	box->GetSelectedFaceProperty()->SetOpacity(0.0);
	box->RotationEnabledOff();
	
	vtkBoxWidgetCallback *callback = vtkBoxWidgetCallback::New();
	box->AddObserver(vtkCommand::InteractionEvent, callback);
	callback->SetVolumeMapper(mapperV1);

	callback = vtkBoxWidgetCallback::New();
	callback->SetVolumeMapper(mapperV2);
	box->AddObserver(vtkCommand::InteractionEvent, callback);
	std::cout<<"slotFileReady OK"<<std::endl;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	
}
void Mainwindow::slotAbout()
{
	/*!
		Método exclusivo de la interfaz. Crea una ventana de dialogo con el mensaje sobre la aplicación.
	*/
	QMessageBox::about(this,
		tr("Acerca de Fusión 3D con DHT"), 
		message);
}
void Mainwindow::setSliceCube(bool checked)
{
		/*!
			Aquí hay que habilitar el vtkBoxWidget y sino existe hay que crearlo (o sino se crea desde slotFileReady()
		*/
	if(this->volume1Active && this->volume2Active)
	{
		if(checked)
		{
			box->EnabledOn();
			cubeActive = true;
		}
		else
		{
			vtkSmartPointer<vtkTransform> identity = vtkSmartPointer<vtkTransform>::New();
			identity->Identity();
			box->SetTransform(identity);
			vtkPlanes *planes = vtkPlanes::New();
			box->GetPlanes(planes);
			mapperV1->SetClippingPlanes(planes);
			mapperV2->SetClippingPlanes(planes);
			if(this->volumeFActive == true)
				mapperF->SetClippingPlanes(planes);
			planes->Delete();
			box->EnabledOff();
			cubeActive = false;
		}
	}
}
void Mainwindow::slotLoadProject()
{
	/*!
		Método exclusivo de la interfaz, abre una ventana y cargar el proyecto seleccionado.
	*/
	QString fileName
         = QFileDialog::getOpenFileName(this, tr("Abrir proyecto"),".","*.txt");
     if (fileName.isEmpty())
         return;
	 this->slotFileReady(fileName);
	 std::cout<<"SlotLoadProject"<<std::endl;
}
void Mainwindow::dockWinRangeSelector()
{
	/*!
		Método exclusivo de la interfaz
	*/
	QDockWidget *dock = new QDockWidget(tr("Selector de rango"),this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	RangeSelector *dwRangeS = new RangeSelector(this);
	dock->setWidget(dwRangeS);
	dock->setHidden(false);
	dock->setEnabled(true);
	dock->adjustSize();
	view->addAction(dock->toggleViewAction());
	connect(dwRangeS,SIGNAL(mean_Range(int,int)),this,SLOT(slotSetGrayInterval(int, int)));
}

void Mainwindow::dockCoefSelector()
{
	/*!
		Método exclusivo de la interfaz
	*/

	QDockWidget *dock = new QDockWidget(tr("Seleccionar"),this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::TopDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea,dock);
	SelectorCoefDHT *dhtCoef = new SelectorCoefDHT(dock);
	dock->setWidget(dhtCoef);
	dock->setHidden(false);
	dock->setEnabled(true);
	dock->adjustSize();
	view->addAction(dock->toggleViewAction());
	connect(dhtCoef,SIGNAL(sendOption(const QString)),this,SLOT(slotLoadCoefDHT(const QString)));
}

void Mainwindow::slotFusion()
{
	/*!
		Aquí se hacen todas las llamadas, instanciaciones, que involucren a la Fusion
	*/
	//std::cout<<"entro fusion"<<std::endl;
	if(!volumeFActive)
	{
		//std::cout<<"if"<<std::endl;
		
		vtkCamera* camera = rendererV1->GetActiveCamera();
		vtkSmartPointer<vtkVolumeProperty> prop = vtkSmartPointer<vtkVolumeProperty>::New();
		prop->SetAmbient(0.1);
		prop->SetDiffuse(0.9);
		prop->SetSpecular(0.4);
		prop->SetSpecularPower(10.0);
		prop->SetIndependentComponents(false);
		prop->SetInterpolationTypeToLinear();
		prop->ShadeOn();

		rendererF = vtkSmartPointer<vtkRenderer>::New();
 
		qVTK1->GetRenderWindow()->AddRenderer(rendererF);
		rendererF->SetActiveCamera(camera);
		rendererF->SetViewport(0.0,0.0,1,0.5);

		volumeF = vtkSmartPointer<vtkVolume>::New();
		mapperF = vtkSmartPointer<vtkVolumeRayCastMapper>::New();

		vtkVolumeRayCastCompositeFunction *compositeFunction =  vtkVolumeRayCastCompositeFunction::New();
		//compositeFunction->SetCompositeMethodToClassifyFirst();
		compositeFunction->SetCompositeMethodToInterpolateFirst();

		mapperF->SetVolumeRayCastFunction(compositeFunction);
		mapperF->SetInput(f->Fusionate(0));
		
		volumeF->SetMapper(mapperF);
		//volumeF->SetProperty(prop);
		mapperF->SetSampleDistance(0.1);

		rendererF->AddVolume(volumeF);
		rendererF->SetBackground(0.5,0.5,0.5);
		rendererF->ResetCamera();
		qVTK1->GetRenderWindow()->Render();
	
		volumeFActive = true;

		vtkBoxWidgetCallback *callback = vtkBoxWidgetCallback::New();
		callback->SetVolumeMapper(mapperF);
		box->AddObserver(vtkCommand::InteractionEvent, callback);
	}
	else
	{
		mapperF->SetInput(f->Fusionate(0));//esto es para no recrear todos los renderers, cuando se haga la fusion con otras opciones...
	}
}
void Mainwindow::slotSetGrayInterval(int opacityMean, int opacityRange)
{
	/*!
		Aquí se hacen todas las llamadas, instanciaciones, para CreateProperty esta función
		va a contener a opacityMean que es la media del valor de gris elegido por el usuario
		opacityRange el tamaño del rango, hay que dividir la mitad de ese valor y sumar o restar
		para obtener el mínimo y el máximo.
	*/
	OpacityMean = opacityMean;
	OpacityRange = opacityRange;

	SetPropertyToActiveVolumes();
}

void Mainwindow::slotSetRGBSegment(std::vector<ColorSegment> *colors)
{
	/*!
		Aquí se hacen todas la llamadas, instanciaciones para leer el vector de ColorSegment
		a partir del vector "colors"
	*/
	Colors = *(colors);
	
	SetPropertyToActiveVolumes();
}

void Mainwindow::SetPropertyToActiveVolumes()
{
	
	vtkSmartPointer<vtkVolumeProperty> property = CreateProperty(	OpacityMean,//mean
																	OpacityRange, //range
																	Colors);
	if(this->volume1Active)
	{
		std::cout<<"1"<<std::endl;
		this->volume1->SetProperty(property);
		std::cout<<"property set to v1"<<std::endl;
	}
	if(this->volume2Active)
	{
		this->volume2->SetProperty(property);
		std::cout<<"property set to v2"<<std::endl;
	}
	if(this->volumeFActive)
	{
		volumeF->SetProperty(property);
		std::cout<<"property set to vF"<<std::endl;
	}
}

void Mainwindow::slotChangeBackground()
{
	/*!
		Método exclusivo de la interfaz para asignar el color de fondo del renderer.
	*/
	QColorDialog winColor;
	QColor col = winColor.getColor(Qt::blue,this);

	if(col.isValid() && winColor.Accepted)
	{
		emit backgroundChanged(col);
		label->setPalette(QPalette(col));
		label->setAutoFillBackground(true);
		vtkRendererCollection *renderers = qVTK1->GetRenderWindow()->GetRenderers();
		vtkCollectionSimpleIterator sit;
		renderers->InitTraversal(sit);
		for(int k=0;k<3;k++)
		{
			vtkRenderer *r = renderers->GetNextRenderer(sit);
		
			if(r != NULL)
			{
				r->SetBackground(col.redF(),
								col.greenF(),
								col.blueF());
			}
		}
	}
	
}
void Mainwindow::dockSetBackgroundColor()
{
	/*!
		Método exclusivo de la interfaz. Crea la ventana flotante que contiene el botón para 
		cambiar el color de fondo.
	*/
	QDockWidget *dockB = new QDockWidget(tr("Opciones de visualización"),this);
	dockB->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea);
	QWidget *window = new QWidget(dockB);
	QGridLayout *grid = new QGridLayout(window);
	QPushButton *pushButtonColor = new QPushButton(tr("Color"),window);
	QCheckBox *boxWidgetState = new QCheckBox(tr("Cubo de corte"),this);
	label = new QLabel(window);
	label->setMaximumSize(16,16);
	label->setPalette(QPalette(Qt::blue));
	label->setAutoFillBackground(true);
	grid->addWidget(label,0,0);
	grid->addWidget(pushButtonColor,0,1);
	grid->addWidget(boxWidgetState,1,0);
	window->setLayout(grid);
	dockB->setWidget(window);
	dockB->setHidden(false);
	dockB->setMaximumSize(280,80);
	connect(pushButtonColor,SIGNAL(clicked()),this,SLOT(slotChangeBackground()));
	connect(boxWidgetState,SIGNAL(toggled(bool)),this,SLOT(setSliceCube(bool)));
	addDockWidget(Qt::RightDockWidgetArea, dockB);
	view->addAction(dockB->toggleViewAction());
}
void Mainwindow::slotShowRGBSegment()
{
	/*!
		Este método es exclusivo de la interfaz. Crea una instancia de RGBSegment la ventana
		que pide cuantos segmentos de color va a usar el usuario.
	*/
	RGBSegment *rgbS = new RGBSegment();
	connect(rgbS,SIGNAL(segment(std::vector<ColorSegment> *)),this,SLOT(slotSetRGBSegment(std::vector<ColorSegment> *)));
	rgbS->show();
}
void Mainwindow::slotLoadCoefDHT(const QString coef)
{
	/*!
		Aquí vamos a hacer las llamadas, instanciaciones, etc. correspondientes a la visualización
		de los Coeficientes de DHT cada número ya indica que coeficiente es el que va a mostrar en pantalla.
		La opción 12 regresa al volumen original.
	*/
	if(coef == "000")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(1));

		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(1));

		std::cout<<"Ver el coeficiente 000"<<std::endl;
	}
	else if(coef == "010")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(2));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(2));
		std::cout<<"Ver el coeficiente 010"<<std::endl;
	}
	else if(coef == "100")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(3));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(3));
		std::cout<<"Ver el coeficiente 100"<<std::endl;
	}
	else if(coef == "001")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(4));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(4));
		std::cout<<"Ver el coeficiente 001"<<std::endl;
	}
	else if(coef == "Gradient")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(5));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(5));
		std::cout<<"Ver el Gradiente"<<std::endl;
	}
	else if(coef == "110")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(6));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(6));
		std::cout<<"Ver el coeficiente 110"<<std::endl;
	}
	else if(coef == "101")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(7));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(7));
		std::cout<<"Ver el coeficiente 101"<<std::endl;
	}
	else if(coef == "011")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(8));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(8));
		std::cout<<"Ver el coeficiente 011"<<std::endl;
	}
	else if(coef == "200")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(9));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(9));
		std::cout<<"Ver el coeficiente 200"<<std::endl;
	}
	else if(coef == "020")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(10));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(10));
		std::cout<<"Ver el coeficiente 020"<<std::endl;
	}
	else if(coef == "002")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(11));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(11));
		std::cout<<"Ver el coeficiente 002"<<std::endl;
	}
	else if(coef == "volume")
	{
		if(volume1Active)
			mapperV1->SetInput(f->GetImageDataV1(0));
		if(volume2Active)
			mapperV2->SetInput(f->GetImageDataV2(0));
		std::cout<<"Ver original"<<std::endl;
	}
	else
	{
		QMessageBox::warning(this, tr("ERROR"),
                              tr("Opción no válida."));
	}

}
void Mainwindow::LoadVolume(std::string name,int op)
{

	vtkSmartPointer<vtkDICOMImageReader> dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
	dicomReader->SetDirectoryName(name.data());
	dicomReader->Update();

	if(op == 1)
	{
		std::cout<<"Voy a cargar el volumen 1 dicom con archivo:\n"<<std::endl;
		std::cout<<name<<std::endl;
		/*!
		Aquí voy a cargar el volumen 1 tipo dicom
		con los parámetros 
		name Es un std::string que tiene la dirección absoluta del conjunto de imágenes
		*/
		//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
		imageDatV1 = dicomReader->GetOutput();
		imageDatV1->Update();
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
	}
	else if(op == 2)
	{
		std::cout<<"Voy a cargar el volumen 2 dicom con archivo:\n"<<std::endl;
		std::cout<<name<<std::endl;
		/*!
		Aquí voy a cargar el volumen 2 tipo dicom
		con los parámetros 
		name Es un std::string que tiene la dirección absoluta del conjunto de imágenes
		*/
		//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
		imageDatV2 = dicomReader->GetOutput();
		imageDatV2->Update();
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
	}
	else
		QMessageBox::warning(this,tr("Advertencia"),tr("No es una opción válida"));
}
void Mainwindow::LoadVolume(std::string name, float spaceX, float spaceY, float spaceZ,int imaX,int imaY,int first, int last,int op)
{
	
	if(op==1)
	{
		/*!
		Aquí voy a cargar el volumen 1 tipo raw
		con los parámetros 
		name	Es un std::string que tiene el patrón para cargar raw
		spaceX	es un float que representa el tamaño del voxel al momento de crearse el volumen sobre el eje X.
		spaceY	es un floar que representa el tamaño del voxel al momento de crearse el volumen sobre el eje Y.
		spaceZ	es un floar que representa el tamaño del voxel al momento de crearse el volumen sobre el eje Z.
		imaX	es un int que representa el tamaño en pixeles de largo de la imagen.
		imaY	es un int que representa el tamaño en pixeles de ancho de la imagen.
		first	es un int que representa el número indicado en el nombre de la imagen para comenzar la carga.
		last	es un int que representa el número indicado en el nombre de la imagen para terminar la carga.
		*/
		std::cout<<"Voy a cargar el volumen 1 raw con archivo:\n"<<std::endl;
		std::cout<<name<<std::endl;

		imageDatV1 = vtkSmartPointer<vtkImageData>::New();

		vtkSmartPointer<vtkImageReader2> r = vtkSmartPointer<vtkImageReader2>::New();

		r->SetDataSpacing(spaceX, spaceY, spaceZ);
		r->SetFilePattern(name.data());
		r->SetDataExtent(0, imaX, 0, imaY, first, last);
		
		r->SetDataOrigin(0.0, 0.0, 0.0);
		r->SetDataScalarTypeToUnsignedChar();
		r->SetDataByteOrderToLittleEndian();
				
		r->UpdateWholeExtent();

		imageDatV1 = r->GetOutput();
		imageDatV1->Update();
		
		//std::cout<<"dim: = "<<imageDatV1->GetDimensions()[0]<<std::endl;
		//std::cout<<"dim: = "<<imageDatV1->GetDimensions()[1]<<std::endl;
		//std::cout<<"dim: = "<<imageDatV1->GetDimensions()[2]<<std::endl;

		//vtkSmartPointer<vtkVolume16Reader> v16 = vtkSmartPointer<vtkVolume16Reader>::New();
		//v16->SetDataDimensions (imaX,imaY);
		//v16->SetImageRange (first,last);
		//v16->SetDataByteOrderToLittleEndian();
		//v16->SetFilePrefix ("CT_Raw\\CT-");
		//v16->SetFilePattern("%s%d.raw");
		//v16->SetDataSpacing (spaceX, spaceY, spaceZ);
		////v16->Update();
		////v16->UpdateWholeExtent();
		//imageDatV1 = v16->GetOutput();
		//imageDatV1->Update();

		//std::cout<<"dim: = "<<imageDatV1->GetDimensions()[0]<<std::endl;
		//std::cout<<"dim: = "<<imageDatV1->GetDimensions()[1]<<std::endl;
		//std::cout<<"dim: = "<<imageDatV1->GetDimensions()[2]<<std::endl;
		


	}
	else if(op ==2)
	{
		/*!
		Aquí voy a cargar el volumen 2 tipo raw
		con los parámetros 
		name	Es un std::string que tiene el patrón para cargar raw
		spaceX	es un float que representa el tamaño del voxel al momento de crearse el volumen sobre el eje X.
		spaceY	es un floar que representa el tamaño del voxel al momento de crearse el volumen sobre el eje Y.
		spaceZ	es un floar que representa el tamaño del voxel al momento de crearse el volumen sobre el eje Z.
		imaX	es un int que representa el tamaño en pixeles de largo de la imagen.
		imaY	es un int que representa el tamaño en pixeles de ancho de la imagen.
		first	es un int que representa el número indicado en el nombre de la imagen para comenzar la carga.
		last	es un int que representa el número indicado en el nombre de la imagen para terminar la carga.
		*/
		std::cout<<"Voy a cargar el volumen 2 raw con archivo:\n"<<std::endl;
		std::cout<<name<<std::endl;

		imageDatV2 = vtkSmartPointer<vtkImageData>::New();

		vtkSmartPointer<vtkImageReader2> r = vtkSmartPointer<vtkImageReader2>::New();

		r->SetDataSpacing(spaceX, spaceY, spaceZ);
		r->SetFilePattern(name.data());
		r->SetDataExtent(0, imaX, 0, imaY, first, last);
		
		r->SetDataOrigin(0.0, 0.0, 0.0);
		//r->SetDataScalarTypeToShort();
		//r->SetHeaderSize(1.26);
		//r->SetDataScalarTypeToUnsignedInt();
		//r->SetDataScalarTypeToUnsignedShort();
		r->SetDataScalarTypeToUnsignedChar();
		r->SetDataByteOrderToLittleEndian();
		//r->SetDataByteOrderToBigEndian();
		r->UpdateWholeExtent();
		
		imageDatV2 = r->GetOutput();
		imageDatV2->Update();
		//vtkSmartPointer<vtkVolume16Reader> v16 = vtkSmartPointer<vtkVolume16Reader>::New();
		//v16->SetDataDimensions (imaX,imaY);
		//v16->SetImageRange (first,last);
		//v16->SetDataByteOrderToLittleEndian();
		//v16->SetFilePrefix ("CT_Raw\\CT-");
		//v16->SetFilePattern("%s%d.raw");
		//v16->SetDataSpacing (spaceX, spaceY, spaceZ);
		////v16->UpdateWholeExtent();
		//imageDatV2 = v16->GetOutput();
		//imageDatV2->Update();

		//std::cout<<"dim: = "<<imageDatV2->GetDimensions()[0]<<std::endl;
		//std::cout<<"dim: = "<<imageDatV2->GetDimensions()[1]<<std::endl;
		//std::cout<<"dim: = "<<imageDatV2->GetDimensions()[2]<<std::endl;
	}
	else
		QMessageBox::warning(this,tr("Advertencia"),tr("No es una opción válida"));
}

vtkSmartPointer<vtkVolumeProperty> Mainwindow::CreateProperty(int opacityMean, int opacityRange, std::vector<ColorSegment> colorSegments)
{
	vtkSmartPointer<vtkVolumeProperty> prop = vtkSmartPointer<vtkVolumeProperty>::New();
	vtkSmartPointer<vtkColorTransferFunction> colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();

	for(unsigned int i=0; i<colorSegments.size(); i++)
	{
		colorFun->AddRGBSegment(colorSegments[i].minGrayLevel, colorSegments[i].redMin, colorSegments[i].greenMin, colorSegments[i].blueMin,
								colorSegments[i].maxGrayLevel, colorSegments[i].redMax, colorSegments[i].greenMax, colorSegments[i].blueMax );
		//colorFun->AddRGBSegment(160, 0.9, 0.9, 0.9,
		//					255, 0.9, 0.9, 0.9 );
	}

	
	//colorFun->AddRGBSegment(mean - 0.5*range, 0.0, 0.0, 0.0,
							//mean + 0.5*range, 1.0, 1.0, 1.0 );
	opacityFun->AddSegment( opacityMean - 0.5*opacityRange, 0.0,

							opacityMean + 0.5*opacityRange, 1.0 );

	prop->SetAmbient(0.1);
	prop->SetDiffuse(0.9);
	prop->SetSpecular(0.4);
	prop->SetSpecularPower(10.0);
	prop->SetIndependentComponents(false);
	prop->SetColor( colorFun );
	prop->SetScalarOpacity( opacityFun );
	prop->SetInterpolationTypeToLinear();
	prop->ShadeOn();
	

	return prop;
}

void Mainwindow::LoadVolume(std::string dir, std::string file,std::string pfx,std::string ptr,int xBegin, int xEnd, int yBegin, int yEnd,int imgB, int imgE,int op)
{
	if(op==1)
	{
		/*!
			Aquí realizo las instanciaciones para cargar un volumen 1
			dir		es un string que contiene la dirección del conjunto de imágenes.
			file	es un string que contiene la dirección de la primera imagen del conjunto.
			pfx		es un string que contiene el texto prefijo que es común en el nombre del conjunto de imágenes.
			ptr		es un string que contiene el texto patrón nombreArchivo%d.bmp.
			xBegin	es un int que representa el tamaño en pixeles de largo de la imagen empezando en cero.
			xEnd	es un int que representa el tamaño en pixeles de largo de la imagen menos un pixel.
			yBegin	es un int que representa el tamaño en pixeles de ancho de la imagen empezando en cero.
			yEnd	es un int que representa el tamaño en pixeles de ancho de la imagen menos un pixel.
			imgB    es un int que indica con que entero comenzará la carga de acuerdo al sufijo indicado en el nombre de la imagen.
			imgE	es un int que indica con que entero terminará la carga de acuerdo al sufijo indicado en el nombre de la imagen.
		*/
		//std::cout<<"Voy a cargar el volumen 1 bmp con archivo:\n"<<std::endl;
		//std::cout<<dir<<std::endl;

		//imageDatV1 = vtkSmartPointer<vtkImageData>::New();

		//vtkSmartPointer<vtkImageReader2Factory> readerFactory =
		//vtkSmartPointer<vtkImageReader2Factory>::New();
		////sprintf_s(file);
		//vtkSmartPointer<vtkImageReader2> r = readerFactory->CreateImageReader2(file.data());
		////vtkSmartPointer<vtkImageReader2> r = vtkSmartPointer<vtkImageReader2>::New();

		//r->SetFilePrefix(pfx.data());
		//r->SetFilePattern(ptr.data());
		//r->SetDataExtent(xBegin, xEnd, yBegin, yEnd, imgB, imgE);
		//
		//r->SetDataOrigin(0.0, 0.0, 0.0);
		//r->SetDataScalarTypeToUnsignedShort();
		////r->SetDataScalarTypeToUnsignedInt();
		////r->SetDataScalarTypeToUnsignedChar();
		////r->SetDataScalarTypeToChar();
		////r->SetDataByteOrderToLittleEndian();
		////r->SetDataByteOrderToBigEndian();
		//r->UpdateWholeExtent();

		//imageDatV1 = r->GetOutput();
		//imageDatV1->Update();

		imageDatV1 = vtkSmartPointer<vtkImageData>::New();
		//imageDatV1->SetExtent(0,7,0,7,0,7);

		imageDatV1->SetDimensions(4,4,4);
		//imageDatV1->SetWholeExtent(extent);
		imageDatV1->SetSpacing(1,1,1);
		imageDatV1->SetOrigin(0,0,0);
		imageDatV1->SetScalarTypeToUnsignedChar();

		unsigned char auxiliar = 50;
		for(int k=0;k<4;k++)
		{
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					unsigned char *scalarPointerR = (unsigned char *)imageDatV1->GetScalarPointer(i,j,k); 
					scalarPointerR[0] = auxiliar;
					
					auxiliar++;
					
				}
			}
		}

		imageDatV1->Update();

		
	}
	else if(op==2)
	{
		///*!
		//	Aquí realizo las instanciaciones para cargar un volumen 2
		//	dir		es un string que contiene la dirección del conjunto de imágenes.
		//	file	es un string que contiene la dirección de la primera imagen del conjunto.
		//	pfx		es un string que contiene el texto prefijo que es común en el nombre del conjunto de imágenes.
		//	ptr		es un string que contiene el texto patrón nombreArchivo%d.bmp.
		//	xBegin	es un int que representa el tamaño en pixeles de largo de la imagen empezando en cero.
		//	xEnd	es un int que representa el tamaño en pixeles de largo de la imagen menos un pixel.
		//	yBegin	es un int que representa el tamaño en pixeles de ancho de la imagen empezando en cero.
		//	yEnd	es un int que representa el tamaño en pixeles de ancho de la imagen menos un pixel.
		//	imgB    es un int que indica con que entero comenzará la carga de acuerdo al sufijo indicado en el nombre de la imagen.
		//	imgE	es un int que indica con que entero terminará la carga de acuerdo al sufijo indicado en el nombre de la imagen.
		//*/
		////std::cout<<"Voy a cargar el volumen 2 bmp con archivo:\n"<<std::endl;
		////std::cout<<dir<<std::endl;

		//imageDatV2 = vtkSmartPointer<vtkImageData>::New();

		//vtkSmartPointer<vtkImageReader2Factory> readerFactory =
		//vtkSmartPointer<vtkImageReader2Factory>::New();
		////sprintf_s(file);
		//vtkSmartPointer<vtkImageReader2> r = readerFactory->CreateImageReader2(file.data());
		////vtkSmartPointer<vtkImageReader2> r = vtkSmartPointer<vtkImageReader2>::New();

		//r->SetFilePrefix(pfx.data());
		//r->SetFilePattern(ptr.data());
		//r->SetDataExtent(xBegin, xEnd, yBegin, yEnd, imgB, imgE);
		//
		//r->SetDataOrigin(0.0, 0.0, 0.0);
		//r->SetDataScalarTypeToUnsignedShort();
		////r->SetDataScalarTypeToUnsignedInt();
		////r->SetDataScalarTypeToUnsignedChar();
		////r->SetDataScalarTypeToChar();
		////r->SetDataByteOrderToLittleEndian();
		////r->SetDataByteOrderToBigEndian();
		//r->UpdateWholeExtent();

		//imageDatV2 = r->GetOutput();
		//imageDatV2->Update();

		imageDatV2 = vtkSmartPointer<vtkImageData>::New();
		//imageDatV2->SetExtent(0,7,0,7,0,7);

		imageDatV2->SetDimensions(4,4,4);
		//imageDatV1->SetWholeExtent(extent);
		imageDatV2->SetSpacing(1,1,1);
		imageDatV2->SetOrigin(0,0,0);
		imageDatV2->SetScalarTypeToUnsignedChar();

		unsigned char auxiliar = 50;
		for(int k=0;k<4;k++)
		{
			for(int j=0;j<4;j++)
			{
				for(int i=0;i<4;i++)
				{
					unsigned char *scalarPointerR = (unsigned char *)imageDatV2->GetScalarPointer(i,j,k); 
					scalarPointerR[0] = auxiliar;
					
					auxiliar++;
					
				}
			}
		}

		imageDatV2->Update();
	}
	else
		QMessageBox::warning(this,tr("Advertencia"),tr("No es una opción válida"));
}