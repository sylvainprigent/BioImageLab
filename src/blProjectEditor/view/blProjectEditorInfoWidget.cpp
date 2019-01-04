/// \file blProjectEditorWidget.cpp
/// \brief blProjectEditorWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorInfoWidget.h"
#include <QtWidgets>

blProjectEditorInfoWidget::blProjectEditorInfoWidget(QWidget *parent) :
    QWidget(parent)
{

    // initialize the data
    m_projectId = 0;

    // build the form
    this->buildWidget();
    this->editView();

}

void blProjectEditorInfoWidget::setData(blProjectInfo *info){
    m_projectId = info->id();
    m_nameEdit->setText(info->name());
    m_descriptionEdit->setText(info->description());

    this->editView();
}

void blProjectEditorInfoWidget::editView(){
    if (m_projectId == 0){
        m_saveButton->setText(tr("Next"));
    }
    else{
        m_saveButton->setText(tr("Save"));
    }
}

void blProjectEditorInfoWidget::buildWidget(){

    QGridLayout *layout = new QGridLayout;
    this->setObjectName("blProjectEditorInfoWidget");

    QLabel *title = new QLabel(tr("Project Informations"), this);
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title, 0, 0, 1, 4);

    QLabel *nameLabel = new QLabel("Name", this);
    m_nameEdit = new QLineEdit(this);
    layout->addWidget(nameLabel, 1, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(m_nameEdit, 1, 1, 1, 3);

    QLabel *descriptionLabel = new QLabel("Description", this);
    m_descriptionEdit = new QTextEdit(this);
    layout->addWidget(descriptionLabel, 2, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(m_descriptionEdit, 2, 1, 1, 3);

    m_saveButton = new QPushButton("Save");
    m_saveButton->setObjectName("btnPrimary");
    m_saveButton->setMaximumWidth(150);
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(emitEditedProject()));
    layout->addWidget(m_saveButton, 3, 3, 1, 1);

    this->setLayout(layout);
}

void blProjectEditorInfoWidget::emitEditedProject(){
    blProjectInfo* info = new blProjectInfo();
    info->setId(m_projectId);
    info->setName(m_nameEdit->text());
    info->setDescription(m_descriptionEdit->toPlainText());
    emit askEditProject(info);
}
