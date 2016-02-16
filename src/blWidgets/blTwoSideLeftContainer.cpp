/// \file blTwoSideLeftContainer.cpp
/// \brief blTwoSideLeftContainer
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#include "blTwoSideLeftContainer.h"

blTwoSideLeftContainer::blTwoSideLeftContainer(QWidget *parent) :
    QWidget(parent)
{

    m_layout = new QHBoxLayout();
    m_bubleWidget = new QLabel(this);
    //m_bubleWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_bubleWidget->setFixedWidth(32);
    //m_layout->addWidget(m_bubleWidget, 0, Qt::AlignRight);
    m_layout->addWidget(m_bubleWidget);

    setClicked(false);
    this->setLayout(m_layout);

    QWidget *widget = new QWidget(this);
    widget->setLayout(m_layout);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    QVBoxLayout *totalLayout = new QVBoxLayout();
    totalLayout->addWidget(widget);
    totalLayout->setContentsMargins(0,0,0,0);
    this->setLayout(totalLayout);

    widget->setObjectName("blTwoSideLeftContainer");
}

void blTwoSideLeftContainer::setWidget(QWidget *widget){
    m_layout->insertWidget(0, widget);
}

void blTwoSideLeftContainer::setClicked(bool value){
    if (value){
       m_bubleWidget->setPixmap(QPixmap::fromImage(QImage("theme/bubblearrow.png")));
    }
    else{
       m_bubleWidget->setPixmap(QPixmap::fromImage(QImage("theme/bubbleclose.png")));
    }
}
