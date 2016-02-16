/// \file blProjectAddImageWidget.cpp
/// \brief blProjectAddImageWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectAddImageWidget.h"
#include "blProjectNewFormWidget.h"

#include <QtGui>

blProjectAddImageWidget::blProjectAddImageWidget(QString viewersDir, QString binariesDir, QWidget *parent) :
    QWidget(parent)
{

    m_viewersDir = viewersDir;
    m_binariesDir = binariesDir;
    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);

    QTabWidget *tab = new QTabWidget(this);
    layout->addWidget(tab);

    QWidget *addSingle = createAddSingleImageWidget();
    tab->addTab(addSingle, tr("Add single image"));

    QWidget *addMultiple = createAddMultipleImageWidget();
    tab->addTab(addMultiple, tr("Add folder"));
}

QWidget *blProjectAddImageWidget::createAddSingleImageWidget(){

    QWidget *widget = new QWidget;
    widget->setMaximumHeight(200);
    widget->setMaximumWidth(700);
    QGridLayout *layout = new QGridLayout;
    widget->setLayout(layout);

    QLabel *title = new QLabel(tr("Image path: "), this);
    m_browseBar = new blBrowseBarWidget(false, "", this);
    //m_browseBar->setMaximumWidth(600);
    QPushButton *validate = new QPushButton(tr("Add"), this);
    validate->setObjectName("btnDefault");
    //validate->setMaximumWidth(100);
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");
    //validate->setMaximumWidth(100);

    connect(validate, SIGNAL(clicked()), this, SLOT(emitAddSingleImage()));
    connect(cancel, SIGNAL(clicked()), this, SIGNAL(cancel()));

    layout->addWidget(title, 0, 0, 1,1,Qt::AlignRight);
    layout->addWidget(m_browseBar, 0, 1, 1, 3);
    layout->addWidget(cancel, 1, 2, 1, 1);
    layout->addWidget(validate, 1, 3, 1, 1);

    return widget;
}

void blProjectAddImageWidget::emitAddSingleImage(){
    qDebug() << "emit add image: " << m_browseBar->text();
    emit askAddSingleImage(m_browseBar->text());
    emit validated();
    m_browseBar->setText("");
}

QWidget* blProjectAddImageWidget::createAddMultipleImageWidget(){

    blProjectNewFormWidget *form = new blProjectNewFormWidget(m_viewersDir, m_binariesDir, this, false);
    connect(form, SIGNAL(askCancel()), this, SIGNAL(cancel()));
    connect(form, SIGNAL(askCreateProject(blProjectControler*)), this, SLOT(emitAskAddProject(blProjectControler*)));
    return form;
}

void blProjectAddImageWidget::emitAskAddProject(blProjectControler* controler){
    emit askAddProject(controler);
}
