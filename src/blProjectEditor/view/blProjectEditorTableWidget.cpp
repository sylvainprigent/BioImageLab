/// \file blProjectEditorTableWidget.cpp
/// \brief blProjectEditorTableWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorTableWidget.h"
#include <QtWidgets>

blProjectEditorTableWidget::blProjectEditorTableWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(this->emptyListWidget());
    this->setLayout(layout);

}

QWidget* blProjectEditorTableWidget::emptyListWidget(){

    m_emptyTableWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    m_emptyTableWidget->setLayout(layout);

    QLabel *emptyWidget = new QLabel;
    emptyWidget->setText(QString("<i> You have not yet imported any data. </i> <br> <i> ")+
                         QString(" click the icon below to import new data</i>"));

    layout->addWidget(emptyWidget, 0, Qt::AlignHCenter |Qt::AlignBottom);

    QPushButton* importDataButton = new QPushButton(this);
    importDataButton->setFixedSize(64,64);
    importDataButton->setObjectName("blProjectImportDataButton");
    connect(importDataButton, SIGNAL(clicked()), this, SIGNAL(askImportData()));
    layout->addWidget(importDataButton, 0, Qt::AlignHCenter |Qt::AlignBottom);

    m_emptyTableWidget->setFixedHeight(300);
    m_emptyTableWidget->setFixedWidth(700);
    emptyWidget->setStyleSheet("QLabel{qproperty-alignment: AlignCenter;}");
    m_emptyTableWidget->setStyleSheet(".QWidget{border: 1px dashed black;}");
    return m_emptyTableWidget;
}
