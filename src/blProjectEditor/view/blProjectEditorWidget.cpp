/// \file blProjectEditorWidget.cpp
/// \brief blProjectEditorWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorWidget.h"
#include <QtWidgets>


blProjectEditorWidget::blProjectEditorWidget(blProjectInfo *projectInfo, QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_toolbar = new blProjectEditorToolbarWidget(projectInfo->name(), this);
    layout->addWidget(m_toolbar, 0, Qt::AlignTop);

    m_table = new blProjectEditorTableWidget(this);
    layout->addWidget(m_table, 1);

    m_footer = new blProjectEditorFooterWidget(this);
    layout->addWidget(m_footer, 0, Qt::AlignBottom);

    this->setLayout(layout);

    connect(m_toolbar, SIGNAL(askImport()), this, SIGNAL(askImport()));
    connect(m_toolbar, SIGNAL(askInfo()), this, SIGNAL(askInfo()));
    connect(m_toolbar, SIGNAL(askTags()), this, SIGNAL(askTags()));
    connect(m_toolbar, SIGNAL(askProcess()), this, SIGNAL(askProcess()));
    connect(m_toolbar, SIGNAL(askViews()), this, SIGNAL(askViews()));

    connect(m_table, SIGNAL(askImportData()), this, SIGNAL(askImport()));

}

void blProjectEditorWidget::setProjectInfo(blProjectInfo* projectInfo){
    m_toolbar->setProjectName(projectInfo->name());
}

blProjectEditorTableWidget* blProjectEditorWidget::table(){
    return m_table;
}
