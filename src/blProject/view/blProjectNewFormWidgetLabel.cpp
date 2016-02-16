/// \file blProjectNewFormWidgetLabel.cpp
/// \brief blProjectNewFormWidgetLabel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectNewFormWidgetLabel.h"
#include <blWidgets/blClickableIcon.h>

blProjectNewFormWidgetLabel::blProjectNewFormWidgetLabel(QWidget *parent) :
    QWidget(parent)
{

    layout = new QVBoxLayout;

    // title
    QLabel *title = new QLabel(tr("Label Extraction"));
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title);

    // CheckBoxes
    m_checkBoxFolders = new QCheckBox(tr("Folders"));
    m_checkBoxDate = new QCheckBox(tr("Created Date"));

    layout->addWidget(m_checkBoxDate);
    layout->addWidget(m_checkBoxFolders);

    // View
    QPushButton *viewButton = new QPushButton(tr("View"));
    viewButton->setObjectName("btnPrimary");
    layout->addWidget(viewButton,0, Qt::AlignRight);
    connect(viewButton, SIGNAL(clicked()), this, SLOT(emitView()));

    this->setLayout(layout);
}


// private slots
void blProjectNewFormWidgetLabel::emitView(){
    emit askView();
}

void blProjectNewFormWidgetLabel::setFoldersCheckBoxVisible(bool visible){
    m_checkBoxFolders->setVisible(visible);
}

QStringList blProjectNewFormWidgetLabel::filtersList(){
    QStringList filters;
    if (m_checkBoxFolders->isChecked()){
        filters.append("Folders");
    }
    if(m_checkBoxDate){
        filters.append("Created Date");
    }
    return filters;
}

