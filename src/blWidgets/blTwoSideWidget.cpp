/// \file blTwoSideWidget.h
/// \brief blTwoSideWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#include "blTwoSideWidget.h"
#include "blTwoSideLeftContainer.h"
#include "blTwoSideRightContainer.h"

blTwoSideWidget::blTwoSideWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QGridLayout();
    m_curentRightWidgetIdx = -1;
    m_curentLeftWidgetIdx = -1;
    m_numberLeftWidget = 0;
    m_rowDelta = 0;
    m_leftWidth = -1;

    //this->setLayout(m_layout);
    m_layout->setVerticalSpacing(0);
    m_layout->setHorizontalSpacing(0);
    m_layout->setContentsMargins(35,5,35,5);

    m_widget = new QWidget(this);
    m_widget->setLayout(m_layout);

    totalLayout = new QVBoxLayout(this);
    totalLayout->setContentsMargins(0,0,0,0);
    totalLayout->addWidget(m_widget);

    m_widget->setObjectName("blTwoSideWidget");
}

blTwoSideWidget::~blTwoSideWidget()
{
    
}


// slots
void blTwoSideWidget::addLeftWidget(QWidget *widget){
    blTwoSideLeftContainer* container = new blTwoSideLeftContainer();
    widget->setParent(this);
    container->setWidget(widget);
    if(m_leftWidth>0){
        container->setFixedWidth(m_leftWidth);
    }

    m_layout->addWidget(container, m_numberLeftWidget, 0,1,1, Qt::AlignTop | Qt::AlignLeft);
    m_numberLeftWidget++;
}

void blTwoSideWidget::setRightWidget(int row, QWidget *widget, int expanding){

    // uncheck the previous left widget
    if (m_curentLeftWidgetIdx > -1){
        blTwoSideLeftContainer* container = dynamic_cast<blTwoSideLeftContainer*>(m_layout->itemAtPosition(m_curentLeftWidgetIdx, 0)->widget());
        container->setClicked(false);
    }

    // remove the previous right widget
    if (m_curentRightWidgetIdx > -1){
        QWidget *w = m_layout->itemAtPosition(m_curentRightWidgetIdx, 1)->widget();
        if (w){
            delete w;
        }
    }

    // add the new right widget
    m_curentRightWidgetIdx = row + m_rowDelta;
    if (m_curentRightWidgetIdx < 0){m_curentRightWidgetIdx = 0;}
    blTwoSideRightContainer *rightContainer = new blTwoSideRightContainer(this);
    rightContainer->addWidget(widget);

    m_layout->addWidget(rightContainer, m_curentRightWidgetIdx, 1,expanding, Qt::AlignBottom);
    //rightContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding );
    // check the new left widget
    m_curentLeftWidgetIdx = row;
    blTwoSideLeftContainer* container = dynamic_cast<blTwoSideLeftContainer*>(m_layout->itemAtPosition(m_curentLeftWidgetIdx, 0)->widget());
    if (container)
        container->setClicked(true);
}

void blTwoSideWidget::setRowDelta(int rowDelta){
    m_rowDelta = rowDelta;
}

void blTwoSideWidget::setFixedLeftWidth(int width){
    m_leftWidth = width;
}

void blTwoSideWidget::free(){


    delete m_widget;

    //delete m_layout;
    m_layout = new QGridLayout();
    m_widget = new QWidget(this);
    totalLayout->addWidget(m_widget);
    m_widget->setLayout(m_layout);

    m_layout->setVerticalSpacing(0);
    m_layout->setHorizontalSpacing(0);
    m_layout->setContentsMargins(35,5,35,5);

    m_widget->setObjectName("blTwoSideWidget");

    m_curentRightWidgetIdx = -1;
    m_curentLeftWidgetIdx = -1;
    m_numberLeftWidget = 0;
    m_rowDelta = 0;
    m_leftWidth = -1;

}
