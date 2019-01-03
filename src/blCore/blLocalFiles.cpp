#include "blLocalFiles.h"

blLocalFiles::blLocalFiles(){

}

QString blLocalFiles::getThemeFile(){

    QString releaseUrl = QString("theme") + QDir::separator() + "default" + QDir::separator() + "stylesheet.css";
    QFileInfo file(releaseUrl);
    if ( file.exists() ){
        return releaseUrl;
    }

    QString buildUrl = QString("..") + QDir::separator() + ".." + QDir::separator() + "theme" + QDir::separator() + "default" + QDir::separator() + "stylesheet.css";
    QFileInfo fileb(buildUrl);
    if (fileb.exists()){
           return buildUrl;
    }

    return "";
}

QString blLocalFiles::getIconDir(){

    QString releaseUrl = QString("theme") + QDir::separator() + "default" + QDir::separator();
    QFileInfo file(releaseUrl);
    if ( file.exists() ){
        return releaseUrl;
    }

    QString buildUrl = QString("..") + QDir::separator() + ".." + QDir::separator() + "theme" + QDir::separator() + "default" + QDir::separator();
    QFileInfo fileb(buildUrl);
    if (fileb.exists()){
           return buildUrl;
    }

    return "";
}

QString blLocalFiles::getSettingsFile(){

    return "settings.db";
}
