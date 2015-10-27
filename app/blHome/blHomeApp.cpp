#include <QtWidgets>

#include <QApplication>
#include <QDir>
#include "../src/blHome/controller/blHomeDefaultWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // widget
    QString iconsDir = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme";
    blHomeDefaultWidget w(iconsDir);
    w.setSettingsUrl("C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\settings.bl");
    w.show();

    QString styleFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\stylesheet.css";
    a.setStyleSheet("file:///" + styleFile);
    return a.exec();
}
