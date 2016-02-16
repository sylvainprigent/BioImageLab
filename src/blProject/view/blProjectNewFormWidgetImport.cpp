/// \file blProjectNewFormWidgetImport.cpp
/// \brief blProjectNewFormWidgetImport
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectNewFormWidgetImport.h"

blProjectNewFormWidgetImport::blProjectNewFormWidgetImport(QWidget *parent) :
    QWidget(parent)
{

    QGridLayout *layout = new QGridLayout;

    // title
    QLabel *title = new QLabel(tr("Import"));
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title, 0,0,1,3);

    // browse bar
    QLabel *browseTitle = new QLabel(tr("Import Folder"));
    m_folderEdit = new QLineEdit;
    QPushButton *browseButton = new QPushButton(tr("..."));
    browseButton->setObjectName("btnPrimary");
    browseButton->setMaximumWidth(50);
    connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));

    layout->addWidget(browseTitle, 1, 0);
    layout->addWidget(m_folderEdit, 1, 1);
    layout->addWidget(browseButton, 1, 2);

    m_checkBox = new QCheckBox(tr("recursive"));
    layout->addWidget(m_checkBox, 2, 1,1,1,Qt::AlignCenter);

    this->setLayout(layout);
}

void blProjectNewFormWidgetImport::browse(){
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open folder"));
    m_folderEdit->setText(folder);
}

QString blProjectNewFormWidgetImport::getPath(){
    return m_folderEdit->text();
}

bool blProjectNewFormWidgetImport::isRecursive(){
    if (m_checkBox->isChecked()){
        return true;
    }
    else{
        return false;
    }
}
