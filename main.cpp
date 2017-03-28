#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "QVTKApplication.h"
#include "mainwindow.h"
#include "ProjectWizard.h"

int main(int argc, char **argv)
{
	QVTKApplication app(argc,argv);
	QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(translator);
	app.setApplicationName("Fusion3D");
	app.setApplicationVersion("version 0.5");
	app.setOrganizationName("LAPI UNAM");
	Mainwindow win;
	win.showMaximized();
	return app.exec();
}