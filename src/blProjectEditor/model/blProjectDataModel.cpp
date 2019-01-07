/// \file blProjectDataModel.cpp
/// \brief blProjectDataModel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectDataModel.h"
#include "blProjectEditorAccess.h"
#include <blCore>
#include <QDebug>
#include <QDir>

blProjectDataModel::blProjectDataModel(){

}

blProjectDataModel::~blProjectDataModel(){

}

blProjectData* blProjectDataModel::importData(blProjectInfo *project, blProjectData *data){

    // get data dir
    QString dataDirPath = project->url() + QDir::separator() + QString("data") + QDir::separator();
    QDir dataDir(dataDirPath);
    if (!dataDir.exists()){
        if ( !dataDir.mkdir(dataDirPath) ){
            throw blException(QString("Cannot create the data directory for the project " + project->name() + " at " + project->url()).toStdString().c_str());
        }
    }

    // copy data to project
    QFileInfo dataFile(data->url());
    QString newDataUrl = dataDirPath + dataFile.fileName();
    if ( !QFile::copy(data->url(), newDataUrl) ){
        throw blException(QString("Cannot copy data from " + data->url() + " to " + newDataUrl).toStdString().c_str());
    }

    blProjectData *dataImported = new blProjectData();
    dataImported->setUrl(newDataUrl);

    // add data to the database
    blProjectData* dataImportedOut = blProjectEditorAccess::instance()->database()->setData(dataImported);
    if (dataImportedOut->id() == 0){
        throw blException( QString("The data " + data->url() + " cannot be imported to the database").toStdString().c_str());
    }
    return dataImportedOut;
}
