#include <QtWidgets>

#include <QApplication>
#include <QDir>
#include "../src/blProject/controller/blProjectWidget.h"
#include "../src/blProject/model/blProjectAccess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // connect to database
    blProjectAccess* projectAccess = blProjectAccess::instance();
    projectAccess->setDatabaseFile("C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\projects\\projectDatabase.db");
    projectAccess->load();

    // widget
    QString viewerDir = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\viewers\\";
    QString binariesDir = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\bin\\";
    blProjectWidget w(viewerDir, binariesDir);
    w.setProjectsRootPath("C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\projects\\");
    w.show();

    QString styleFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\default\\stylesheet.css";
    a.setStyleSheet("file:///" + styleFile);
    return a.exec();
}
