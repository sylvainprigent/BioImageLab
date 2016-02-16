/// \file blProjectViewColumnParameters.cpp
/// \brief blProjectViewColumnParameters
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectViewColumnParameters.h"

blProjectViewColumnParameters::blProjectViewColumnParameters(QWidget *parent) :
    blClickableIcon("theme/settings.png", "" , 30,30, 2, parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(showEditor()));

    createEditor();
}

void blProjectViewColumnParameters::createEditor(){

    m_editor = new QWidget();
    m_editor->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_editor->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

    QGridLayout *layout = new QGridLayout;

    blClickableIcon* closeCross = new blClickableIcon("theme/close.png", "", 12,12,0,this);
    m_dateLabel = new QLabel(this);
    QLabel *editCompositionTitle = new QLabel(tr("Tool:"), this);
    QPushButton *openCompoButton = new QPushButton(tr("open"), this);

    layout->addWidget(closeCross, 0,2,1,1,Qt::AlignTop | Qt::AlignRight);
    layout->addWidget(m_dateLabel, 1,0,1,2);
    layout->addWidget(editCompositionTitle, 2,0,1,1);
    layout->addWidget(openCompoButton, 2,1,1,1);

    m_editor->setLayout(layout);

    connect(closeCross, SIGNAL(clicked()), this, SLOT(hideEditor()));
    connect(openCompoButton, SIGNAL(clicked()), this, SLOT(emitOpenCompo()));
    setDate("");
    m_editor->setVisible(false);
}

void blProjectViewColumnParameters::setDate(QString date){

    QString text = "<br>Date:</br> " + date;
    m_dateLabel->setText(text);
}

void blProjectViewColumnParameters::setCompoUrl(QString url){
    m_compoUrl = url;
}

void blProjectViewColumnParameters::emitOpenCompo(){
    qDebug() << "blProjectViewColumnParameters emit open compo:" << m_compoUrl;
    emit askOpenCompo(m_compoUrl);
}

void blProjectViewColumnParameters::showEditor(){

    m_editor->setVisible(true);

    int x = m_editor->cursor().pos().x();
    int y = m_editor->cursor().pos().y();
    const int width = QApplication::desktop()->width();
    if (width -x < m_editor->width() ){
        x = width - m_editor->width();
    }

    m_editor->move(x,y);
}

void blProjectViewColumnParameters::hideEditor(){
    m_editor->setVisible(false);
}
