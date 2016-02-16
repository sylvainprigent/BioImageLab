/// \file blProjectFolderLabelExtractor.cpp
/// \brief blProjectFolderLabelExtractor
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectFolderLabelExtractor.h"

blProjectFolderLabelExtractor::blProjectFolderLabelExtractor(QStringList files, QString rootPath){
    m_files = files;
    m_rootPath = rootPath;
}

QList<QStringList> blProjectFolderLabelExtractor::run(QString regExps){

    if (regExps == "Folders"){
        return pathLabelExtractor();
    }
    if (regExps == "Created Date"){
        return dataLabelExtractor();
    }
    else{
        QList<QStringList> empty;
        return empty;
    }
}

/*
int blProjectFolderLabelExtractor::labelsCount(){

}

QStringList blProjectFolderLabelExtractor::labelsTitle(){

}*/

QStringList blProjectFolderLabelExtractor::label(int i){
    return m_extractedLabels.at(i);
}

QStringList blProjectFolderLabelExtractor::removeRootPath(){
    QStringList list;
    for (int i = 0 ; i < m_files.size() ; ++i){
        QString inter = m_files[i];
        list.append(inter.remove(0, m_rootPath.size()));
    }
    return list;
}

QList<QStringList> blProjectFolderLabelExtractor::pathLabelExtractor(){

    //QStringList files = removeRootPath();

    //qDebug() << "pathLabelExtractor: " << "count labels";
    QVector<int> numLabels; numLabels.resize(m_files.size());
    QList<QStringList> labelsFolders;
    int totalLabels = 0;
    for (int i = 0 ; i < m_files.size() ; ++i){
        QStringList labels = m_files[i].split("/");
        numLabels[i] = labels.size();
        labelsFolders.append(labels);
        if (labels.size() > totalLabels){
            totalLabels = labels.size();
        }
    }

    //qDebug() << "pathLabelExtractor: " << "extract";
    QList<QStringList> extractedLabels;
    for (int i = 0 ; i < labelsFolders.size() ; ++i){
        QStringList inter;
        if (labelsFolders[i].size() == totalLabels){
            for (int j = 0 ; j < totalLabels ; ++j){
                inter.append(labelsFolders[i][j]);
            }
        }
        else{
            for (int j = 0 ; j < labelsFolders[i].size() -1 ; ++j){
                inter.append(labelsFolders[i][j]);
            }
            for (int j = labelsFolders[i].size() -1 ; j < totalLabels-1 ; ++j){
                inter.append("");
            }
             inter.append(labelsFolders[i][labelsFolders[i].size() -1]);
        }
        extractedLabels.append(inter);
        //qDebug() << "inter = " << inter;
    }
    //qDebug() << "extractedLabels folder: " << extractedLabels.size();

    // remove redondancey
    for (int label = totalLabels-1 ; label >=0 ; --label){
        bool changed = false;
        for (int i = 1 ; i  < m_files.size() ; ++i){
            if (extractedLabels[i][label] != extractedLabels[0][label]){
                changed = true;
                break;
            }
        }
        if (!changed){
            for (int i = 0 ; i  < m_files.size() ; ++i){
                extractedLabels[i].removeAt(label);
            }
        }
    }
    return extractedLabels;
}

QList<QStringList> blProjectFolderLabelExtractor::dataLabelExtractor(){

    QList<QStringList> dateLabels;
    for (int i = 0 ; i < m_files.size() ; ++i){
        QFileInfo fileInfo(m_files[i]);
        QStringList date;
        date.append(fileInfo.created().toString(Qt::TextDate));
        dateLabels.append(date);
    }
    return dateLabels;
}
