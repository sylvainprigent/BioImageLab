/// \file blProjectNewFormWidgetFilterSingle.cpp
/// \brief blProjectNewFormWidgetFilterSingle
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectNewFormWidgetFilterSingle.h"
#include <blWidgets/blClickableIcon.h>

blProjectNewFormWidgetFilterSingle::blProjectNewFormWidgetFilterSingle(QString title, int idx, QWidget *parent) :
    QWidget(parent)
{

    m_idx = idx;
    QGridLayout *layout = new QGridLayout;


    titleLabel = new QLabel("<b>" + title + ":</b>");
    blClickableIcon *closeButton = new blClickableIcon("theme/close.png", "", 16,16,2);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(emitClose()));
    layout->addWidget(titleLabel, 0, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(closeButton, 0, 1, 1, 1, Qt::AlignRight);

    QLabel *startLabel = new QLabel(tr("      Starts with"));
    startLineEdit = new QLineEdit;
    layout->addWidget(startLabel, 1, 0);
    layout->addWidget(startLineEdit, 1, 1);

    QLabel *containsLabel = new QLabel(tr("<i>and</i> Contains"));
    containsLineEdit = new QLineEdit;
    layout->addWidget(containsLabel, 2, 0);
    layout->addWidget(containsLineEdit, 2, 1);

    QLabel *endsLabel = new QLabel(tr("<i>and</i> Ends by"));
    endsLineEdit = new QLineEdit;
    layout->addWidget(endsLabel, 3, 0);
    layout->addWidget(endsLineEdit, 3, 1);

    this->setLayout(layout);
}

QStringList blProjectNewFormWidgetFilterSingle::getFilterInfo(){
    QStringList info;
    info.append(startLineEdit->text());
    info.append(containsLineEdit->text());
    info.append(endsLineEdit->text());

    return info;
}

void blProjectNewFormWidgetFilterSingle::emitClose(){
    emit close(this);
    emit close(m_idx);
}

void blProjectNewFormWidgetFilterSingle::decreaseIdxByOne(){
    m_idx--;
    titleLabel->setText("<b>Filter " + QString::number(m_idx) + ":</b>");
}

int blProjectNewFormWidgetFilterSingle::idx(){
    return m_idx;
}
