#include <QtWidgets>

#include <QApplication>
#include <QDir>
#include "bioseController.h"
#include <blFinder>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // widget
    QString iconsDir = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\default\\";
    QString settingsUrl = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\settings.db";
    bioseController w(settingsUrl, iconsDir);

    w.setWindowTitle("Biose");
    w.show();


    QRect rec = QApplication::desktop()->screenGeometry();
    w.resize(0.8*rec.width(), 0.8*rec.height());
    a.setWindowIcon(QIcon(iconsDir + "icon.png"));
    w.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            qApp->desktop()->availableGeometry()
        ));

    blHomeSettingsGroups settings;
    settings.load(settingsUrl);
    QString styleFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\default\\stylesheet.css";
    QFile file(settings.value("Home", "stylesheet"));
    if (file.exists()){
        styleFile = settings.value("Home", "stylesheet");
    }
    a.setStyleSheet("file:///" + styleFile);


    return a.exec();
}
