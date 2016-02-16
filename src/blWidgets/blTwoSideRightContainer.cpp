/// \file blTwoSideRightContainer.cpp
/// \brief blTwoSideRightContainer
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#include "blTwoSideRightContainer.h"

blTwoSideRightContainer::blTwoSideRightContainer(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(2,5,2,7);
    m_layout->setSpacing(0);

    QWidget *widget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout();
    totalLayout->setContentsMargins(0,0,0,0);
    totalLayout->setSpacing(0);
    totalLayout->addWidget(widget, 1, Qt::AlignTop);
    widget->setLayout(m_layout);
    this->setLayout(totalLayout);

    widget->setObjectName("blTwoSideRightContainer");
    //this->setMaximumHeight(800);
}

void blTwoSideRightContainer::addWidget(QWidget* widget){
    m_layout->addWidget(widget, 1, Qt::AlignTop);
}
