/// \file blProjectWidget.cpp
/// \brief blProjectWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectBrowserController.h"
#include "blProjectCore/model/blProjectAccess.h"

#include <QVBoxLayout>

blProjectBrowserController::blProjectBrowserController(QWidget *parent) : QWidget(parent){


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    m_projectBrowserWidget = new blProjectBrowserWidget(true, true, this);
    layout->addWidget(m_projectBrowserWidget);

    connect(m_projectBrowserWidget, SIGNAL(askNewProject()), this, SIGNAL(askNewProject()));
    connect(m_projectBrowserWidget, SIGNAL(askOpenProject(blProjectInfo*)), this, SIGNAL(askOpenProject(blProjectInfo*)));
    connect(m_projectBrowserWidget, SIGNAL(askDeleteProject(blProjectInfo*)), this, SLOT(deleteProject(blProjectInfo*)));
}

blProjectBrowserController::~blProjectBrowserController(){

}

void blProjectBrowserController::deleteProject(blProjectInfo* project){
    blProjectAccess::instance()->database()->removeProject(project->id());

    /// \todo remove also the project directory
}
