/// \file blFileSearch.cpp
/// \brief blFileSearch
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blFileSearch.h"

#include <QtGui>

blFileSearch::blFileSearch(){
}

QStringList blFileSearch::searchFiles(QString folderPath, bool recursive){
    QDir dirImage;
    dirImage.setPath(folderPath);
    searchForImages(dirImage, recursive);
    return m_foundFiles;
}

QStringList blFileSearch::removeRootPath(const QStringList pathList, const QString rootPath){
    QStringList truncatedPath;
    for (int i = 0 ; i < pathList.size() ; ++i){
        truncatedPath.append(removeRootPath(pathList[i], rootPath));
    }
    return truncatedPath;
}

QString blFileSearch::removeRootPath(const QString path, const QString rootPath){
    if (path.startsWith(rootPath)){
        QString inter = path;
        inter = inter.remove(rootPath);
        return inter;
    }
    return path;
}

// private
void blFileSearch::searchForImages(QDir dirImage, bool recursive) {

    // We get the folders/files contained in dirImage
    const QFileInfoList fileinfolist = dirImage.entryInfoList();

    QListIterator<QFileInfo> it( fileinfolist );
    QFileInfo fi;

    while ((it.hasNext ())) {

        fi = it.next();
        // We get the name of the folder.
        QString name = fi.fileName ();
        QString path = fi.absoluteFilePath();

        // If it is a Folder, enter in it
        if (fi.isDir ()) {
            if (recursive){
                if ( name != "." && name != ".."){
                    QDir dirRec;
                    dirRec.setPath(path);
                    qDebug() << path;
                    searchForImages(dirRec, recursive);
                }
            }
        }
        // It is a file, check if it is an image matching the expected extensions
        else if ((fi.isFile ())){

            m_foundFiles.append (path);

        }
    }
}
