/// \file blProjectNewFormWidgetDescription.cpp
/// \brief blProjectNewFormWidgetDescription
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectNewFormWidgetDescription.h"

blProjectNewFormWidgetDescription::blProjectNewFormWidgetDescription(bool emptyProjectButton, QWidget *parent) :
    QWidget(parent)
{

    m_layout = new QGridLayout(this);
    // title
    QLabel *title = new QLabel(tr("Description"), this);
    title->setObjectName("blLabelFormHeader1");
    m_layout->addWidget(title, 0, 0, 1, 2);

    // Name
    QLabel *projectName = new QLabel(tr("Name:"), this);
    m_layout->addWidget(projectName, 1, 0);
    m_projectNameEdit = new QLineEdit(this);
    m_layout->addWidget(m_projectNameEdit, 1, 1);

    // Description
    QLabel *description = new QLabel(tr("objective:"), this);
    m_layout->addWidget(description, 2, 0, 1, 1, Qt::AlignTop);
    m_projectDescriptionEdit = new QTextEdit(this);
    m_projectDescriptionEdit->setMaximumHeight(300);
    m_layout->addWidget(m_projectDescriptionEdit, 2,1);

    description->setVisible(false);
    m_projectDescriptionEdit->setVisible(false);

    // create empty project
    if (emptyProjectButton){
        QPushButton *emptyProjectButton = new QPushButton;
        emptyProjectButton->setText(tr("Create empty project"));
        connect(emptyProjectButton, SIGNAL(clicked()), this, SLOT(emitEmptyProject()));
        m_layout->addWidget(emptyProjectButton, 5, 1, 1, 1, Qt::AlignRight);
    }

    this->setLayout(m_layout);
}

QString blProjectNewFormWidgetDescription::getName(){
    return m_projectNameEdit->text();
}

QString blProjectNewFormWidgetDescription::getDescription(){
    return m_projectDescriptionEdit->toPlainText();
}

void blProjectNewFormWidgetDescription::emitEmptyProject(){
    emit askCreateEmptyProject();
}

QGridLayout* blProjectNewFormWidgetDescription::layout(){
    return m_layout;
}

void blProjectNewFormWidgetDescription::setName(QString name){
    m_projectNameEdit->setText(name);
}

void blProjectNewFormWidgetDescription::setDescription(QString desc){
    m_projectDescriptionEdit->setText(desc);
}
