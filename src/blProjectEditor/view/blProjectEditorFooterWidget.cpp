/// \file blProjectEditorFooterWidget.cpp
/// \brief blProjectEditorFooterWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorFooterWidget.h"
#include <QtWidgets>

blProjectEditorFooterWidget::blProjectEditorFooterWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel("Hello footer !");

    layout->addWidget(label);
    this->setLayout(layout);

}
