#include "WizardLoadFile.h"
//#include "LoadFile.h"
#include <QtGui>
#include <QFile>	
#include <string>

WizardLoadFile::WizardLoadFile(QWidget *parent)
	: QWizard(parent)
{
	//addPage(new IntroPage);
	addPage(new InfoPageVol1);
	addPage(new InfoPageVol2);
	//addPage(new ConclusionPage);

	setWindowTitle(tr("Selecci�n y carga de los volumenes a fusionar"));

}
void WizardLoadFile::accept()
{

	QDialog::accept();
}
/*IntroPage::IntroPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Fusi�n de vol�menes usando la transformada discreta de Hermite"));
    label = new QLabel(tr("A trav�s de esta ventana realizaremos la carga de "
                          "las imag�nes m�dicas que posteriormente se visualiza- "
                          "ran como un volumen en su pantalla."
                          "Posteriormente se realizar� la especificaci�n de los "
                          "par�metros para efectuar la fusi�n de sus vol�menes"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}*/
InfoPageVol1::InfoPageVol1(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Carga de im�genes correspondientes al volumen 1."));
	QVBoxLayout *layout = new QVBoxLayout;
	pageVol1 = new LoadFile();
	int dimu = pageVol1->dimu;
	int dimv = pageVol1->dimv;
	int dimvw = pageVol1->dimvw;
	int dimw = pageVol1->dimw;
	float spacingX = pageVol1->spX;
	float spacingY = pageVol1->spY;
	float spacingZ = pageVol1->spZ;
	std::string dir = pageVol1->dirName;
	std::string file = pageVol1->fileName;
	std::string prfx = pageVol1->prefix;
	std::string ptrn = pageVol1->pattern;

	layout->addWidget(pageVol1);
    setLayout(layout);

	/*QFile file("proyecto.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		QMessageBox::warning(0,tr("Simple Wizard"),
                             tr("Cannot write file %1:\n%2"));
         return;
	}
    file*/

}
InfoPageVol2::InfoPageVol2(int volume, QWidget *parent)
	: QWizardPage(parent), 
	  LoadFile()
{
	setTitle(tr("Carga im�genes correspondientes al volumen 2."));
	
	
}
/*ConclusionPage::ConclusionPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Conclusion"));
    
    label = new QLabel;
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}
void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 para generar los vol�menes.")
                   .arg(finishText));
}
*/