/// \file blProjectEditorController.cpp
/// \brief blProjectEditorController
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorController.h"
#include "blProjectCore/model/blProjectAccess.h"
#include "blProjectEditor/model/blProjectEditorAccess.h"
#include "blProjectEditor/model/blProjectDataModel.h"
#include "blCore/blException.h"

#include <QVBoxLayout>

blProjectEditorController::blProjectEditorController(blProjectInfo *projectInfo, QWidget *parent) : QWidget(parent){

    m_projectInfo = projectInfo;

    // initialize the database
    blProjectEditorAccess* projectDatabaseAccess = blProjectEditorAccess::instance();
    projectDatabaseAccess->setDatabaseFile(projectInfo->url() + QDir::separator() + "project.db");
    projectDatabaseAccess->load();
    projectDatabaseAccess->database()->viewDatabase();

    this->createWidgets(projectInfo);
    this->loadContent();

    // info
    connect(m_projectEditorWidget, SIGNAL(askInfo()), this, SLOT(showInfo()));
    connect(m_porjectEditorInfo, SIGNAL(askEditProject(blProjectInfo*)), this, SLOT(editProjectInfo(blProjectInfo*)));

    // tags
    connect(m_projectEditorWidget, SIGNAL(askTags()), this, SLOT(showTags()));
    connect(m_projectEditorTags, SIGNAL(askAddTag(blProjectTag*)), this, SLOT(addTag(blProjectTag*)));
    connect(m_projectEditorTags, SIGNAL(askRemoveTag(blProjectTag*)), this, SLOT(removeTag(blProjectTag*)));

    // import
    connect(m_projectEditorWidget, SIGNAL(askImport()), this, SLOT(showImport()));
    connect(m_projectEditorImport, SIGNAL(askImportData(blProjectData*)), this, SLOT(importData(blProjectData*)));
}

blProjectEditorController::~blProjectEditorController(){

}

void blProjectEditorController::loadContent(){
    blProjectContent *content = blProjectEditorAccess::instance()->database()->getContent();
    content->print();
    m_projectEditorWidget->table()->setContent(content);
}

void blProjectEditorController::createWidgets(blProjectInfo *projectInfo){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    // main central widget
    m_projectEditorWidget = new blProjectEditorWidget(projectInfo, this);
    layout->addWidget(m_projectEditorWidget);

    // Informations editor
    m_porjectEditorInfo = new blProjectEditorInfoWidget();
    m_porjectEditorInfo->setData(projectInfo);
    m_porjectEditorInfo->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            m_porjectEditorInfo->size(),
            qApp->desktop()->availableGeometry()
        ));
    m_porjectEditorInfo->setVisible(false);

    // tags editor
    m_projectEditorTags = new blProjectEditorTagsWidget();
    m_projectEditorTags->setTags(blProjectEditorAccess::instance()->database()->getTags());
    m_projectEditorTags->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            m_projectEditorTags->size(),
            qApp->desktop()->availableGeometry()
        ));
    m_projectEditorTags->setVisible(false);

    // import editor
    m_projectEditorImport = new blProjectEditorImportWidget();
    m_projectEditorImport->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            m_projectEditorImport->size(),
            qApp->desktop()->availableGeometry()
        ));
    m_projectEditorImport->setVisible(false);
}

void blProjectEditorController::showInfo(){
    m_porjectEditorInfo->setVisible(true);
}

void blProjectEditorController::editProjectInfo(blProjectInfo* projectInfo){
    blProjectAccess::instance()->database()->editProject(projectInfo);
    m_porjectEditorInfo->setVisible(false);
    m_projectEditorWidget->setProjectInfo(projectInfo);
}

void blProjectEditorController::showTags(){
    m_projectEditorTags->setVisible(true);
}

void blProjectEditorController::addTag(blProjectTag *tag){

    blProjectEditorAccess::instance()->database()->setTag(tag);
    m_projectEditorTags->addTag(tag);
    //qDebug() << "add tag not implemented";
}

void blProjectEditorController::removeTag(blProjectTag *tag){

    blProjectEditorAccess::instance()->database()->removeTag(tag);
    m_projectEditorTags->removeTag(tag);
    qDebug() << "Remove tag done";
}

void blProjectEditorController::showImport(){
    m_projectEditorImport->setVisible(true);
}

void blProjectEditorController::importData(blProjectData* data){

    blProjectDataModel *dataModel = new blProjectDataModel();

    try {
        data = dataModel->importData(m_projectInfo, data);

        if ( QMessageBox::information(this, tr("Import data"), tr("Data have been imported")) ){
            m_projectEditorImport->setVisible(false);
        }
    }
    catch (const blException& e){
        QMessageBox::critical(this, tr("Import data error"), e.what());
    }



}
