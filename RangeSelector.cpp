#include "RangeSelector.h"
#include <QtGui>
#include <QImage>
#include <QPixmap>

inline int MIN(int a,int b) {return a<=b ? a : b; }
inline int MAX(int a,int b) {return a>=b ? a : b; }

RangeSelector::RangeSelector(QWidget *parent)
	:QWidget(parent)
{
	this->setupUi(this);
	m_mean = 128;
	m_range = 128;
	/*connect(dialWidthSelector,SIGNAL(valueChanged(int)),this,SLOT(calculateRamp(int)));*/
	this->label->setPixmap(QPixmap(":/images/histogram.png"));	
	connect(dialCenterSelector,SIGNAL(valueChanged(int)),this,SLOT(setMeanGrayValue(int)));
	connect(dialWidthSelector,SIGNAL(valueChanged(int)),this,SLOT(setRangeValue(int)));
	connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(setMeanGrayValue(int)));
	connect(pushButtonApply,SIGNAL(clicked()),this,SLOT(sendParameter()));
	this->setMaximumSize(300,400);
}
void RangeSelector::setMeanGrayValue(int val)
{
	m_mean = val;
}
void RangeSelector::setRangeValue(int val)
{
	m_range = val;
}
void RangeSelector::calculateRamp(int val)
{
	int left = MAX(dialCenterSelector->value() - val,1);
	int right= MIN(dialCenterSelector->value() + val,2048);

	QColor rgbCol;

	/*QPainter rangeCol;
	rangeCol.setBrush(QColor(102,255,255,127));	*/
	/*int left = MAX(dialCenterSelector->value() - dialWidthSelector->value(),0);
	int	right= MIN(dialCenterSelector->value() + dialWidthSelector->value(),4095);*/

	left = (int)2048/(256*left);
	right = (int)2048/(256*right);

	QImage imgAux(256,100,QImage::Format_ARGB32);
	
	for(int c=0;c<left;c++)
	{
		for(int d=0;d<100;d++)
		{
			rgbCol.setRgb(102,255,255);
			rgbCol.setRgba(127);
			imgAux.setPixel(c,d,rgbCol.rgba());
		}
	}

	for(int e=left + 1; e < right; e++)
	{
		for(int f=0;f<100;f++)
		{
			rgbCol.setRgb(102,255,255);
			rgbCol.setAlpha(8);
			imgAux.setPixel(e,f,rgbCol.rgb());
		}
	}
	rgbCol.setRgb(102,102,153);
	rgbCol.setAlpha(127);
	for(int h=0;h<100;h++)
	{
		imgAux.setPixel(left,h,rgbCol.rgba());
		imgAux.setPixel(right,h,rgbCol.rgba());
	}
	

	for(int j=right;j<256;j++)
	{
		for(int k=0;k<100;k++)
		{
			rgbCol.setRgb(204, 204,51);
			rgbCol.setAlpha(127);
			imgAux.setPixel(j,k,rgbCol.rgba());
		}
	} 
	QImage histo(":images/histogram.png");
	//histo.scaled(imgAux.width(),imgAux.height());
	imgAux.setAlphaChannel(histo.scaled(imgAux.width(),imgAux.height()));
	this->label->setPixmap(QPixmap::fromImage(imgAux.scaled(label->width(),label->height())));
	
}
void RangeSelector::limitedRange(int val)
{
	dialWidthSelector->setRange(1,val%2);
	spinBox_2->setRange(1,val%2);
}
void RangeSelector::sendParameter()
{
	if(((m_mean - m_range) >= 0) && ((m_mean + m_range) <= 4096))
	{
		emit mean_Range(m_mean,m_range);
	}
	else 
	{
		QMessageBox::warning(this,tr("Error en el rango"),tr("Este no es rango no puede exceder la mitad del centro establecido"));
	}
}
