#ifndef _RGBSEGMENT_H_
#define _RGBSEGMENT_H_

#include <QWidget>
#include <QtGui\QColor>
#include <QtCore\QSignalMapper>
#include "ui_RGBSegment.h"
#include "ColorSegment.h"

class RGBSegment : public QWidget,public Ui::RGBSegment
{
	Q_OBJECT
public:
	RGBSegment(QWidget *parent = 0);
	~RGBSegment();
private slots:
	void slotSetLabelColor(QWidget * widget);
	void sendParameter();
private:
	QSignalMapper signalm;
	void setConnections();
signals:
	void colorChanged(QColor color);
	void segment(std::vector<ColorSegment> *colors);
	
};

#endif