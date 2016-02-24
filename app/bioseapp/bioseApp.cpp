#include <QtWidgets>

#include <QApplication>
#include <QDir>
#include "bioseController.h"
#include <blFinder>
#include "blCore/blSettingsAccess.h"
#include "blProjectnew/model/blProjectAccess.h"

void initialiseSettings(QString distDir, QString settingsFile, QString themesDir){
    // load settings
    blSettingsAccess* settingsAccess = blSettingsAccess::instance();
    settingsAccess->setSettingsFile(settingsFile);
    settingsAccess->load();

    // set default settings
    blSettingsGroups *groups = settingsAccess->instance()->settings();

    // home:
    QString stylesheetFile = groups->value("Home", "stylesheet", true);
    if (stylesheetFile.isEmpty()){
        groups->set("Home", "stylesheet", themesDir + "default" + QDir::separator() + "stylesheet.css");
    }

    // Project:
    QString projectsDatabaseFile = groups->value("Project", "Database URL", true);
    if (projectsDatabaseFile.isEmpty()){
        groups->set("Project", "Database URL", distDir + "projects.db");
    }

    QString projectsDir = groups->value("Project", "Data Directory", true);
    if (projectsDir.isEmpty()){
        groups->set("Project", "Data Directory", distDir + "projects" + QDir::separator());
    }
}

void initialiseProjectsDatbase(QString distDir){
    // database
    blProjectAccess *projectAccess = blProjectAccess::instance();
    projectAccess->setDatabaseFile(distDir + QDir::separator() + "projects.db");
    projectAccess->load();

    // storage directory
    QString projectDirName = distDir + QDir::separator() + "projects";
    QDir projectsDir;
    if (!projectsDir.exists()){
        projectsDir.mkdir(projectDirName);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // settings
    QString distDir = QDir::currentPath() + QDir::separator() + ".." + QDir::separator() + ".." + QDir::separator() + "dist" + QDir::separator();
    QString themesDir = QDir::currentPath() + QDir::separator() + ".." + QDir::separator() + ".." + QDir::separator() + "theme" + QDir::separator();
    QString settingsFile = distDir + "settings.db";

    // initialize settings
    initialiseSettings(distDir, settingsFile, themesDir);

    // initialize project database
    initialiseProjectsDatbase(distDir);

    // instanciate Gui
    QString iconsDir = themesDir + "default" + QDir::separator();
    bioseController w(iconsDir);

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


    // set stylesheet
    QString styleFile = blSettingsAccess::instance()->settings()->value("Home", "stylesheet");
    a.setStyleSheet("file:///" + styleFile);

    return a.exec();
}
