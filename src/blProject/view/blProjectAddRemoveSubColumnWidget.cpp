/// \file blProjectAddRemoveSubColumnWidget.cpp
/// \brief blProjectAddRemoveSubColumnWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectAddRemoveSubColumnWidget.h"

blProjectAddRemoveSubColumnWidget::blProjectAddRemoveSubColumnWidget(QWidget *parent )
    :QWidget(parent){

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);

    QTabWidget *tab = new QTabWidget(this);
    layout->addWidget(tab);

    QWidget *addWidget = this->createAddWidget();
    tab->addTab(addWidget, tr("Add column"));

    QWidget *removeWidget = this->createRemoveWidget();
    tab->addTab(removeWidget, tr("Remove column"));
}

void blProjectAddRemoveSubColumnWidget::setMainColumnName(QString name){
    m_mainColumnName = name;
}

void blProjectAddRemoveSubColumnWidget::emitAdd(){
    emit askAddRemoveSubColumn(m_mainColumnName, m_addColumnNameEdit->text(), true);
}

void blProjectAddRemoveSubColumnWidget::emitRemove(){
    emit askAddRemoveSubColumn(m_mainColumnName, m_removeColumnNamesBox->currentText(), false);
}

QWidget *blProjectAddRemoveSubColumnWidget::createAddWidget(){

    QWidget *widget = new QWidget;
    widget->setMaximumHeight(200);
    widget->setMaximumWidth(700);
    QGridLayout *layout = new QGridLayout;
    widget->setLayout(layout);

    QLabel *title = new QLabel(tr("Column Name: "), this);
    m_addColumnNameEdit = new QLineEdit(this);

    QPushButton *validate = new QPushButton(tr("Add"), this);
    validate->setObjectName("btnDefault");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");

    connect(validate, SIGNAL(clicked()), this, SLOT(emitAdd()));
    connect(cancel, SIGNAL(clicked()), this, SIGNAL(cancel()));

    layout->addWidget(title, 0, 0, 1,1,Qt::AlignRight);
    layout->addWidget(m_addColumnNameEdit, 0, 1, 1, 3);
    layout->addWidget(cancel, 1, 2, 1, 1);
    layout->addWidget(validate, 1, 3, 1, 1);

    return widget;
}

QWidget *blProjectAddRemoveSubColumnWidget::createRemoveWidget(){

    QWidget *widget = new QWidget;
    widget->setMaximumHeight(200);
    widget->setMaximumWidth(700);
    QGridLayout *layout = new QGridLayout;
    widget->setLayout(layout);

    QLabel *title = new QLabel(tr("Column Name: "), this);
    m_removeColumnNamesBox = new QComboBox(this);

    QPushButton *validate = new QPushButton(tr("Remove"), this);
    validate->setObjectName("btnDefault");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");

    connect(validate, SIGNAL(clicked()), this, SLOT(emitRemove()));
    connect(cancel, SIGNAL(clicked()), this, SIGNAL(cancel()));

    layout->addWidget(title, 0, 0, 1,1,Qt::AlignRight);
    layout->addWidget(m_removeColumnNamesBox, 0, 1, 1, 3);
    layout->addWidget(cancel, 1, 2, 1, 1);
    layout->addWidget(validate, 1, 3, 1, 1);

    return widget;
}

void blProjectAddRemoveSubColumnWidget::setSubColumnsNames(QStringList names){
    m_removeColumnNamesBox->clear();
    m_removeColumnNamesBox->addItems(names);
}
