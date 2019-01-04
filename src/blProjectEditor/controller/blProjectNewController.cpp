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

#include <QVBoxLayout>

blProjectNewController::blProjectNewController(QWidget *parent) : QWidget(parent){

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
        emit projectCreated(projectInfo);
    }
    else{
        QMessageBox::information(this, tr("Error"), tr("Cannot create the project in the database"));
    }
}
