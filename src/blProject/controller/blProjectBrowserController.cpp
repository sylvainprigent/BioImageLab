/// \file blProjectWidget.cpp
/// \brief blProjectWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectBrowserController.h"
#include "blProject/model/blProjectAccess.h"

#include <QVBoxLayout>

blProjectBrowserController::blProjectBrowserController(QWidget *parent) : QWidget(parent){


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    blProjectBrowserWidget* projectBrowserWidget = new blProjectBrowserWidget(true, true, this);
    layout->addWidget(projectBrowserWidget);

    connect(projectBrowserWidget, SIGNAL(askNewProject()), this, SIGNAL(askNewProject()));
    connect(projectBrowserWidget, SIGNAL(askOpenProject(blProjectInfo*)), this, SIGNAL(askOpenProject(blProjectInfo*)));
    //connect(projectBrowserWidget, SIGNAL(askDeleteProject(blProjectInfo*)), this, SLOT(deleteProject(blProjectInfo*)));
}

blProjectBrowserController::~blProjectBrowserController(){

}
