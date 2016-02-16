/// \file blProjectViewColumnHeader.cpp
/// \brief blProjectViewColumnHeader
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectViewColumnHeader.h"

blProjectViewColumnHeader::blProjectViewColumnHeader(QString title, QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(0,0,0,0);
    QWidget *tableHeader = new QWidget;
    totalLayout->addWidget(tableHeader);
    tableHeader->setObjectName("blProjectTableHeaderWidget");
    QHBoxLayout *layout = new QHBoxLayout;
    tableHeader->setLayout(layout);
    this->setLayout(totalLayout);

    m_titleLabel = new QLabel(title);
    m_titleLabel->setObjectName("blProjectTableHeaderWidgetTitleLabel");
    m_selectorWidget = new blProjectViewColumnSelector;
    connect(m_selectorWidget, SIGNAL(visibleColumns(QStringList)), this, SLOT(emitVisibleColumns(QStringList)));

    m_paramWidget = new blProjectViewColumnParameters(this);

    m_deleteWidget = new blClickableIcon("theme/trash_white.png", "", 30,30,2, this);
    connect(m_deleteWidget, SIGNAL(clicked()), this, SLOT(emitDeleteColumn()));

    m_addRemoveColumns = new QPushButton(this);
    m_addRemoveColumns->setObjectName("blProjectViewColumnHeaderAddRemoveColumnsButton");
    m_addRemoveColumns->setFixedSize(30,30);
    connect(m_addRemoveColumns, SIGNAL(clicked()), this, SLOT(emitAddRemoveColumns()));

    m_calculateThumbnail = new QPushButton(this);
    m_calculateThumbnail->setObjectName("blProjectViewColumnHeaderThumbnailButton");
    m_calculateThumbnail->setFixedSize(30,30);
    connect(m_calculateThumbnail, SIGNAL(clicked()), this, SLOT(emitComputeThumbnails()));

    layout->addWidget(m_paramWidget, 0, Qt::AlignLeft);
    layout->addWidget(m_selectorWidget, 0, Qt::AlignLeft);
    layout->addWidget(m_titleLabel, 1, Qt::AlignCenter);
    layout->addWidget(m_deleteWidget, 0, Qt::AlignRight);
    layout->addWidget(m_addRemoveColumns, 0, Qt::AlignRight);
    layout->addWidget(m_calculateThumbnail, 0, Qt::AlignRight);

    tableHeader->setStyleSheet("#blProjectTableHeaderWidget{background-color: rgba(01,81,81,65%)}");
    m_titleLabel->setStyleSheet("#blProjectTableHeaderWidgetTitleLabel{qproperty-alignment: AlignCenter; color: white; font: bold 14px;}");
}

void blProjectViewColumnHeader::setTrashVisible(bool value){
    m_deleteWidget->setVisible(value);
}

void blProjectViewColumnHeader::setParamVisible(bool value){
    m_paramWidget->setVisible(value);
}

blProjectViewColumnSelector *blProjectViewColumnHeader::selector(){
    return m_selectorWidget;
}

void blProjectViewColumnHeader::addColumn(QString columnName){
    m_selectorWidget->addColumn(columnName);
}

void blProjectViewColumnHeader::emitVisibleColumns(QStringList selectedHeaders){
    emit visibleColumns(selectedHeaders);
}

void blProjectViewColumnHeader::setTitle(QString title){
    m_titleLabel->setText(title);
}

QString blProjectViewColumnHeader::title(){
    return m_titleLabel->text();
}

void blProjectViewColumnHeader::emitDeleteColumn(){
    int answer = QMessageBox::question(this, tr("Delete Column"),
                                       "This will definitively delete the column ant it's data",
                                       QMessageBox ::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes){
        emit askDeleteColumn(m_titleLabel->text());
    }
}

void blProjectViewColumnHeader::emitComputeThumbnails(){
    emit askComputeThumbnails(m_titleLabel->text());
}

void blProjectViewColumnHeader::emitAddRemoveColumns(){
     emit askAddRemoveColumns(m_titleLabel->text());
}

blProjectViewColumnParameters* blProjectViewColumnHeader::parameterEditor(){
    return m_paramWidget;
}
