/// \file blProjectEditorImportWidget.cpp
/// \brief blProjectEditorImportWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorImportWidget.h"
#include <QtWidgets>

blProjectEditorImportWidget::blProjectEditorImportWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout* layout = new QVBoxLayout;
    this->setObjectName("blProjectEditorImportWidget");

    QLabel *title = new QLabel(tr("Import"), this);
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title);

    QWidget *addWidget = new QWidget(this);
    QHBoxLayout *addLayout = new QHBoxLayout;
    QPushButton *addButton = new QPushButton(tr("Browse"), this);
    addButton->setObjectName("btnDefault");
    m_addEdit = new QLineEdit(this);
    addLayout->addWidget(m_addEdit, 1);
    addLayout->addWidget(addButton, 0, Qt::AlignLeft);
    addWidget->setLayout(addLayout);
    layout->addWidget(addWidget);

    QPushButton *importButton = new QPushButton("Import", this);
    importButton->setObjectName("btnPrimary");
    layout->addWidget(importButton, 0, Qt::AlignRight);

    layout->addWidget(new QWidget(this), 1, Qt::AlignTop);
    this->setLayout(layout);

    connect(addButton, SIGNAL(released()), this, SLOT(browse()));
    connect(importButton, SIGNAL(released()), this, SLOT(emitAskImportData()));
}

void blProjectEditorImportWidget::browse(){
    QString file = QFileDialog::getOpenFileName(this, "Import data", QString(), "*.*");
    m_addEdit->setText(file);
}

void blProjectEditorImportWidget::emitAskImportData(){
    blProjectData *data = new blProjectData();
    data->setUrl(m_addEdit->text());
    emit askImportData(data);
}

