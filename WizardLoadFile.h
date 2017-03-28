#ifndef WIZARDLOADFILE_H
#define WIZARDLOADFILE_H

#include <QWizard>
#include "LoadFile.h"
class LoadFile;
class QLabel;
class QVBoxLayout;
class WizardLoadFile : public QWizard
{
	Q_OBJECT

public:
	WizardLoadFile(QWidget *parent);
	void accept();
};
/*class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};
*/
class InfoPageVol1 : public QWizardPage
{
    Q_OBJECT

public:
	InfoPageVol1(QWidget *parent = 0);

private:
	LoadFile *pageVol1;
   
};
class InfoPageVol2 : public QWizardPage, public LoadFile
{
	Q_OBJECT
public:
	InfoPageVol2(int volume= 2, QWidget *parent = 0);
private:
   
};
/*class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

protected:
    void initializePage();

private:
    QLabel *label;
};
*/
#endif