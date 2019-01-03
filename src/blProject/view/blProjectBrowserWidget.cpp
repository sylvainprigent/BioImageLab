/// \file blProjectBrowserWidget.cpp
/// \brief blProjectBrowserWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectBrowserWidget.h"
#include "blProject/model/blProjectAccess.h"
#include <QVBoxLayout>

blProjectBrowserWidget::blProjectBrowserWidget(bool useNewProjectIcone, bool useEmptyWidget, QWidget *parent) :
    QWidget(parent)
{
    m_useNewProjectIcone = useNewProjectIcone;
    m_useEmptyWidget = useEmptyWidget;
    createWidget();
}

void blProjectBrowserWidget::createWidget(){

    // 1- create the widget
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    if (m_useNewProjectIcone){
        m_toolbar = new blProjectBrowserWidgetToolBar(this);
        m_toolbar->setMaximumHeight(100);
        layout->addWidget(m_toolbar);
        connect(m_toolbar, SIGNAL(askNewProject()), this, SIGNAL(askNewProject()));
    }

    blProjectAccess* projectDatabase = blProjectAccess::instance();
    QList<blProjectInfo*> projectsInfo = projectDatabase->database()->allProjects();
    m_table = new blProjectBrowserWidgetList(projectsInfo, this, m_useEmptyWidget);

    layout->addWidget(m_table);
    this->setLayout(layout);

    // 2- connect
    connect(m_table, SIGNAL(askOpenProject(blProjectInfo*)), this, SIGNAL(askOpenProject(blProjectInfo*)));
    connect(m_table, SIGNAL(askDeleteProject(blProjectInfo*)), this, SIGNAL(askDeleteProject(blProjectInfo*)));
    connect(m_table, SIGNAL(askNewProject()), this, SIGNAL(askNewProject()));
}

void blProjectBrowserWidget::rowDeletedFeedBack(bool success, QString message){
    m_table->rowDeletedFeedBack(success, message);
}
