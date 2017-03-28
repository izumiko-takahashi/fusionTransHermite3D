#ifndef _RANGESELECTOR_H_
#define _RANGESELECTOR_H_
#include <QWidget>

#include "ui_RangeSelector.h"

class RangeSelector : public QWidget, public Ui::RangeSelector
{
	Q_OBJECT
public:
	int m_mean;
	int m_range;
	RangeSelector(QWidget *parent);
public slots:
	void sendParameter();
	void setMeanGrayValue(int val);
	void setRangeValue(int val);
//protected:
//	void mousePressEvent(QMouseEvent * event);
	//void updateImageHistogram();
private slots:
	void calculateRamp(int val);
	void limitedRange(int val);
	
signals:
	void mean_Range(int mean,int range);
};
#endif