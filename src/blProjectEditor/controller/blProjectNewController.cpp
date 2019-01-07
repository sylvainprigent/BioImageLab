/// \file blProjectNewController.cpp
/// \brief blProjectNewController
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectNewController.h"
#include "blProjectCore/model/blProjectAccess.h"
#include "blProjectEditor/view/blProjectEditorInfoWidget.h"
#include "blCore/blSettingsAccess.h"

#include <QVBoxLayout>

blProjectNewController::blProjectNewController(QString projectsDir, QWidget *parent) : QWidget(parent){

    m_projectsDir = projectsDir;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    blProjectEditorInfoWidget* infoWidget = new blProjectEditorInfoWidget(this);
    layout->addWidget(infoWidget);

    connect(infoWidget, SIGNAL(askEditProject(blProjectInfo*)), this, SLOT(createProject(blProjectInfo*)));

}

blProjectNewController::~blProjectNewController(){

}

void blProjectNewController::createProject(blProjectInfo* projectInfo){

    QDate dateNow = QDate::currentDate();
    QString dateNowString = dateNow.toString("yyyy-MM-dd");
    projectInfo->setCreatedDate(dateNowString);
    projectInfo->setLastModifiedDate(dateNowString);
    if ( blProjectAccess::instance()->database()->addProject(projectInfo) ){

        QString projectDirPath = m_projectsDir + QDir::separator() + "project_" + QString::number(projectInfo->id());
        //qDebug() << "create project m_projectsDir: " << m_projectsDir;
        //qDebug() << "create project directory: " << projectDirPath;
        QDir projectDir(projectDirPath);
        projectInfo->setUrl(projectDirPath);
        if ( projectDir.mkdir(projectDirPath) ){
            blProjectAccess::instance()->database()->editProject(projectInfo);
            emit projectCreated(projectInfo);
        }
        else{
            QMessageBox::information(this, tr("Error"), tr("Cannot create the project directory: ") + projectDirPath);
        }

    }
    else{
        QMessageBox::information(this, tr("Error"), tr("Cannot create the project in the database"));
    }
}
