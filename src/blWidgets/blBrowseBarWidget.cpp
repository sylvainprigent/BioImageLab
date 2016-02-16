/// \file blBrowseBarWidget.h
/// \brief blBrowseBarWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#include "blBrowseBarWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "blClickableIcon.h"
#include <QDebug>

blBrowseBarWidget::blBrowseBarWidget(bool isFolder, QString iconFile, QWidget *parent) : QWidget(parent){

    m_isFolder = isFolder;
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    m_lineEdit = new QLineEdit(this);
    connect(m_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(emitPathChanged(QString)));
    connect(m_lineEdit, SIGNAL(returnPressed()), this, SLOT(emitPathChanged()));
    layout->addWidget(m_lineEdit);

    if (iconFile == ""){
        QPushButton *button = new QPushButton("...",this);
        button->setObjectName("btnDefault");
        connect(button, SIGNAL(clicked()), this, SLOT(browse()));
        layout->addWidget(button);
    }
    else{
        blClickableIcon *browseIcon = new blClickableIcon(iconFile, "",20,20,0,this);
        QHBoxLayout *browseLayout = new QHBoxLayout(m_lineEdit);

        browseLayout->addWidget(browseIcon, 0, Qt::AlignRight);
        browseLayout->setContentsMargins(0,0,0,0);
        browseLayout->setSpacing(0);
        browseLayout->setMargin(2);

        connect(browseIcon, SIGNAL(clicked()), this, SLOT(browse()));
    }

}

void blBrowseBarWidget::emitPathChanged(QString path){
    emit pathChanged(path);
}

void blBrowseBarWidget::emitPathChanged(){
    qDebug() << "emited path = " << m_lineEdit->text() ;
    emit pathChanged(m_lineEdit->text());
}

void blBrowseBarWidget::browse(){
    if (m_isFolder){
        QString folder = QFileDialog::getExistingDirectory(this, tr("Open folder"));
        m_lineEdit->setText(folder);
    }
    else{
        QString fichier = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), "*.*");
        m_lineEdit->setText(fichier);
    }
}

void blBrowseBarWidget::setText(QString txt){
    m_lineEdit->setText(txt);
}

QString blBrowseBarWidget::text(){
    return m_lineEdit->text();
}

QLineEdit * blBrowseBarWidget::getLineEdit(){
    return m_lineEdit;
}
