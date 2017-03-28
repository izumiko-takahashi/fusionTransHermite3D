#include "RGBSegment.h"
#include <QtGui>
#include <QtCore\QSignalMapper>
#include "ColorSegment.h"

RGBSegment::RGBSegment(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
	setConnections();
	connect(pbAccept,SIGNAL(clicked()),this,SLOT(sendParameter()));
	connect(pbAccept,SIGNAL(clicked()),this,SLOT(close()));
	connect(pbCancel,SIGNAL(clicked()),this,SLOT(close()));
}
RGBSegment::~RGBSegment()
{
}
void RGBSegment::slotSetLabelColor(QWidget * widget)	
{
	QColorDialog dialog;
	QColor color = dialog.getColor(Qt::blue,this);
	if(color.isValid() && dialog.Accepted)
	{
		emit colorChanged(color);
		widget->setPalette(QPalette(color));
		widget->setAutoFillBackground(true);

	}
}
void RGBSegment::setConnections()
{
	signalm.setMapping(pbColorDialogx,lcolorx); 
	signalm.setMapping(pbColorDialogy,lcolory);
	signalm.setMapping(pbColorDialogxa,lcolora2);
	signalm.setMapping(pbColorDialogya,lcolorb2);
	signalm.setMapping(pbColorDialogxb,lcolorc2);
	signalm.setMapping(pbColorDialogyb,lcolord2);
	signalm.setMapping(pbColorDialoga3,lcolora3);
	signalm.setMapping(pbColorDialogb3,lcolorb3);
	signalm.setMapping(pbColorDialogc3,lcolorc3);
	signalm.setMapping(pbColorDialogd3,lcolord3);
	signalm.setMapping(pbColorDialoge3,lcolore3);
	signalm.setMapping(pbColorDialogf3,lcolorf3);
	signalm.setMapping(pbColorDialoga4,lcolora4);
	signalm.setMapping(pbColorDialogb4,lcolorb4);
	signalm.setMapping(pbColorDialogc4,lcolorc4);
	signalm.setMapping(pbColorDialogd4,lcolord4);
	signalm.setMapping(pbColorDialoge4,lcolore4);
	signalm.setMapping(pbColorDialogf4,lcolorf4);
	signalm.setMapping(pbColorDialogg4,lcolorg4);
	signalm.setMapping(pbColorDialogh4,lcolorh4);
	signalm.setMapping(pbColorDialoga5,lcolora5);
	signalm.setMapping(pbColorDialogb5,lcolorb5);
	signalm.setMapping(pbColorDialogc5,lcolorc5);
	signalm.setMapping(pbColorDialogc5,lcolorc5);
	signalm.setMapping(pbColorDialogd5,lcolord5);
	signalm.setMapping(pbColorDialoge5,lcolore5);
	signalm.setMapping(pbColorDialogf5,lcolorf5);
	signalm.setMapping(pbColorDialogg5,lcolorg5);
	signalm.setMapping(pbColorDialogh5,lcolorh5);
	signalm.setMapping(pbColorDialogi5,lcolori5);
	signalm.setMapping(pbColorDialogj5,lcolorj5);
	signalm.setMapping(pbColorDialoga6,lcolora6);
	signalm.setMapping(pbColorDialogb6,lcolorb6);
	signalm.setMapping(pbColorDialogc6,lcolorc6);
	signalm.setMapping(pbColorDialogc6,lcolorc6);
	signalm.setMapping(pbColorDialogd6,lcolord6);
	signalm.setMapping(pbColorDialoge6,lcolore6);
	signalm.setMapping(pbColorDialogf6,lcolorf6);
	signalm.setMapping(pbColorDialogg6,lcolorg6);
	signalm.setMapping(pbColorDialogh6,lcolorh6);
	signalm.setMapping(pbColorDialogi6,lcolori6);
	signalm.setMapping(pbColorDialogj6,lcolorj6);
	signalm.setMapping(pbColorDialogk6,lcolork6);
	signalm.setMapping(pbColorDialoga7,lcolora7);
	signalm.setMapping(pbColorDialogb7,lcolorb7);
	signalm.setMapping(pbColorDialogc7,lcolorc7);
	signalm.setMapping(pbColorDialogc7,lcolorc7);
	signalm.setMapping(pbColorDialogd7,lcolord7);
	signalm.setMapping(pbColorDialoge7,lcolore7);
	signalm.setMapping(pbColorDialogf7,lcolorf7);
	signalm.setMapping(pbColorDialogg7,lcolorg7);
	signalm.setMapping(pbColorDialogh7,lcolorh7);
	signalm.setMapping(pbColorDialogi7,lcolori7);
	signalm.setMapping(pbColorDialogj7,lcolorj7);
	signalm.setMapping(pbColorDialogk7,lcolork7);
	signalm.setMapping(pbColorDialogl7,lcolorl7);
	signalm.setMapping(pbColorDialogm7,lcolorm7);
	signalm.setMapping(pbColorDialogn7,lcolorn7);

	
	connect(pbColorDialogx,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogy,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogxa,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogya,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogxb,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogyb,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoga3,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogb3,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogc3,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogd3,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoge3,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogf3,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoga4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogb4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogc4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogd4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoge4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogf4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogg4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogh4,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoga5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogb5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogc5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogd5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoge5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogf5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogg5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogh5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogi5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogj5,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoga6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogb6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogc6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogd6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoge6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogf6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogg6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogh6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogi6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogj6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogk6,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoga7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogb7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogc7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogd7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialoge7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogf7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogg7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogh7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogi7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogj7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogk7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogl7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogm7,SIGNAL(clicked()),&signalm,SLOT(map()));
	connect(pbColorDialogn7,SIGNAL(clicked()),&signalm,SLOT(map()));
	
	connect(&signalm,SIGNAL(mapped(QWidget *)),this,SLOT(slotSetLabelColor(QWidget *)));
}
void RGBSegment::sendParameter()
{
	std::vector<ColorSegment> colors;
	int fin = comboBox->currentIndex() + 1;
	int min1,min2,min3,min4,min5,min6,min7;
	int max1,max2,max3,max4,max5,max6,max7;
	switch(fin)
	{
	case 1:
		min1 = sbx->value();
		max1 = sby->value();
		break;
	case 2:
		min1 = sbxa2->value();
		min2 = sbxb2->value();
		max1 = sbya2->value();
		max2 = sbyb2->value();
		break;
	case 3:
		min1 = sbxa3->value();
		min2 = sbxb3->value();
		min3 = sbxc3->value();
		max1 = sbya3->value();
		max2 = sbyb3->value();
		max3 = sbyc3->value();
		break;
	case 4:
		min1 = sbxa4->value();
		min2 = sbxb4->value();
		min3 = sbxc4->value();
		min4 = sbxd4->value();
		max1 = sbya4->value();
		max2 = sbyb4->value();
		max3 = sbyc4->value();
		max4 = sbyd4->value();
		break;
	case 5:
		min1 = sbxa5->value();
		min2 = sbxb5->value();
		min3 = sbxc5->value();
		min4 = sbxd5->value();
		min5 = sbxe5->value();
		max1 = sbya5->value();
		max2 = sbyb5->value();
		max3 = sbyc5->value();
		max4 = sbyd5->value();
		max5 = sbye5->value();
		break;
	case 6:
		min1 = sbxa6->value();
		min2 = sbxb6->value();
		min3 = sbxc6->value();
		min4 = sbxd6->value();
		min5 = sbxe6->value();
		min6 = sbxf6->value();
		max1 = sbya6->value();
		max2 = sbyb6->value();
		max3 = sbyc6->value();
		max4 = sbyd6->value();
		max5 = sbye6->value();
		max6 = sbyf6->value();
		break;
	case 7:
		min1 = sbxa7->value();
		min2 = sbxb7->value();
		min3 = sbxc7->value();
		min4 = sbxd7->value();
		min5 = sbxe7->value();
		min6 = sbxf7->value();
		min7 = sbxg7->value();
		max1 = sbya7->value();
		max2 = sbyb7->value();
		max3 = sbyc7->value();
		max4 = sbyd7->value();
		max5 = sbye7->value();
		max6 = sbyf7->value();
		max7 = sbyg7->value();
		break;
	default:
		QMessageBox::warning(this,tr("Error al capturar datos"),tr("Se produjo un error en la captura de datos. Inténtelo de nuevo."));
		return;
		break;
	}
	if(fin==1)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolorx->palette().window().color().redF(),
									lcolorx->palette().window().color().greenF(),
									lcolorx->palette().window().color().blueF(),
									lcolory->palette().window().color().redF(),
									lcolory->palette().window().color().greenF(),
									lcolory->palette().window().color().blueF());
		colors.push_back(c);
	}
	else if(fin==2)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolora2->palette().window().color().redF(),
									lcolora2->palette().window().color().greenF(),
									lcolora2->palette().window().color().blueF(),
									lcolorb2->palette().window().color().redF(),
									lcolorb2->palette().window().color().greenF(),
									lcolorb2->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min2,max2,
						lcolorc2->palette().window().color().redF(),
						lcolorc2->palette().window().color().greenF(),
						lcolorc2->palette().window().color().blueF(),
						lcolord2->palette().window().color().redF(),
						lcolord2->palette().window().color().greenF(),
						lcolord2->palette().window().color().blueF());
		colors.push_back(c);
	}
	else if(fin==3)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolora3->palette().window().color().redF(),
									lcolora3->palette().window().color().greenF(),
									lcolora3->palette().window().color().blueF(),
									lcolorb3->palette().window().color().redF(),
									lcolorb3->palette().window().color().greenF(),
									lcolorb3->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min2,max2,
						lcolorc3->palette().window().color().redF(),
						lcolorc3->palette().window().color().greenF(),
						lcolorc3->palette().window().color().blueF(),
						lcolord3->palette().window().color().redF(),
						lcolord3->palette().window().color().greenF(),
						lcolord3->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min3,max3,
						lcolore3->palette().window().color().redF(),
						lcolore3->palette().window().color().greenF(),
						lcolore3->palette().window().color().blueF(),
						lcolorf3->palette().window().color().redF(),
						lcolorf3->palette().window().color().greenF(),
						lcolorf3->palette().window().color().blueF());
		colors.push_back(c);
	}
	else if(fin==4)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolora4->palette().window().color().redF(),
									lcolora4->palette().window().color().greenF(),
									lcolora4->palette().window().color().blueF(),
									lcolorb4->palette().window().color().redF(),
									lcolorb4->palette().window().color().greenF(),
									lcolorb4->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min2,max2,
						lcolorc4->palette().window().color().redF(),
						lcolorc4->palette().window().color().greenF(),
						lcolorc4->palette().window().color().blueF(),
						lcolord4->palette().window().color().redF(),
						lcolord4->palette().window().color().greenF(),
						lcolord4->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min3,max3,
						lcolore4->palette().window().color().redF(),
						lcolore4->palette().window().color().greenF(),
						lcolore4->palette().window().color().blueF(),
						lcolorf4->palette().window().color().redF(),
						lcolorf4->palette().window().color().greenF(),
						lcolorf4->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min4,max4,
						lcolorg4->palette().window().color().redF(),
						lcolorg4->palette().window().color().greenF(),
						lcolorg4->palette().window().color().blueF(),
						lcolorh4->palette().window().color().redF(),
						lcolorh4->palette().window().color().greenF(),
						lcolorh4->palette().window().color().blueF());
		colors.push_back(c);
	}
	else if(fin==5)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolora5->palette().window().color().redF(),
									lcolora5->palette().window().color().greenF(),
									lcolora5->palette().window().color().blueF(),
									lcolorb5->palette().window().color().redF(),
									lcolorb5->palette().window().color().greenF(),
									lcolorb5->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min2,max2,
						lcolorc5->palette().window().color().redF(),
						lcolorc5->palette().window().color().greenF(),
						lcolorc5->palette().window().color().blueF(),
						lcolord5->palette().window().color().redF(),
						lcolord5->palette().window().color().greenF(),
						lcolord5->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min3,max3,
						lcolore5->palette().window().color().redF(),
						lcolore5->palette().window().color().greenF(),
						lcolore5->palette().window().color().blueF(),
						lcolorf5->palette().window().color().redF(),
						lcolorf5->palette().window().color().greenF(),
						lcolorf5->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min4,max4,
						lcolorf5->palette().window().color().redF(),
						lcolorf5->palette().window().color().greenF(),
						lcolorf5->palette().window().color().blueF(),
						lcolorg5->palette().window().color().redF(),
						lcolorg5->palette().window().color().greenF(),
						lcolorg5->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min5,max5,
						lcolorh5->palette().window().color().redF(),
						lcolorh5->palette().window().color().greenF(),
						lcolorh5->palette().window().color().blueF(),
						lcolori5->palette().window().color().redF(),
						lcolori5->palette().window().color().greenF(),
						lcolori5->palette().window().color().blueF());
		colors.push_back(c);
	}
	else if(fin==6)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolora6->palette().window().color().redF(),
									lcolora6->palette().window().color().greenF(),
									lcolora6->palette().window().color().blueF(),
									lcolorb6->palette().window().color().redF(),
									lcolorb6->palette().window().color().greenF(),
									lcolorb6->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min2,max2,
						lcolorc6->palette().window().color().redF(),
						lcolorc6->palette().window().color().greenF(),
						lcolorc6->palette().window().color().blueF(),
						lcolord6->palette().window().color().redF(),
						lcolord6->palette().window().color().greenF(),
						lcolord6->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min3,max3,
						lcolore6->palette().window().color().redF(),
						lcolore6->palette().window().color().greenF(),
						lcolore6->palette().window().color().blueF(),
						lcolorf6->palette().window().color().redF(),
						lcolorf6->palette().window().color().greenF(),
						lcolorf6->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min4,max4,
						lcolorg6->palette().window().color().redF(),
						lcolorg6->palette().window().color().greenF(),
						lcolorg6->palette().window().color().blueF(),
						lcolorh6->palette().window().color().redF(),
						lcolorh6->palette().window().color().greenF(),
						lcolorh6->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min5,max5,
						lcolori6->palette().window().color().redF(),
						lcolori6->palette().window().color().greenF(),
						lcolori6->palette().window().color().blueF(),
						lcolorj6->palette().window().color().redF(),
						lcolorj6->palette().window().color().greenF(),
						lcolorj6->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min6,max6,
						lcolork6->palette().window().color().redF(),
						lcolork6->palette().window().color().greenF(),
						lcolork6->palette().window().color().blueF(),
						lcolorl6->palette().window().color().redF(),
						lcolorl6->palette().window().color().greenF(),
						lcolorl6->palette().window().color().blueF());
		colors.push_back(c);
	}
	else if(fin==7)
	{
		ColorSegment c = ColorSegment(min1,max1,
									lcolora7->palette().window().color().redF(),
									lcolora7->palette().window().color().greenF(),
									lcolora7->palette().window().color().blueF(),
									lcolorb7->palette().window().color().redF(),
									lcolorb7->palette().window().color().greenF(),
									lcolorb7->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min2,max2,
						lcolorc7->palette().window().color().redF(),
						lcolorc7->palette().window().color().greenF(),
						lcolorc7->palette().window().color().blueF(),
						lcolord7->palette().window().color().redF(),
						lcolord7->palette().window().color().greenF(),
						lcolord7->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min3,max3,
						lcolore7->palette().window().color().redF(),
						lcolore7->palette().window().color().greenF(),
						lcolore7->palette().window().color().blueF(),
						lcolorf7->palette().window().color().redF(),
						lcolorf7->palette().window().color().greenF(),
						lcolorf7->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min4,max4,
						lcolorg7->palette().window().color().redF(),
						lcolorg7->palette().window().color().greenF(),
						lcolorg7->palette().window().color().blueF(),
						lcolorh7->palette().window().color().redF(),
						lcolorh7->palette().window().color().greenF(),
						lcolorh7->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min5,max5,
						lcolori7->palette().window().color().redF(),
						lcolori7->palette().window().color().greenF(),
						lcolori7->palette().window().color().blueF(),
						lcolorj7->palette().window().color().redF(),
						lcolorj7->palette().window().color().greenF(),
						lcolorj7->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min6,max6,
						lcolork7->palette().window().color().redF(),
						lcolork7->palette().window().color().greenF(),
						lcolork7->palette().window().color().blueF(),
						lcolorl7->palette().window().color().redF(),
						lcolorl7->palette().window().color().greenF(),
						lcolorl7->palette().window().color().blueF());
		colors.push_back(c);
		c = ColorSegment(min7,max7,
						lcolorm7->palette().window().color().redF(),
						lcolorm7->palette().window().color().greenF(),
						lcolorm7->palette().window().color().blueF(),
						lcolorn7->palette().window().color().redF(),
						lcolorn7->palette().window().color().greenF(),
						lcolorn7->palette().window().color().blueF());
		colors.push_back(c);
	}
	emit segment(&colors);
}