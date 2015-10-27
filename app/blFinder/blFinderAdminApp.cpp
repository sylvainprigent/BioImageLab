#include <QtWidgets>

#include <QApplication>
#include <QDir>
#include "../src/blFinder/controller/blFinderAdminDefaultWidget.h"
#include "../src/blFinder/model/blFinderAccess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize the database
    blFinderAccess *database = blFinderAccess::instance();
    database->setDatabaseFile("C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\finder_database.db");
    database->load();
    //database->database()->addTestEntries();

    // widget
    blFinderAdminDefaultWidget w;
    w.show();

    QString styleFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\stylesheet.css";
    a.setStyleSheet("file:///" + styleFile);
    return a.exec();
}
