/// \file blProjectFolderFilter.cpp
/// \brief blProjectFolderFilter
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectFolderFilter.h"
#include "blFileSearch.h"

blProjectFolderFilter::blProjectFolderFilter(QString folderPath, bool isRecursive, QList<QStringList> filtersInfos)
{
    m_folderPath = folderPath;
    m_isRecursive = isRecursive;
    m_filtersInfos = filtersInfos;

}

QStringList blProjectFolderFilter::run(){

    m_curentFiles.clear();
    for (int i = 0 ; i < m_filtersInfos.size() ; ++i){
        QStringList newSet = filter(m_filtersInfos[i][0], m_filtersInfos[i][1], m_filtersInfos[i][2]);

        // add list to curentFiles
        QVector<int> notfounded;
        for (int j = 0 ; j < newSet.size() ; ++j){
            if (!findInCurent(newSet[j])){
                notfounded.append(j);
            }
        }
        for (int j = 0 ; j < notfounded.size() ; ++j){
            m_curentFiles.append(newSet[notfounded[j]]);
        }
    }
    return m_curentFiles;
}

QStringList blProjectFolderFilter::filter(QString starts, QString contains, QString ends){

    QStringList selected;
    blFileSearch fileSearch;
    QStringList images = fileSearch.searchFiles(m_folderPath, m_isRecursive);
    for (int i = 0 ; i < images.size() ; ++i){
        QString fileName = images[i];

        // filter the fileName
        bool boolStart = false;
        if ( !starts.isEmpty() ){
            if (fileName.startsWith(starts)){
                boolStart = true;
            }
        }
        else{
            boolStart = true;
        }
        bool boolContain = false;
        if ( !contains.isEmpty() ){
            if (fileName.contains(contains)){
                boolContain = true;
            }
        }
        else{
            boolContain = true;
        }
        bool boolEnd = false;
        if ( !ends.isEmpty() ){
            if (fileName.endsWith(ends)){
                boolEnd = true;
            }
        }
        else{
            boolEnd = true;
        }

        if ( boolStart && boolContain && boolEnd){
            selected.append(fileName);
        }
    }
    return selected;
}

bool blProjectFolderFilter::findInCurent(QString path){
    for (int i = 0 ; i < m_curentFiles.size() ; ++i){
        if (m_curentFiles[i] == path){
            return true;
        }
    }
    return false;
}
