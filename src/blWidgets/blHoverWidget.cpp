/// \file blHoverWidget.cpp
/// \brief blHoverWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#include "blHoverWidget.h"
#include "blClickableIcon.h"

blHoverWidget::blHoverWidget(blHoverableWidget *parent) :
    QWidget(parent)
{

    QWidget *thisWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(thisWidget);

    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    thisWidget->setLayout(m_layout);
    this->setLayout(layout);


    blClickableIcon *closeButton = new blClickableIcon("theme/cross_white.png", "", 15,15,1);
    closeButton->setFixedSize(15,15);
    closeButton->setObjectName("blHoverWidgetCloseButton");
    closeButton->setStyleSheet("#blHoverWidgetCloseButton{background-color:transparent; color:white;}");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(emitClose()));
    m_layout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);

    if (parent){
        this->resize(parent->size());
        //this->setFixedSize(parent->size());
    }

    connect(parent, SIGNAL(resized(int,int)), this, SLOT(resizeSlot(int, int)));
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //m_layout->addWidget(new QWidget,1, Qt::AlignTop);

    thisWidget->setObjectName("blHoverWidget");
    thisWidget->setStyleSheet("#blHoverWidget{background-color: rgba(58,58,58,97%);}");
}

void blHoverWidget::addWidget(QWidget *w){
    m_layout->addWidget(w);
}

void blHoverWidget::emitClose(){
    emit askClose();
    emit askClose(this);
}

void blHoverWidget::resizeSlot(int w, int h){
    this->resize(w,h);
}
