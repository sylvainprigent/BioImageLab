/// \file blHoverableWidget.cpp
/// \brief blHoverableWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#include "blHoverableWidget.h"

blHoverableWidget::blHoverableWidget(QWidget *parent) :
    QWidget(parent)
{
}


void blHoverableWidget::resizeEvent( QResizeEvent * event ){
    emit resized(event->size().width(), event->size().height());
}
