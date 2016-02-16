/// \file blProjectModel.cpp
/// \brief blProjectModel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectModel.h"
#include <QDir>
#include <QDebug>
#include "blCore/blDir.h"

blProjectModel::blProjectModel(QObject *parent) : QObject(parent){

}

blProjectModel::blProjectModel(QString projectUrl, QObject *parent) : QObject(parent){
    m_projectUrl = projectUrl;
}

// name
void blProjectModel::setProjectName(QString projectName){
    m_projectName = projectName;
}

QString blProjectModel::projectName(){
    return m_projectName;
}

// IO
void blProjectModel::setProjectUrl(QString projectUrl){
    m_projectUrl = projectUrl;
}

QString blProjectModel::projectUrl(){
    return m_projectUrl;
}

void blProjectModel::load(){

    // 1- get the column files
    QStringList dataFiles;
    QString mainFile = m_projectUrl + QDir::separator() + "data.blb";
    qDebug() << "load project from: " <<  mainFile;
    QFile file(mainFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR: Cannot open the file " + mainFile + " to save column " + file.errorString();
        return;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8);
    in >> m_projectName;
    in >> dataFiles;

    qDebug() << "project Name = " << m_projectName;
    qDebug() << "columns urls = " << dataFiles;

    // 2- load all the files data.blb
    for (int i = 0 ; i < dataFiles.size() ; ++i){
        blProjectModelMainColumn column(dataFiles[i]);
        column.load();
        qDebug() << "loaded columns: " << column.name();
        m_mainColumns[column.name()] = column;
    }
}

void blProjectModel::save(){

    // 0- create the folder if not exists
    QDir projectDir(m_projectUrl);
    if (!projectDir.exists()){
        projectDir.mkdir(m_projectUrl);
    }

    // 1- save the data
    QStringList dataFiles;
    QMapIterator<QString, blProjectModelMainColumn> i(m_mainColumns);
    QString folder, fileURL;
    while (i.hasNext()) {
        i.next();
        qDebug() << "Model save column: " << i.key();
        folder = mainColumnFolder(i.key());

        fileURL = folder + QDir::separator() + "data.blb";
        qDebug() << "Model save the column " << i.key();
        qDebug() << "Model save the column at url " << fileURL;
        dataFiles.append(fileURL);
        blProjectModelMainColumn column = i.value();
        column.setName(i.key());
        column.setFile(fileURL);
        column.save();
    }

    // 2- Save the column order file
    QString mainFile = m_projectUrl + QDir::separator() + "data.blb";
    QFile file(mainFile);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "ERROR: Cannot open the file " + mainFile + " to save column " + file.errorString();
        return;
    }
    qDebug() << "file url contains: " << dataFiles;
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_5);
    out << m_projectName;
    out << dataFiles;
}

// getters/setters
void blProjectModel::addMainColumn(QString name, blProjectModelMainColumn& column){
    column.setName(name);
    m_mainColumns[name] = column;
}

blProjectModelMainColumn& blProjectModel::mainColumn(QString name){
    return m_mainColumns[name];
}

QMap<QString, blProjectModelMainColumn>& blProjectModel::mainColumns(){
    return m_mainColumns;
}

QStringList blProjectModel::mainColumnsName(){

    QStringList columnsNames;
    QMap<QString, blProjectModelMainColumn>::iterator i;
    for (i = m_mainColumns.begin(); i != m_mainColumns.end(); ++i){
        columnsNames.append(i.key());
    }
    return columnsNames;
}

QStringList blProjectModel::columnsName(QString mainColumn){

    QMap<QString, blProjectModelColumn> mainColumnData = m_mainColumns[mainColumn].columns();

    QStringList columnsNames;
    QMap<QString, blProjectModelColumn>::iterator i;
    for (i = mainColumnData.begin(); i != mainColumnData.end(); ++i){
        columnsNames.append(i.key());
    }

    return columnsNames;
}

QString blProjectModel::mainColumnFolder(QString folderName){

    // 1- create the folder URL
    QString folder = m_projectUrl + QDir::separator() + folderName;

    // 2- create the folder if not exists
    QDir dir(folder);
    if (!dir.exists()){
        if (!dir.mkdir(folder)){
            qDebug() << "ERROR: Cannot save the column at: " << folder;
        }
    }

    // 3- return the folder URL
    return folder;
}

// queries
void blProjectModel::createColumnIfNotExists(QString mainColumnName, QString columnName){
    // add main column if not existing
    qDebug() << "blProjectModel:: add main column if not existing";
    if (!this->isMainColumn(mainColumnName)){
        blProjectModelMainColumn column;
        this->addMainColumn(mainColumnName,column);
    }
    // add column if not existing
    qDebug() << "blProjectModel:: add column if not existing";
    if (!this->isColumn(mainColumnName, columnName)){
        blProjectModelMainColumn column = this->mainColumn(mainColumnName);
        column.addColumn(columnName);
    }
}


bool blProjectModel::isMainColumn(QString name){

    QMap<QString, blProjectModelMainColumn>::iterator i = m_mainColumns.begin();
    while (i != m_mainColumns.end()) {
        if (i.key() == name){
            return true;
        }
        ++i;
    }
    return false;
}

bool blProjectModel::isColumn(QString mainColumnName, QString columnName){
    if (isMainColumn(mainColumnName)){
        blProjectModelMainColumn& column = mainColumn(mainColumnName);
        return column.isColumn(columnName);
    }
    return false;
}

void blProjectModel::removeMainColumn(QString columnName){

    // remove the key
    QMap<QString, blProjectModelMainColumn>::Iterator it;
    for( it = m_mainColumns.begin();  it != m_mainColumns.end();  ++it)
    {
        if( it.key() == columnName )
            m_mainColumns.remove( it.key() );
    }

    // remove the data
    if (!columnName.isEmpty()){
        blDir::deleteFolder(m_projectUrl + QDir::separator() + columnName);
    }
}

void blProjectModel::removeSubColumn(QString mainColumnName, QString subColumnName){

    blProjectModelMainColumn mainCol = m_mainColumns[mainColumnName];
    mainCol.removeColumn(subColumnName);
    m_mainColumns[mainColumnName] = mainCol;
}

blProjectModelColumn blProjectModel::columnData(QString mainColumnName, QString subColumnName){
    blProjectModelMainColumn mainCol = m_mainColumns[mainColumnName];
    return mainCol.column(subColumnName);
}
