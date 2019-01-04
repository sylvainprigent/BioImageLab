/// \file blProjectInfo.cpp
/// \brief blProjectInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectModel.h"
#include "blProjectAccess.h"
#include "blCore/blSettingsAccess.h"
#include "blProjectIndex.h"
#include <QDebug>

blProjectModel::blProjectModel(){
    m_info = 0;
    m_index = 0;
}

blProjectModel::~blProjectModel(){
    if (m_index){
        m_index->disconnect();
    }
}

void blProjectModel::setProjectInfo(blProjectInfo* info){
    m_info = info;
    QString projectAbsoluteUrl = blSettingsAccess::instance()->settings()->value("Project", "Data Directory") + QDir::separator() + m_info->url() + QDir::separator();
    // 1- connect to the project database
    m_index = new blProjectIndex( projectAbsoluteUrl + "index.db");
    m_index->connect();
}

blProjectIndex *blProjectModel::index(){
    return m_index;
}

QString blProjectModel::createProject(blProjectInfo* info){

    m_info = info;
    // add project to the database
    bool success = blProjectAccess::instance()->database()->editProject(info);
    blProjectAccess::instance()->database()->viewTable("projects");

    if (success){
        // create the url
        QString projectDir = blSettingsAccess::instance()->settings()->value("Project", "Data Directory");
        QDir newProjectDir(projectDir + QDir::separator() + "project_" + info->id());
        int id = info->id();
        while(newProjectDir.exists()){
            id++;
            newProjectDir.setPath(projectDir + QDir::separator() + "project_" + QString::number(id));
        }
        //qDebug() << "project dir = " << projectDir + QDir::separator() + "project_" + QString::number(id);
        if(!newProjectDir.mkdir(projectDir + QDir::separator() + "project_" + QString::number(id))){
            return "Unable to create the project directory";
        }

        // set th eurl to database
        info->setUrl("project_" + QString::number(id));
        success = blProjectAccess::instance()->database()->editProject(info);
        qDebug() << "-------------create project infos:" ;
        blProjectAccess::instance()->database()->viewTable("projects");
        if (!success){
            return "Cannot write to the project URL into the database";
        }
    }
    else{
        return "Cannot write to the project database";
    }
    return "success";
}

QString blProjectModel::importData(blProjectInfo* projectInfo,  blImportDataInfo *importInfo){

    QString projectAbsoluteUrl = blSettingsAccess::instance()->settings()->value("Project", "Data Directory") + QDir::separator() + projectInfo->url() + QDir::separator();
    // 1- connect to the project database
    blProjectIndex index( projectAbsoluteUrl + "index.db");
    index.connect();

    // 2- import column
    blMainColumnInfo mainColumnInfo = index.setMainColumn(importInfo->mainColumnInfo());
    // set maincolumn id to sub columns
    QList<blSubColumnInfo> subColumns = importInfo->subColumnsInfos();

    //qDebug() << "blProjectModel::importData main column id = " << mainColumnInfo.id();
    QList<blSubColumnInfo> subColumnsIdx;
    for(int i = 0 ; i < subColumns.count() ; i++){
        blSubColumnInfo info = subColumns.at(i);
        info.set_id_main_col(mainColumnInfo.id());
        blSubColumnInfo infodb = index.setSubColumnInfo(info);
        //qDebug() << "sub column id = " << infodb.id();
        subColumnsIdx.append(infodb);
    }

    // 3- import tags
    // set sub columns ids to tags
    QList<blTagInfo> tags = importInfo->tags().all();
    QList<blTagInfo> tagsIdx;
    for(int i = 0 ; i < tags.count() ; i++){
        // get the sub column id from name
        blTagInfo info = tags.at(i);
        QString subColName = info.subColName();
        //qDebug() << "tag subColumnName = " << subColName;
        for (int sc = 0 ; sc < subColumnsIdx.count() ; sc++){
            if (subColumnsIdx[sc].name() == subColName){
                //qDebug() << "found sub column name, id ! " << subColumnsIdx[sc].id();
                info.setSubColId(subColumnsIdx[sc].id());
            }
        }
        tagsIdx.append( index.setTag(info) );
    }


    // 4- create the data dir into the project directory
    QList<blDataInfo> data = importInfo->data();
    QString dirUrl = projectAbsoluteUrl + "col_" + QString::number(mainColumnInfo.id()) + QDir::separator();
    QDir dataDir(dirUrl);
    if (!dataDir.exists()){
        dataDir.mkdir(dirUrl);
    }

    // 5- index data
    for(int i = 0 ; i < data.count() ; i++){

        blDataInfo dataInfo = data.at(i);
        qDebug() << "add new data: " << dataInfo.url();
        // set the main column id
        dataInfo.setid_main_col(mainColumnInfo.id());

        // set the sub column id
        QString subColName = dataInfo.id_sub_column_name();
        for (int sc = 0 ; sc < subColumnsIdx.count() ; sc++){
            if (subColumnsIdx[sc].name() == subColName){
                dataInfo.setid_sub_column(subColumnsIdx[sc].id());
            }
        }

        // set the full url
        QString datatype = index.getSubColDataType(dataInfo.id_sub_column());
        qDebug() << "------------add data datatype = " << datatype << ", id sub col = " << dataInfo.id_sub_column();
        if (datatype != "tag"){
            QString originalUrl = dataInfo.url();
            QFileInfo originalFile(originalUrl);
            QString projectUrl = dirUrl + originalFile.fileName();
            QFile::copy(originalUrl, projectUrl);
            dataInfo.seturl(projectUrl);
            //data[i] = curentData;
        }

        // index data
        index.setData(dataInfo);
    }

    index.viewTable("blp_maincol");
    index.viewTable("blp_subcol");
    index.viewTable("blp_data");
    index.viewTable("blp_tags");
    index.disconnect();
    qDebug()<< "import data done";

}

QList<blMainColumnInfo> blProjectModel::mainColumns(){
    QString projectAbsoluteUrl = blSettingsAccess::instance()->settings()->value("Project", "Data Directory") + QDir::separator() + m_info->url() + QDir::separator();

    blProjectIndex index( projectAbsoluteUrl + "index.db");
    index.connect();
    QList<blMainColumnInfo> mc = index.mainColumns();
    index.disconnect();
    return mc;
}

QList<blSubColumnInfo> blProjectModel::subColumns(int mainColumnId){
    QString projectAbsoluteUrl = blSettingsAccess::instance()->settings()->value("Project", "Data Directory") + QDir::separator() + m_info->url() + QDir::separator();

    blProjectIndex index( projectAbsoluteUrl + "index.db");
    index.connect();
    QList<blSubColumnInfo> mc = index.subColumns(mainColumnId);
    index.disconnect();
    return mc;
}
