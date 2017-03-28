#ifndef _LOADFILE_H_
#define _LOADFILE_H_

#include <QWidget>
#include <string>
class QGroupBox;
class QComboBox;
class QStackedWidget;
class QString;

class LoadFile : public QWidget 
{
	Q_OBJECT
public:
	LoadFile();
	int Vol;
	std::string fileName,dirName,prefix,pattern;
	float spX,spY,spZ;
	int dimu,dimv,stIdx,sdIdx,dimvw,dimw;

	//Members
	QComboBox *chooseType;
	QGroupBox *controlGroup;
	QStackedWidget *stackType;
	//Methods
	QWidget *myWindow(int vol);
	QGroupBox *groupBoxDICOM();
	QGroupBox *groupBoxRAW();
	QGroupBox *groupBoxBMP();
public slots:
	/*void sendParameter();*/
	/*void whichVol(int op);*/
	void setDirName(const QString &name);
	void setFileName(const QString &name);
	void setPrefix(const QString &name);
	void setPattern(const QString &name);
	void setSpaceX(double x);
	void setSpaceY(double y);
	void setSpaceZ(double z);
	void setDimU(int u);
	void setDimV(int v);
	void setDimW(int w);
	void setDimVW(int vw);
	void setFirstIndex(int f);
	void setLastIndex(int g);
	void getFileName();
	void getDirName();	
signals:
	void fileRAW(std::string name, float spaceX, float spaceY, float spaceZ,int imaX,int imaY,int first, int last,int op);
	void fileDICOM(std::string name,int op);
	void strDirName(QString dirName);
	void strFileName(QString fileName);
	void fileBMP(std::string dir, std::string fileNam, std::string prefix, std::string pattern, int xbeg,int xend,int ybeg, int yend,int imgb,int imge,int op);
};

#endif

