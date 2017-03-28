#include <QtGui>
#include "projectwizard.h"

ProjectWizard::ProjectWizard(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_LoadDICOM, new LoadDICOMPage);
    setPage(Page_LoadRAW, new LoadRAWPage);
	setPage(Page_LoadBMP, new LoadBMPPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Intro);

#ifndef Q_WS_MAC
    setWizardStyle(ModernStyle);
#endif
    setOption(HaveHelpButton, true);
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));

    setWindowTitle(tr("Cargar datos"));
}

void ProjectWizard::accept()
{
	QByteArray block,volA, volB;
	QByteArray sizeXA, sizeYA,spacingXA,spacingYA,spacingZA, index1A,index2A;
	QByteArray sizeXB, sizeYB,spacingXB,spacingYB,spacingZB, index1B,index2B;

	QByteArray bmpA,prefixA,patternA,lengthA,heightA,nImgA;
	QByteArray bmpB,prefixB,patternB,lengthB,heightB,nImgB;

	if(field("dcm_op").toBool())
	{
		volA = field("dicom.nameA").toByteArray();
		volB = field("dicom.nameB").toByteArray();

		block ="dicom\n" + volA + "\n" + volB;
	}
	else if(field("raw_op").toBool())
		{
			volA = field("raw.volA").toByteArray();
			sizeXA = field("raw.sizeXA").toByteArray();
			sizeYA = field("raw.sizeYA").toByteArray();
			spacingXA = field("raw.espXA").toByteArray();
			spacingYA = field("raw.espYA").toByteArray();
			spacingZA = field("raw.espZA").toByteArray();
			index1A = field("raw.idx1A").toByteArray();
			index2A = field("raw.idx2A").toByteArray();

			volB = field("raw.volB").toByteArray();
			sizeXB = field("raw.sizeXB").toByteArray();
			sizeYB = field("raw.sizeYB").toByteArray();
			spacingXB = field("raw.espXB").toByteArray();
			spacingYB = field("raw.espYB").toByteArray();
			spacingZB = field("raw.espZB").toByteArray();
			index1B = field("raw.idx1B").toByteArray();
			index2B = field("raw.idx2B").toByteArray();

			block = "raw\n" + volA + "\n" + sizeXA + "\n" + sizeYA + "\n" 
			+ spacingXA + "\n"+ spacingYA + "\n"+ spacingZA + "\n"+ index1A + "\n"
			+ index2A + "\n"+ volB + "\n"+ sizeXB + "\n"+ sizeYB + "\n"
			+ spacingXB + "\n"+ spacingYB + "\n"+ spacingZB + "\n"+ index1B + "\n" + index2B ;
		}
			else if(field("bmp_op").toBool())
			{
				volA = field("bmp.dirvolA").toByteArray();
				bmpA = field("bmp.filevolA").toByteArray();
				prefixA=field("bmp.prefixvolA").toByteArray();
				patternA=field("bmp.patternvolA").toByteArray();
				lengthA = field("bmp.lengthVolA").toByteArray();
				heightA = field("bmp.heightVolA").toByteArray();
				nImgA = field("bmp.numImgA").toByteArray();

				volB = field("bmp.dirvolB").toByteArray();
				bmpB = field("bmp.filevolB").toByteArray();
				prefixB=field("bmp.prefixvolB").toByteArray();
				patternB=field("bmp.patternvolB").toByteArray();
				lengthB = field("bmp.lengthVolB").toByteArray();
				heightB = field("bmp.heightVolB").toByteArray();
				nImgB = field("bmp.numImgB").toByteArray();

				block = "bmp\n" + volA + "\n" +
				bmpA + "\n" +
				prefixA + "\n" +
				patternA + "\n" +
				lengthA + "\n" +
				heightA + "\n" +
				nImgA + "\n" +
				volB + "\n" +
				bmpB + "\n" +
				prefixB + "\n" +
				patternB + "\n" +
				lengthB + "\n" +
				heightB + "\n" +
				nImgB; 
			}
    QString outputDir = field("outputDir").toString() + ".txt";

	QFile projectFile(outputDir);
    if (!projectFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Simple Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
							 .arg(projectFile.fileName())
							 .arg(projectFile.errorString()));
        return;
    }
	QDialog::accept();
    projectFile.write(block);
	projectFile.close();
	emit fileReady(outputDir);
}


void ProjectWizard::showHelp()
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Intro:
        message = tr("En esta ventana hay que seleccionar el formato de las imágenes "
                     "que va a cargar en la aplicación"
					 "<p> Entre los formatos aceptados en esta aplicación se encuentran </p>"
					 "<tt>DICOM   RAW  y   BMP </tt> ");
        break;
    case Page_LoadDICOM:
        message = tr("Para cargar imágenes en formato dicom, sólo se requiere de la "
                     "ubicación del directorio contenedor de sus imágenes");
        break;
    case Page_LoadRAW:
        message = tr("<p><tt>Para cargar imágenes en formato raw, se requieren de los siguientes parámetros</tt></p> "
			"<p>Un patrón por ejemplo - frz\\frzo%d.raw </p> donde frz es el directorio que contiene las imágenes</p> "
			"<p>frzo es el nombre común para las imágenes y el %d corresponde al cambio numérico consecutivo.</p> "
			"<p>El tamaño de las imágenes (por omisión 256 pixeles) de largo y ancho</p>"
			"<p>Primer indice y último indican el rango de la serie de imágenes, ejemplo frzo1,frzo2,frzo3,...frzo133</p>"
			"<p>para este ejemplo el primer indice es 1, mientras que el último es 133.</p> "
					 "<p>Los espaciamientos indican una escala de interpolación en cada uno de los ejes.</p>");
        break;
	case Page_LoadBMP:
        message = tr("<p><tt>Para cargar imágenes en formato bmp, se requieren de los siguientes parámetros</tt></p> "
			"<p>El directorio que contiene las imágenes </p>"
			"<p>La primera imagen del conjunto de imágenes para formar su volumen.</p> "
			"<p>Un prefijo, el nombre que se repite en todas las imágenes </p>"
			"<p>El patrón se indica con %d si la secuencia de imágenes van de 1,2,3..100, etc.</p> "
			"<p>El tamaño de las imágenes por omisión será de 256 pixeles</p>"
			"<p>Número de imágenes para formar su volumen.</p> ");
        break;
    case Page_Conclusion:
        message = tr("Asigne un nombre al archivo que contendrá los datos para cargar "
                     "las imágenes seleccionadas.");
        break;
    default:
        message = tr("No hay ayuda disponible.");
    }

    if (lastHelpMessage == message)
        message = tr("Consulte el manual de usuario para mayores detalles");

    QMessageBox::information(this, tr("Ayuda del cargador de datos"), message);

    lastHelpMessage = message;

}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Formato de las imagenes"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    topLabel = new QLabel(tr("Este asistente lo guiara por una serie de ventanas "
                             "para elegir las imagenes, especificar carácteristicas "
                             "y crear el volumen requerido, para finalizar visualizando"
							 "sus volúmenes."));
    dcmRadioButton = new QRadioButton(tr("Imágenes en formato DICOM"));
    rawRadioButton = new QRadioButton(tr("Imágenes en formato RAW"));
	bmpRadioButton = new QRadioButton(tr("Imágenes en formato BMP"));
    dcmRadioButton->setChecked(true);

	registerField("dcm_op",dcmRadioButton);
	registerField("raw_op",rawRadioButton);
	registerField("bmp_op",bmpRadioButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(dcmRadioButton);
    layout->addWidget(rawRadioButton);
	layout->addWidget(bmpRadioButton);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    if (dcmRadioButton->isChecked()) 
	{
        return ProjectWizard::Page_LoadDICOM;
    } else if(rawRadioButton->isChecked())
			{
				return ProjectWizard::Page_LoadRAW;
			} 
			else if(bmpRadioButton->isChecked()) 
			{
					return ProjectWizard::Page_LoadBMP;
			}
	return -1;
}

LoadDICOMPage::LoadDICOMPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("DICOM"));
    setSubTitle(tr("Complete el campo requerido con la ubicación de la carpeta, presione el botón "
                   "si no conoce la ruta del directorio"));
	setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    vol1Label = new QLabel(tr("Dirección del conjunto de imágenes A:"));
    vol1LineEdit = new QLineEdit;

    QPushButton *pathButton = new QPushButton("...");
	connect(pathButton,SIGNAL(clicked()),this,SLOT(getDirNameA()));
	connect(this,SIGNAL(strDirNameA(const QString)),vol1LineEdit,SLOT(setText(const QString)));
	
    registerField("dicom.nameA*", vol1LineEdit);

	vol2Label = new QLabel(tr("Dirección del conjunto de imágenes B:"));
    vol2LineEdit = new QLineEdit;

    QPushButton *pathButton2 = new QPushButton("...");
	connect(pathButton2,SIGNAL(clicked()),this,SLOT(getDirNameB()));
	connect(this,SIGNAL(strDirNameB(const QString)),vol2LineEdit,SLOT(setText(const QString)));

	
    registerField("dicom.nameB*", vol2LineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(vol1Label, 0, 0);
    layout->addWidget(vol1LineEdit, 0, 1);
    layout->addWidget(pathButton, 0, 2);
	layout->addWidget(vol2Label, 1, 0);
    layout->addWidget(vol2LineEdit, 1, 1);
    layout->addWidget(pathButton2, 1, 2);
    setLayout(layout);
}
void LoadDICOMPage::getDirNameA()
{
	QString dirA = QFileDialog::getExistingDirectory(this,tr("Seleciona directorio"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	
	emit strDirNameA(dirA);
}
void LoadDICOMPage::getDirNameB()
{
	QString dirB = QFileDialog::getExistingDirectory(this,tr("Seleciona directorio"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	
	emit strDirNameB(dirB);
}
int LoadDICOMPage::nextId() const
{
    return ProjectWizard::Page_Conclusion;
}

LoadRAWPage::LoadRAWPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr(" RAW "));
    setSubTitle(tr("Complete los campos requeridos"));
	setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

	QHBoxLayout *main = new QHBoxLayout;
	main->addWidget(groupBox());
	main->addWidget(groupBox2());
    setLayout(main);

}
QGroupBox *LoadRAWPage::groupBox()
{
	QGroupBox *main = new QGroupBox(tr("Volumen A"));
	labelA = new QLabel(tr("Patrón :"));
	prefixA = new QLabel("Espaciamiento:");
	dimA = new QLabel("Dimensión de la Imagen:");
	indexA = new QLabel(tr("Indices del Conjunto:"));

	QLabel *labelX = new QLabel(tr("X:"));
	QLabel *labelY = new QLabel(tr("Y:"));
	QLabel *labelZ = new QLabel(tr("Z:"));
	QLabel *labelU = new QLabel(tr("Largo:"));
	QLabel *labelV = new QLabel(tr("Ancho:"));
	QLabel *tex1 = new QLabel(tr("La primera imagen:"));
	QLabel *tex2 = new QLabel(tr("La última imagen:"));

	vol1LineEdit = new QLineEdit;
	sizeX = new QSpinBox;
	sizeX->setRange(1,3000);
	sizeX->setSingleStep(10);
	sizeX->setValue(256);

	sizeY = new QSpinBox;
	sizeY->setRange(1,3000);
	sizeY->setSingleStep(10);
	sizeY->setValue(256);

	espX = new QDoubleSpinBox;
	espX->setRange(0.01,12.99);
	espX->setValue(1.00);

	espY = new QDoubleSpinBox;
	espY->setRange(0.01,12.99);
	espY->setValue(1.00);

	espZ = new QDoubleSpinBox;
	espZ->setRange(0.01,12.99);
	espZ->setValue(1.80);

	firstImageIndex = new QSpinBox;
	firstImageIndex->setRange(1,10);
	firstImageIndex->setValue(1);

	lastImageIndex = new QSpinBox;
	lastImageIndex->setRange(1,400);
	lastImageIndex->setValue(10);

    registerField("raw.volA*", vol1LineEdit);
	registerField("raw.sizeXA",sizeX);
	registerField("raw.sizeYA",sizeY);
	registerField("raw.espXA",espX,"value"," valueChanged()");
	registerField("raw.espYA",espY,"value"," valueChanged()");
	registerField("raw.espZA",espZ,"value"," valueChanged()");
	registerField("raw.idx1A",firstImageIndex);
	registerField("raw.idx2A",lastImageIndex);

	QHBoxLayout *lay1 = new QHBoxLayout;
	lay1->addWidget(labelU);
	lay1->addWidget(sizeX,2);

	QHBoxLayout *lay2 = new QHBoxLayout;
	lay2->addWidget(labelV);
	lay2->addWidget(sizeY,2);

	QVBoxLayout *layoutSize = new QVBoxLayout;
	layoutSize->addWidget(dimA);
    layoutSize->addLayout(lay1);
    layoutSize->addLayout(lay2);
    
	QHBoxLayout *lay3 = new QHBoxLayout;
	lay3->addWidget(labelX);
	lay3->addWidget(espX);

	QHBoxLayout *lay4 = new QHBoxLayout;
	lay4->addWidget(labelY);
	lay4->addWidget(espY);

	QHBoxLayout *lay5 = new QHBoxLayout;
	lay5->addWidget(labelZ);
	lay5->addWidget(espZ);

	QVBoxLayout *layoutEsp = new QVBoxLayout;
	layoutEsp->addWidget(prefixA);
    layoutEsp->addLayout(lay3);
    layoutEsp->addLayout(lay4);
	layoutEsp->addLayout(lay5);  

	QHBoxLayout *lay6 = new QHBoxLayout;
	lay6->addWidget(tex1);
	lay6->addWidget(firstImageIndex,2);

	QHBoxLayout *lay7 = new QHBoxLayout;
	lay7->addWidget(tex2);
	lay7->addWidget(lastImageIndex,2);

	QVBoxLayout *layoutIndex = new QVBoxLayout;
	layoutIndex->addWidget(indexA);
    layoutIndex->addLayout(lay6);
    layoutIndex->addLayout(lay7);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(labelA,0,0);
	layout->addWidget(vol1LineEdit,0,1,1,4);
	layout->addLayout(layoutSize,1,0);
	layout->addLayout(layoutEsp,2,0);
	layout->addLayout(layoutIndex,1,1);
	main->setLayout(layout);
    
	return main;
}
QGroupBox *LoadRAWPage::groupBox2()
{
	QGroupBox *main = new QGroupBox(tr("Volumen B"));
	labelB = new QLabel(tr("Patrón :"));
	prefixB = new QLabel("Espaciamiento:");
	dimB = new QLabel("Dimensión de la Imagen:");
	indexB = new QLabel(tr("Indices del Conjunto:"));
	vol2LineEdit = new QLineEdit;
	
	QLabel *labelX = new QLabel(tr("X:"));
	QLabel *labelY = new QLabel(tr("Y:"));
	QLabel *labelZ = new QLabel(tr("Z:"));
	QLabel *labelU = new QLabel(tr("Largo:"));
	QLabel *labelV = new QLabel(tr("Ancho:"));
	QLabel *tex1 = new QLabel(tr("La primera imagen:"));
	QLabel *tex2 = new QLabel(tr("La última imagen:"));

	sizeX_2 = new QSpinBox;
	sizeX_2->setRange(1,3000);
	sizeX_2->setSingleStep(20);
	sizeX_2->setValue(256);

	sizeY_2 = new QSpinBox;
	sizeY_2->setRange(1,3000);
	sizeY_2->setSingleStep(20);
	sizeY_2->setValue(256);

	espX_2 = new QDoubleSpinBox;
	espX_2->setRange(0.01,12.99);
	espX_2->setValue(1.0);

	espY_2 = new QDoubleSpinBox;
	espY_2->setRange(0.01,12.99);
	espY_2->setValue(1.0);

	espZ_2 = new QDoubleSpinBox;
	espZ_2->setRange(0.01,12.99);
	espZ_2->setValue(1.80);

	firstImageIndex_2 = new QSpinBox;
	firstImageIndex_2->setRange(1,10);
	firstImageIndex_2->setValue(1);

	lastImageIndex_2 = new QSpinBox;
	lastImageIndex_2->setRange(1,400);
	lastImageIndex_2->setValue(10);

    registerField("raw.volB*", vol2LineEdit);
	registerField("raw.sizeXB",sizeX_2);
	registerField("raw.sizeYB",sizeY_2);
	registerField("raw.espXB",espX_2,"value"," valueChanged()");
	registerField("raw.espYB",espY_2,"value"," valueChanged()");
	registerField("raw.espZB",espZ_2,"value"," valueChanged()");
	registerField("raw.idx1B",firstImageIndex_2);
	registerField("raw.idx2B",lastImageIndex_2);

	QHBoxLayout *laya = new QHBoxLayout;
	laya->addWidget(labelU);
	laya->addWidget(sizeX_2,2);

	QHBoxLayout *layb = new QHBoxLayout;
	layb->addWidget(labelV);
	layb->addWidget(sizeY_2,2);
	
	QVBoxLayout *layoutSize = new QVBoxLayout;
	layoutSize->addWidget(dimB);
    layoutSize->addLayout(laya);
    layoutSize->addLayout(layb);
   
	QHBoxLayout *lay3 = new QHBoxLayout;
	lay3->addWidget(labelX);
	lay3->addWidget(espX_2,2);

	QHBoxLayout *lay4 = new QHBoxLayout;
	lay4->addWidget(labelY);
	lay4->addWidget(espY_2,2);

	QHBoxLayout *lay5 = new QHBoxLayout;
	lay5->addWidget(labelZ);
	lay5->addWidget(espZ_2,2);

	QVBoxLayout *layoutEsp = new QVBoxLayout;
	layoutEsp->addWidget(prefixB);
    layoutEsp->addLayout(lay3);
    layoutEsp->addLayout(lay4);
	layoutEsp->addLayout(lay5);
   
	QHBoxLayout *lay6 = new QHBoxLayout;
	lay6->addWidget(tex1);
	lay6->addWidget(firstImageIndex_2,2);

	QHBoxLayout *lay7 = new QHBoxLayout;
	lay7->addWidget(tex2);
	lay7->addWidget(lastImageIndex_2,2);

	QVBoxLayout *layoutIndex = new QVBoxLayout;
	layoutIndex->addWidget(indexB);
    layoutIndex->addLayout(lay6);
    layoutIndex->addLayout(lay7);
   
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(labelB,0,0);
	layout->addWidget(vol2LineEdit,0,1,1,4);
	layout->addLayout(layoutSize,1,0);
	layout->addLayout(layoutEsp,2,0);
	layout->addLayout(layoutIndex,1,2);
	main->setLayout(layout);
	return main;
}

int LoadRAWPage::nextId() const
{	
	return ProjectWizard::Page_Conclusion;
}

LoadBMPPage::LoadBMPPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Bit Mapper bmp"));
    setSubTitle(tr("Complete el campo requerido con la ubicación de la carpeta, presione el botón "
                   "si no conoce la ruta del directorio"));
	setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

	QHBoxLayout *main = new QHBoxLayout;
	main->addWidget(groupBoxBMP());
	main->addWidget(groupBoxBMP_2());
	setLayout(main);
}
QGroupBox *LoadBMPPage::groupBoxBMP()
{
	QGroupBox *main = new QGroupBox(tr("Volumen A"));
	labelDir = new QLabel(tr("Directorio:"));
	labelFile = new QLabel(tr("Selecciona la primera imagen:"));
	labelPrefix = new QLabel(tr("Prefijo"));
	labelPattern = new QLabel(tr("Patrón"));
	labelImgDim = new QLabel(tr("Dimensiones de la imagen:"));
	QLabel *labellength = new QLabel(tr("Largo"));
	QLabel *labelheight = new QLabel(tr("Ancho"));
	labelImgNum = new QLabel(tr("Número de imágenes"));
	dirLineEdit = new QLineEdit;
	imgLineEdit = new QLineEdit;
	prxLineEdit = new QLineEdit;
	ptrLineEdit = new QLineEdit;
	buttonDir = new QPushButton("...");
	buttonImg = new QPushButton("...");
	connect(buttonDir,SIGNAL(clicked()),this,SLOT(getDirNameA()));
	connect(buttonImg,SIGNAL(clicked()),this,SLOT(getFileNameA()));
	connect(this,SIGNAL(strDirNameA(const QString)),dirLineEdit,SLOT(setText(const QString)));
	connect(this,SIGNAL(strFileNameA(const QString)),imgLineEdit,SLOT(setText(const QString)));

	spinBoxlength = new QSpinBox;
	spinBoxlength->setRange(1,3000);
	spinBoxlength->setSingleStep(20);
	spinBoxlength->setValue(256);

	spinBoxheight = new QSpinBox;
	spinBoxheight->setRange(1,3000);
	spinBoxheight->setSingleStep(20);
	spinBoxheight->setValue(256);

	spinBoxImg = new QSpinBox;
	spinBoxImg->setRange(1,4092);
	spinBoxImg->setSingleStep(256);
	spinBoxImg->setValue(256);

	registerField("bmp.dirvolA*",dirLineEdit );
	registerField("bmp.filevolA*",imgLineEdit);
	registerField("bmp.prefixvolA*",prxLineEdit);
	registerField("bmp.patternvolA*",ptrLineEdit);
	registerField("bmp.lengthVolA",spinBoxlength);
	registerField("bmp.heightVolA",spinBoxheight);
	registerField("bmp.numImgA",spinBoxImg);

	QHBoxLayout *lay1 = new QHBoxLayout;
	lay1->addWidget(dirLineEdit,4);
	lay1->addWidget(buttonDir);

	QHBoxLayout *lay2 = new QHBoxLayout;
	lay2->addWidget(imgLineEdit,4);
	lay2->addWidget(buttonImg);

	QVBoxLayout *layout1 = new QVBoxLayout;
	layout1->addLayout(lay1);
	layout1->addLayout(lay2);
	layout1->addWidget(prxLineEdit);
	layout1->addWidget(ptrLineEdit);

	QVBoxLayout *layout2 = new QVBoxLayout;
	layout2->addWidget(labelDir);
	layout2->addWidget(labelFile);
	layout2->addWidget(labelPrefix);
	layout2->addWidget(labelPattern);

	QHBoxLayout *layout3 = new QHBoxLayout;
	layout3->addLayout(layout2);
	layout3->addLayout(layout1,4);

	QVBoxLayout *layout4 = new QVBoxLayout;
	layout4->addWidget(labellength);
	layout4->addWidget(labelheight);

	QVBoxLayout *layout5 = new QVBoxLayout;
	layout5->addWidget(spinBoxlength);
	layout5->addWidget(spinBoxheight);

	QHBoxLayout *layout6 = new QHBoxLayout;
	layout6->addWidget(labelImgNum);
	layout6->addWidget(spinBoxImg);

	QHBoxLayout *layout7 = new QHBoxLayout;
	layout7->addLayout(layout4);
	layout7->addLayout(layout5);

	QVBoxLayout *layout8 =new QVBoxLayout;
	layout8->addWidget(labelImgDim);
	layout8->addLayout(layout7);

	QGridLayout *laymain = new QGridLayout;
	laymain->addLayout(layout3,0,0,1,4);
	laymain->addLayout(layout6,1,2);
	laymain->addLayout(layout7,1,1);
	laymain->addLayout(layout8,1,0);
	main->setLayout(laymain);
	
	return main;
}
QGroupBox *LoadBMPPage::groupBoxBMP_2()
{
	QGroupBox *main = new QGroupBox(tr("Volumen B"));

	labelDir_2 = new QLabel(tr("Directorio:"));
	labelFile_2 = new QLabel(tr("Selecciona la primera imagen:"));
	labelPrefix_2 = new QLabel(tr("Prefijo"));
	labelPattern_2 = new QLabel(tr("Patrón"));
	labelImgDim_2 = new QLabel(tr("Dimensiones de la imagen:"));
	QLabel *labellength = new QLabel(tr("Largo"));
	QLabel *labelheight = new QLabel(tr("Ancho"));
	labelImgNum_2 = new QLabel(tr("Número de imágenes"));
	dirLineEdit_2 = new QLineEdit;
	imgLineEdit_2 = new QLineEdit;
	prxLineEdit_2 = new QLineEdit;
	ptrLineEdit_2 = new QLineEdit;
	buttonDir_2 = new QPushButton("...");
	buttonImg_2 = new QPushButton("...");
	connect(buttonDir_2,SIGNAL(clicked()),this,SLOT(getDirNameB()));
	connect(buttonImg_2,SIGNAL(clicked()),this,SLOT(getFileNameB()));
	connect(this,SIGNAL(strDirNameB(const QString)),dirLineEdit_2,SLOT(setText(const QString)));
	connect(this,SIGNAL(strFileNameB(const QString)),imgLineEdit_2,SLOT(setText(const QString)));

	spinBoxlength_2 = new QSpinBox;
	spinBoxlength_2->setRange(1,3000);
	spinBoxlength_2->setSingleStep(20);
	spinBoxlength_2->setValue(256);

	spinBoxheight_2 = new QSpinBox;
	spinBoxheight_2->setRange(1,3000);
	spinBoxheight_2->setSingleStep(20);
	spinBoxheight_2->setValue(256);

	spinBoxImg_2 = new QSpinBox;
	spinBoxImg_2->setRange(1,4092);
	spinBoxImg_2->setSingleStep(256);
	spinBoxImg_2->setValue(256);

	registerField("bmp.dirvolB*",dirLineEdit_2 );
	registerField("bmp.filevolB*",imgLineEdit_2);
	registerField("bmp.prefixvolB*",prxLineEdit_2);
	registerField("bmp.patternvolB*",ptrLineEdit_2);
	registerField("bmp.lengthVolB",spinBoxlength_2);
	registerField("bmp.heightVolB",spinBoxheight_2);
	registerField("bmp.numImgB",spinBoxImg_2);

	QHBoxLayout *lay1 = new QHBoxLayout;
	lay1->addWidget(dirLineEdit_2,4);
	lay1->addWidget(buttonDir_2);

	QHBoxLayout *lay2 = new QHBoxLayout;
	lay2->addWidget(imgLineEdit_2,4);
	lay2->addWidget(buttonImg_2);

	QVBoxLayout *layout1 = new QVBoxLayout;
	layout1->addLayout(lay1);
	layout1->addLayout(lay2);
	layout1->addWidget(prxLineEdit_2);
	layout1->addWidget(ptrLineEdit_2);

	QVBoxLayout *layout2 = new QVBoxLayout;
	layout2->addWidget(labelDir_2);
	layout2->addWidget(labelFile_2);
	layout2->addWidget(labelPrefix_2);
	layout2->addWidget(labelPattern_2);

	QHBoxLayout *layout3 = new QHBoxLayout;
	layout3->addLayout(layout2);
	layout3->addLayout(layout1,4);

	QVBoxLayout *layout4 = new QVBoxLayout;
	layout4->addWidget(labellength);
	layout4->addWidget(labelheight);

	QVBoxLayout *layout5 = new QVBoxLayout;
	layout5->addWidget(spinBoxlength_2);
	layout5->addWidget(spinBoxheight_2);

	QHBoxLayout *layout6 = new QHBoxLayout;
	layout6->addWidget(labelImgNum_2);
	layout6->addWidget(spinBoxImg_2);

	QHBoxLayout *layout7 = new QHBoxLayout;
	layout7->addLayout(layout4);
	layout7->addLayout(layout5);

	QVBoxLayout *layout8 =new QVBoxLayout;
	layout8->addWidget(labelImgDim_2);
	layout8->addLayout(layout7);

	QGridLayout *laymain = new QGridLayout;
	laymain->addLayout(layout3,0,0,1,4);
	laymain->addLayout(layout6,1,2);
	laymain->addLayout(layout7,1,1);
	laymain->addLayout(layout8,1,0);
	main->setLayout(laymain);

	return main;
}
void LoadBMPPage::getFileNameA()
{
	QString bmpNameA = QFileDialog::getOpenFileName(this,tr("Seleccionar primera imagen"),".",tr("Imágenes (*.bmp)"));
	emit strFileNameA(bmpNameA);
}
void LoadBMPPage::getDirNameA()
{
	QString dir = QFileDialog::getExistingDirectory(this,tr("Seleciona directorio"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	
	emit strDirNameA(dir);
}
void LoadBMPPage::getFileNameB()
{
	QString bmpNameB = QFileDialog::getOpenFileName(this,tr("Seleccionar primera imagen"),".",tr("Imágenes (*.bmp)"));
	emit strFileNameB(bmpNameB);
}
void LoadBMPPage::getDirNameB()
{
	QString dir = QFileDialog::getExistingDirectory(this,tr("Seleciona directorio"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	
	emit strDirNameB(dir);
}
int LoadBMPPage::nextId() const
{
	return ProjectWizard::Page_Conclusion;
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Especifique un nombre al proyecto y de aceptar para iniciar la carga"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    bottomLabel = new QLabel(tr("Nombre del Proyecto:"));
	QLineEdit *outputDirLineEdit = new QLineEdit;
	outputDirLineEdit->setText(tr("ProyectoFusion"));
	registerField("outputDir*",outputDirLineEdit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
	layout->addWidget(outputDirLineEdit);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
	QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
}
