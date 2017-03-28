#include <QtGui>
#include <QFileDialog>
#include "LoadFile.h"

//! [0]
LoadFile::LoadFile(){}
QWidget *LoadFile::myWindow(int vol)
{
	this->Vol = vol;
	stackType = new QStackedWidget;
	stackType->addWidget(groupBoxDICOM());
	stackType->addWidget(groupBoxRAW());
	stackType->addWidget(groupBoxBMP());
	
	controlGroup = new QGroupBox("Tipo de formato");
	QGridLayout *grid = new QGridLayout;

	chooseType = new QComboBox;
	chooseType->addItem(tr("Cargar en formato DICOM"));
	chooseType->addItem(tr("Cargar en formato RAW"));
	chooseType->addItem(tr("Cargar en formato BMP"));
	grid->addWidget(chooseType,0,0,1,3);
	grid->addWidget(stackType,1,0,1,5);
	controlGroup->setLayout(grid);
	setLayout(grid);
	
	connect(chooseType,SIGNAL(activated(int)),stackType,SLOT(setCurrentIndex(int)));
}

QGroupBox *LoadFile::groupBoxDICOM()
{
    QGroupBox *groupBox = new QGroupBox("DICOM");
	QLabel *title = new QLabel(tr("&Nombre:"));
	QLineEdit *dirVol1 = new QLineEdit;
	title->setBuddy(dirVol1);
	dirVol1->setToolTip(tr("Dirección del conjunto de imagenes"));
	QPushButton *bdirVol1 = new QPushButton("...",this);
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(title,0,0,1,2);
	layout->addWidget(dirVol1,1,0,1,3);
	layout->addWidget(bdirVol1,1,2,1,1);
	groupBox->setLayout(layout);
	connect(bdirVol1,SIGNAL(clicked()),this,SLOT(getDirName()));
    connect(dirVol1,SIGNAL(textChanged(const QString)),this,SLOT(setDirName(const QString)));
	connect(this,SIGNAL(strDirName(const QString)),dirVol1,SLOT(setText(const QString)));
    return groupBox;
}
QGroupBox *LoadFile::groupBoxRAW()
{
	QGroupBox *groupBox = new QGroupBox("RAW");
	QLineEdit *dirVol1 = new QLineEdit;
	QLabel *name = new QLabel("&Nombre:");
	name->setBuddy(dirVol1);
	QLabel *prefix = new QLabel("Espaciamiento:");
	QLabel *dim = new QLabel("Dimensión de la Imagen:");
	QLabel *index = new QLabel(tr("Indices del Conjunto:"));

	QPushButton *bdirVol1 = new QPushButton("...",this);

	QSpinBox *sizeX = new QSpinBox();
	sizeX->setRange(1,65536);
	sizeX->setSingleStep(20);
	sizeX->setValue(32);
	QSpinBox *sizeY = new QSpinBox();
	sizeY->setRange(sizeX->minimum()+1,65536);
	sizeY->setSingleStep(20);
	sizeY->setValue(32);
	QDoubleSpinBox *espX = new QDoubleSpinBox();
	espX->setRange(0.01,12.99);
	espX->setValue(0.01);
	QDoubleSpinBox *espY = new QDoubleSpinBox();
	espY->setRange(0.01,12.99);
	espY->setValue(0.01);
	QDoubleSpinBox *espZ = new QDoubleSpinBox();
	espZ->setRange(0.01,12.99);
	espZ->setValue(0.01);
	QSpinBox *firstImageIndex = new QSpinBox();
	firstImageIndex->setRange(0,10);
	firstImageIndex->setValue(0);
	QSpinBox *lastImageIndex = new QSpinBox();
	lastImageIndex->setRange(firstImageIndex->minimum()+1,400);
	lastImageIndex->setValue(10);

    QGridLayout *layout = new QGridLayout;
		layout->addWidget(name,0,0,1,2);
		layout->addWidget(dirVol1,0,1,1,3);
		layout->addWidget(bdirVol1,0,4,1,1);

		layout->addWidget(dim,1,0,1,2);
		layout->addWidget(sizeX,2,0);
		layout->addWidget(sizeY,3,0);

		layout->addWidget(prefix,1,2,1,2);
		layout->addWidget(espX,2,2);
		layout->addWidget(espY,3,2);
		layout->addWidget(espZ,4,2);

		layout->addWidget(index,1,4,1,2);
		layout->addWidget(firstImageIndex,2,4);
		layout->addWidget(lastImageIndex,3,4);
	groupBox->setLayout(layout);

	connect(dirVol1,SIGNAL(textChanged(const QString)),this,SLOT(setDirName(const QString)));
	connect(this,SIGNAL(strDirName(const QString)),dirVol1,SLOT(setText(const QString)));
	connect(sizeX,SIGNAL(valueChanged(int)),this,SLOT(setDimU(int)));
	connect(sizeY,SIGNAL(valueChanged(int)),this,SLOT(setDimV(int)));
	connect(espX,SIGNAL(valueChanged(double)),this,SLOT(setSpaceX(double)));
	connect(espY,SIGNAL(valueChanged(double)),this,SLOT(setSpaceY(double)));
	connect(espZ,SIGNAL(valueChanged(double)),this,SLOT(setSpaceZ(double)));
	connect(firstImageIndex,SIGNAL(valueChanged(int)),this,SLOT(setFirstIndex(int)));
	connect(lastImageIndex,SIGNAL(valueChanged(int)),this,SLOT(setLastIndex(int)));
	return groupBox;
}
QGroupBox *LoadFile::groupBoxBMP()
{
	QGroupBox *g  = new QGroupBox("BMP");
	QLabel *tex = new QLabel(tr("&Directorio:"));
	QLineEdit *dir = new QLineEdit;
	tex->setBuddy(dir);
	QPushButton *bDir = new QPushButton("...",this);
	QLabel *tex2 = new QLabel(tr("&Primera imagen"));
	QLineEdit *img = new QLineEdit;
	tex2->setBuddy(img);
	QPushButton *bimg = new QPushButton("...",this);
	QLabel *tex3 = new QLabel(tr("Prefijo:"));
	QLineEdit *prx = new QLineEdit;
	QLabel *tex4 = new QLabel(tr("Patrón:"));
	QLineEdit *pattern = new QLineEdit;
	QLabel *tex5 = new QLabel(tr("Dimensiones -- número de imágenes"));
	QSpinBox *xbeg = new QSpinBox();
	QSpinBox *xend = new QSpinBox();
	QSpinBox *ybeg = new QSpinBox();
	QSpinBox *yend = new QSpinBox();
	QSpinBox *imgb = new QSpinBox();
	QSpinBox *imge = new QSpinBox();
	QGridLayout *ly = new QGridLayout;
	ly->addWidget(tex,0,0);
	ly->addWidget(dir,0,1);
	ly->addWidget(bDir,1,2);
	ly->addWidget(tex2,1,0);
	ly->addWidget(img,1,1);
	ly->addWidget(bimg,1,2);
	ly->addWidget(tex3,2,0);
	ly->addWidget(prx,2,1);
	ly->addWidget(tex4,3,0);
	ly->addWidget(pattern,3,1);
	ly->addWidget(tex5,4,0);
	ly->addWidget(xbeg,4,1);
	ly->addWidget(ybeg,4,2);
	ly->addWidget(imgb,4,3);
	ly->addWidget(xend,5,1);
	ly->addWidget(yend,5,2);
	ly->addWidget(imge,5,3);
	g->setLayout(ly);
	connect(bDir,SIGNAL(clicked()),this,SLOT(getDirName()));
    connect(dir,SIGNAL(textChanged(const QString)),this,SLOT(setDirName(const QString)));
	connect(this,SIGNAL(strDirName(const QString)),dir,SLOT(setText(const QString)));
	connect(bimg,SIGNAL(clicked()),this,SLOT(getFileName()));
	connect(img,SIGNAL(textChanged(const QString)),this,SLOT(setFileName(const QString)));
	connect(this,SIGNAL(strFileName(const QString)),img,SLOT(setText(const QString)));
	connect(prx,SIGNAL(textChanged(const QString)),this,SLOT(setPrefix(const QString)));
	connect(pattern,SIGNAL(textChanged(const QString)),this,SLOT(setPattern(const QString)));
	connect(xbeg,SIGNAL(valueChanged(int)),this,SLOT(setDimU(int)));
	connect(xend,SIGNAL(valueChanged(int)),this,SLOT(setDimW(int)));
	connect(ybeg,SIGNAL(valueChanged(int)),this,SLOT(setDimV(int)));
	connect(yend,SIGNAL(valueChanged(int)),this,SLOT(setDimVW(int)));
	connect(imgb,SIGNAL(valueChanged(int)),this,SLOT(setFirstIndex(int)));
	connect(imge,SIGNAL(valueChanged(int)),this,SLOT(setLastIndex(int)));
    return g;
	
}
/*void LoadFile::sendParameter()
{
	std::string n;
	std::string fl;
	std::string pfx;
	std::string ptr;
	int u,v,a,b,op,w,vw;
	float x,y,z;
	n = this->dirName;
	fl = this->fileName;
	pfx = this->prefix;
	ptr = this->pattern;
	x= spX;
	y=spY;
	z=spZ;
	u=dimu;
	v=dimv;
	vw=dimvw;
	w=dimw;
	a=stIdx;
	b=sdIdx;
	op = Vol;

	if(stackType->currentIndex() == 2)
	{
		emit fileBMP(n,fl,pfx,ptr,u,w,v,vw,a,b,op);
	}
	else
		if(stackType->currentIndex() == 1)
		{
			emit fileRAW(n,x,y,z,u,v,a,b,op);
		}
		else
			if(stackType->currentIndex() == 0)
			{
				emit fileDICOM(n,op);
			}
}*/
/*void LoadFile::whichVol(int op)
{
	//std::cout<<op<<std::endl;
	Vol = op;
}*/
void LoadFile::setDirName(const QString &name)
{
	this->dirName = name.toStdString();
}
void LoadFile::setFileName(const QString &name)
{
	this->fileName = name.toStdString();
}
void LoadFile::setPrefix(const QString &name)
{
	this->prefix = name.toStdString();
}
void LoadFile::setPattern(const QString &name)
{
	this->pattern = name.toStdString();
}
void LoadFile::setSpaceX(double x)
{
	this->spX =(float) x;
	//std::cout<<spX<<std::endl;
}
void LoadFile::setSpaceY(double y)
{
	this->spY =(float) y;
	//std::cout<<spY<<std::endl;
}

void LoadFile::setSpaceZ(double z)
{
	this->spZ =(float) z;
	//std::cout<<spZ<<std::endl;
}
void LoadFile::setDimU(int u)
{
	this->dimu = u;
	//std::cout<<dimu<<std::endl;
}
void LoadFile::setDimV(int v)
{
	this->dimv = v;
	//std::cout<<dimv<<std::endl;
}
void LoadFile::setDimW(int w)
{
	this->dimw = w;
	//std::cout<<dimw<<std::endl;
}
void LoadFile::setDimVW(int vw)
{
	this->dimvw = vw;
	//std::cout<<dimvw<<std::endl;
}
void LoadFile::setFirstIndex(int f)
{
	this->stIdx = f;
	//std::cout<<stIdx<<std::endl;
}
void LoadFile::setLastIndex(int g)
{
	this->sdIdx = g;
	//std::cout<<sdIdx<<std::endl;
}
void LoadFile::getDirName()
{
	QString dir = QFileDialog::getExistingDirectory(this,tr("Seleciona directorio"),".",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	
	emit strDirName(dir);

}
void LoadFile::getFileName()
{
	QString bmpName = QFileDialog::getOpenFileName(this,tr("Seleccionar primera imagen"),".",tr("Imágenes (*.bmp)"));
	emit strFileName(bmpName);
}