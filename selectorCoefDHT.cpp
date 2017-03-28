#include "selectorCoefDHT.h"
#include <iostream>


SelectorCoefDHT::SelectorCoefDHT(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	rbOriginal->setChecked(true);
	setConection();
}
void SelectorCoefDHT::loadCoef000(bool toggle)
{
	if(toggle)
		emit sendOption("000");
}
void SelectorCoefDHT::loadCoef010(bool toggle)
{
	if(toggle)
		emit sendOption("010");
}
void SelectorCoefDHT::loadCoef100(bool toggle)
{
	if(toggle)
		emit sendOption("100");
}
void SelectorCoefDHT::loadCoef001(bool toggle)
{
	if(toggle)
		emit sendOption("001");
}
void SelectorCoefDHT::loadGradient(bool toggle)
{
	if(toggle)
		emit sendOption("Gradient");
}
void SelectorCoefDHT::loadCoef110(bool toggle)
{	
	if(toggle)
		emit sendOption("110");
}
void SelectorCoefDHT::loadCoef101(bool toggle)
{			
	if(toggle)
		emit sendOption("101");
}
void SelectorCoefDHT::loadCoef011(bool toggle)
{	
	if(toggle)	
		emit sendOption("011");
}
void SelectorCoefDHT::loadCoef200(bool toggle)
{
	if(toggle)
		emit sendOption("200");
}
void SelectorCoefDHT::loadCoef020(bool toggle)
{		
	if(toggle)
		emit sendOption("020");
}
void SelectorCoefDHT::loadCoef002(bool toggle)
{
	if(toggle)
	 emit sendOption("002");
}
void SelectorCoefDHT::restartVolume(bool on)
{
	if(on)
	emit sendOption("volume");	
}
void SelectorCoefDHT::setConection()
{
	connect(rbOriginal,SIGNAL(toggled(bool)),this,SLOT(restartVolume(bool)));
	connect(rb000,SIGNAL(toggled(bool)),this,SLOT(loadCoef000(bool)));
	connect(rb010,SIGNAL(toggled(bool)),this,SLOT(loadCoef010(bool)));
	connect(rb100,SIGNAL(toggled(bool)),this,SLOT(loadCoef100(bool)));
	connect(rb001,SIGNAL(toggled(bool)),this,SLOT(loadCoef001(bool)));
	connect(rb110,SIGNAL(toggled(bool)),this,SLOT(loadCoef110(bool)));
	connect(rb101,SIGNAL(toggled(bool)),this,SLOT(loadCoef101(bool)));
	connect(rb020,SIGNAL(toggled(bool)),this,SLOT(loadCoef020(bool)));
	connect(rb011,SIGNAL(toggled(bool)),this,SLOT(loadCoef011(bool)));
	connect(rb002,SIGNAL(toggled(bool)),this,SLOT(loadCoef002(bool)));
	connect(rb200,SIGNAL(toggled(bool)),this,SLOT(loadCoef200(bool)));
	connect(rbGradient,SIGNAL(toggled(bool)),this,SLOT(loadGradient(bool)));
}

