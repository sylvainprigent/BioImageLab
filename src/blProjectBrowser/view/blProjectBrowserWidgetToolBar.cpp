/// \file blProjectBrowserWidgetToolBar.cpp
/// \brief blProjectBrowserWidgetToolBar
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectBrowserWidgetToolBar.h"

#include <blWidgets/blClickableIcon.h>
#include <QHBoxLayout>
#include <QPushButton>

blProjectBrowserWidgetToolBar::blProjectBrowserWidgetToolBar(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0,15,0,15);
    this->setLayout(layout);

    QPushButton *newProjectButton = new QPushButton(this);
    newProjectButton->setObjectName("blProjectNewProjectButton");
    newProjectButton->setFixedSize(64,64);
    connect(newProjectButton, SIGNAL(clicked()), this, SLOT(emitNewProject()));

    layout->addWidget(new QWidget, 1, Qt::AlignRight);
    layout->addWidget(newProjectButton, 0, Qt::AlignRight);
}

void blProjectBrowserWidgetToolBar::emitNewProject(){
    emit askNewProject();
}
