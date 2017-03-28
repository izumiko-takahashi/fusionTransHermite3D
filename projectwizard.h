#ifndef PROJECTWIZARD_H
#define PROJECTWIZARD_H

#include <QWizard>
#include <QtGui>

class QCheckBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QSpinBox;
class QDoubleSpinBox;

//! [0] //! [1]
class ProjectWizard : public QWizard
{
    Q_OBJECT

public:
    enum { Page_Intro, Page_LoadDICOM, Page_LoadRAW,Page_LoadBMP,
           Page_Conclusion };

    ProjectWizard(QWidget *parent);
	QFile *projectFile;
	void accept();
	void writeInFile();

private slots:
    void showHelp();
signals:
	void fileReady(const QString &outputFile);

};
//! [1] //! [3]

//! [4]
class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *topLabel;
    QRadioButton *dcmRadioButton;
    QRadioButton *rawRadioButton;
	QRadioButton *bmpRadioButton;	
};
//! [4]

//! [5]
class LoadDICOMPage : public QWizardPage
{
    Q_OBJECT

public:
    LoadDICOMPage(QWidget *parent = 0);

    int nextId() const;
public slots:
	void getDirNameA();
	void getDirNameB();
private:
    QLabel *vol1Label;
    QLabel *vol2Label;
    QLineEdit *vol1LineEdit;
    QLineEdit *vol2LineEdit;
signals:
	void strDirNameA(QString dirNameA);
	void strDirNameB(QString dirNameB);
};

class LoadRAWPage : public QWizardPage
{
    Q_OBJECT

public:
    LoadRAWPage(QWidget *parent = 0);
	QGroupBox *groupBox();
	QGroupBox *groupBox2();

    int nextId() const;
private:
	QLabel *labelA;
	QLabel *prefixA;
	QLabel *dimA;
	QLabel *indexA;
	QLineEdit *vol1LineEdit;

	QLabel *labelB;
	QLabel *prefixB;
	QLabel *dimB;
	QLabel *indexB;
	QLineEdit *vol2LineEdit;

	QSpinBox *sizeX;
	QSpinBox *sizeY;

	QSpinBox *sizeX_2;
	QSpinBox *sizeY_2;
	
	QDoubleSpinBox *espX;
	QDoubleSpinBox *espY;
	QDoubleSpinBox *espZ;

	QDoubleSpinBox *espX_2;
	QDoubleSpinBox *espY_2;
	QDoubleSpinBox *espZ_2;

	QSpinBox *firstImageIndex;
	QSpinBox *lastImageIndex;

	QSpinBox *firstImageIndex_2;
	QSpinBox *lastImageIndex_2;
    
};
class LoadBMPPage : public QWizardPage
{
    Q_OBJECT

public:
    LoadBMPPage(QWidget *parent = 0);
	QGroupBox *groupBoxBMP();
	QGroupBox *groupBoxBMP_2();
    int nextId() const;
public slots:
	void getFileNameA();
	void getDirNameA();	
	void getFileNameB();
	void getDirNameB();	
private:
	QLabel *labelDir;
	QLabel *labelFile;
	QLabel *labelPrefix;
	QLabel *labelPattern;
	QLabel *labelImgDim;
	QLabel *labelImgNum;
	QLineEdit *dirLineEdit;
	QLineEdit *imgLineEdit;
	QLineEdit *prxLineEdit;
	QLineEdit *ptrLineEdit;
	QPushButton *buttonDir;
	QPushButton *buttonImg;
	QSpinBox *spinBoxlength;
	QSpinBox *spinBoxheight;
	QSpinBox *spinBoxImg;
	QLabel *labelDir_2;
	QLabel *labelFile_2;
	QLabel *labelPrefix_2;
	QLabel *labelPattern_2;
	QLabel *labelImgDim_2;
	QLabel *labelImgNum_2;
	QLineEdit *dirLineEdit_2;
	QLineEdit *imgLineEdit_2;
	QLineEdit *prxLineEdit_2;
	QLineEdit *ptrLineEdit_2;
	QPushButton *buttonDir_2;
	QPushButton *buttonImg_2;
	QSpinBox *spinBoxlength_2;
	QSpinBox *spinBoxheight_2;
	QSpinBox *spinBoxImg_2;
signals:
	void strDirNameA(const QString dirNameA);
	void strFileNameA(const QString fileNameA);
	void strDirNameB(const QString dirNameB);
	void strFileNameB(const QString fileNameB);
};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    void initializePage();
private:
    QLabel *bottomLabel;
};
//! [6]

#endif
