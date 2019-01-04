/// \file blProjectEditorToolbarWidget.cpp
/// \brief blProjectEditorToolbarWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorToolbarWidget.h"
#include <QtWidgets>

blProjectEditorToolbarWidget::blProjectEditorToolbarWidget(QString projectName, QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;
    QToolBar *toolbar = new QToolBar();
    layout->addWidget(toolbar);
    layout->setContentsMargins(0,0,0,0);

    QAction* importAction = toolbar->addAction("Import");
    QAction* tagsAction = toolbar->addAction("Tags");
    QAction* processAction = toolbar->addAction("Process");
    QAction* viewAction = toolbar->addAction("View");
    QAction* infoAction = toolbar->addAction("Informations");

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolbar->addWidget(spacerWidget);

    m_projectNameLabel = new QLabel(projectName);
    m_projectNameLabel->setObjectName("blProjectEditorToolbarWidgetTitle");
    toolbar->addWidget(m_projectNameLabel);

    this->setLayout(layout);

    connect(importAction, SIGNAL(triggered(bool)), this, SLOT(emitAskImport(bool)));
    connect(tagsAction, SIGNAL(triggered(bool)), this, SLOT(emitAskTags(bool)));
    connect(processAction, SIGNAL(triggered(bool)), this, SLOT(emitAskProcess(bool)));
    connect(viewAction, SIGNAL(triggered(bool)), this, SLOT(emitAskViews(bool)));
    connect(infoAction, SIGNAL(triggered(bool)), this, SLOT(emitAskInfo(bool)));
}

void blProjectEditorToolbarWidget::setProjectName(QString projectName){
    m_projectNameLabel->setText(projectName);
}

void blProjectEditorToolbarWidget::emitAskImport(bool){
    emit askImport();
}

void blProjectEditorToolbarWidget::emitAskTags(bool){
    emit askTags();
}

void blProjectEditorToolbarWidget::emitAskProcess(bool){
    emit askProcess();
}

void blProjectEditorToolbarWidget::emitAskViews(bool){
    emit askViews();
}

void blProjectEditorToolbarWidget::emitAskInfo(bool){
    emit askInfo();
}
