/// \file blProjectEditorController.cpp
/// \brief blProjectEditorController
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorController.h"
#include "blProjectCore/model/blProjectAccess.h"

#include <QVBoxLayout>

blProjectEditorController::blProjectEditorController(blProjectInfo *projectInfo, QWidget *parent) : QWidget(parent){

    this->createWidgets(projectInfo);

    connect(m_projectEditorWidget, SIGNAL(askInfo()), this, SLOT(showInfo()));
    connect(m_porjectEditorInfo, SIGNAL(askEditProject(blProjectInfo*)), this, SLOT(editProjectInfo(blProjectInfo*)));
}

blProjectEditorController::~blProjectEditorController(){

}

void blProjectEditorController::createWidgets(blProjectInfo *projectInfo){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    m_projectEditorWidget = new blProjectEditorWidget(projectInfo, this);
    layout->addWidget(m_projectEditorWidget);

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
}

void blProjectEditorController::showInfo(){
    m_porjectEditorInfo->setVisible(true);
}

void blProjectEditorController::editProjectInfo(blProjectInfo* projectInfo){
    blProjectAccess::instance()->database()->editProject(projectInfo);
    m_porjectEditorInfo->setVisible(false);
    m_projectEditorWidget->setProjectInfo(projectInfo);
}
