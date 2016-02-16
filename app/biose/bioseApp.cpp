#include <QtWidgets>

#include <QApplication>
#include <QDir>
#include "bioseController.h"
#include <blFinder>
#include "blCore/blSettingsAccess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // settings
    // load settings
    blSettingsAccess* settingsAccess = blSettingsAccess::instance();
    QString settingsFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\settings.db";
    settingsAccess->setSettingsFile(settingsFile);
    settingsAccess->load();

    //settingsAccess->settings()->add("Project", "Projects directory", "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\projects\\");
    //settingsAccess->settings()->save(settingsFile);

    // widget
    QString iconsDir = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\default\\";
    QString settingsUrl = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\settings.db";
    QString hubZeroUrl = "https://cloud-53.genouest.org/login";
    bioseController w(settingsUrl, iconsDir);
    w.setHubZeroUrl(hubZeroUrl);

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

    blSettingsGroups settings;
    settings.load(settingsUrl);
    QString styleFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\default\\stylesheet.css";
    QFile file(settings.value("Home", "stylesheet"));
    if (file.exists()){
        styleFile = settings.value("Home", "stylesheet");
    }
    a.setStyleSheet("file:///" + styleFile);


    return a.exec();
}
