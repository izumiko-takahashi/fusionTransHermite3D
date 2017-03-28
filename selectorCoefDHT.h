#ifndef _SELECTORCOEFDHT_H_
#define _SELECTORCOEFDHT_H_

#include <QtGui>
#include <QStringList>
#include <QtCore/QSignalMapper>
#include "ui_selectorCoefDHT.h"

class SelectorCoefDHT : public QWidget, public Ui::selectorCoefDHT
{
	Q_OBJECT
public:
	SelectorCoefDHT(QWidget *parent = 0);
private:
	QSignalMapper signalMapper;
	void setConection();
private slots:
	void loadCoef000(bool toggle);
	void loadCoef010(bool toggle);
	void loadCoef100(bool toggle);
	void loadCoef001(bool toggle);
	void loadGradient(bool toggle);
	void loadCoef110(bool toggle);
	void loadCoef101(bool toggle);
	void loadCoef011(bool toggle);
	void loadCoef200(bool toggle);
	void loadCoef020(bool toggle);
	void loadCoef002(bool toggle);
	void restartVolume(bool on);
signals:
	void sendOption(const QString coef);
};

#endif