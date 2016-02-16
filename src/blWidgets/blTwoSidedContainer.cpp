/// \file blTwoSidedContainer.cpp
/// \brief blTwoSidedContainer
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#include "blTwoSidedContainer.h"
#include <QtGui>

blTwoSidedContainer::blTwoSidedContainer(QWidget *parent) :
    QWidget(parent)
{

    // 1- splitter
    //QVBoxLayout *layout = new QVBoxLayout;
    //layout->setContentsMargins(0,0,0,0);
    //this->setLayout(layout);
    QHBoxLayout *splitter = new QHBoxLayout;
    splitter->setContentsMargins(0,5,5,5);
    splitter->setSpacing(0);
    this->setLayout(splitter);
    //layout->addWidget(splitter);

    //splitter->setStyleSheet("QSplitter::handle {background: #585858;}");

    // 2- LeftWidget
    leftWidget = new QWidget(this);
    m_leftLayout = new QVBoxLayout;
    m_leftLayout->setContentsMargins(0,0,0,0);
    m_leftLayout->setSpacing(0);
    leftWidget->setLayout(m_leftLayout);
    leftWidget->setStyleSheet("background: #ffffff;");
    m_leftLayout->addWidget(new QWidget, 1);

    // scroll area
    scrollArea = new QScrollArea;
    scrollArea->setObjectName("blcDropBarScroll");
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(leftWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setContentsMargins(0,0,0,0);
    //scrollArea->setFixedWidth(700);
    //splitter->addWidget(scrollArea, 0, Qt::AlignLeft);
    splitter->addWidget(scrollArea);

    // 3- RightWidget
    rightWidget = new QWidget(this);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightWidget->setStyleSheet(".QWidget{background: #ffffff; border: none; border-radius: 7px;}");
    m_rightLayout = new QVBoxLayout;
    m_rightLayout->setContentsMargins(5,5,5,5);
    rightWidget->setLayout(m_rightLayout);
    splitter->addWidget(rightWidget);

}

//public slots:
void blTwoSidedContainer::addLeftWidget(QWidget *widget){
    blLeftTwoSidedSingleWidgetContainer *container = new blLeftTwoSidedSingleWidgetContainer(widget, this);
    connect(container, SIGNAL(clicked(blLeftTwoSidedSingleWidgetContainer*)), this, SLOT(changeSelectedWidget(blLeftTwoSidedSingleWidgetContainer*)));
    m_leftLayout->insertWidget(m_leftLayout->count()-1,container, 0, Qt::AlignTop);
}

//private slots:
void blTwoSidedContainer::changeSelectedWidget(blLeftTwoSidedSingleWidgetContainer* selectedWidget){
    for (int i = 0 ; i < m_leftLayout->count() ; ++i){
        if (m_leftLayout->itemAt(i)->widget()){
            blLeftTwoSidedSingleWidgetContainer *w = dynamic_cast<blLeftTwoSidedSingleWidgetContainer *>(m_leftLayout->itemAt(i)->widget());
            if (w){
                if (w == selectedWidget){
                    w->setSelected(true);
                    qDebug() << "emit clicker parameter widget";
                    emit clicked(selectedWidget->widget());
                }
                else{
                    w->setSelected(false);
                }
            }
        }
    }
}

void blTwoSidedContainer::removeLeftWidget(QWidget* widget){

    qDebug() << "blTwoSidedContainer::removeWidget : ";
    for (int i = 0 ; i < m_leftLayout->count() ; ++i){
        if (m_leftLayout->itemAt(i)->widget()){
            blLeftTwoSidedSingleWidgetContainer *w = dynamic_cast<blLeftTwoSidedSingleWidgetContainer *>(m_leftLayout->itemAt(i)->widget());
            if (w){
                if (w->widget() == widget){
                    delete w;
                    break;
                }
            }
        }
    }
    qDebug() << "blTwoSidedContainer::removeWidget done ";
}

void blTwoSidedContainer::resetRightWidget(){
    QLayoutItem* item;
    while ( ( item = m_rightLayout->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
    m_rightLayout->addWidget(new QWidget);
    rightWidget->setStyleSheet(".QWidget{background: #ffffff; border: none;}");
}

void blTwoSidedContainer::setRightWidget(QWidget *widget){
    QLayoutItem* item;
    while ( ( item = m_rightLayout->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
    m_rightLayout->addWidget(widget);
    rightWidget->setStyleSheet(".QWidget{background: #ffffff; border: 1px solid #5A8E8E; border-radius: 7px;}");
}

void blTwoSidedContainer::free(){

    qDebug() << "blTwoSidedContainer::free()";
    QLayoutItem* item;
    while ( ( item = m_leftLayout->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
    m_leftLayout->addWidget(new QWidget, 1);

    qDebug() << "blTwoSidedContainer::free() end";
}

void blTwoSidedContainer::setFixedLeftWidth(int width){
    leftWidget->setFixedWidth(width);
    scrollArea->setFixedWidth(width);
}

void blTwoSidedContainer::setSelectedLeftWidget(int row){

    for (int i = 0 ; i < m_leftLayout->count() ; ++i){
        if (m_leftLayout->itemAt(i)->widget()){
            blLeftTwoSidedSingleWidgetContainer *w = dynamic_cast<blLeftTwoSidedSingleWidgetContainer *>(m_leftLayout->itemAt(i)->widget());
            if (w){
                if (i == row){
                    w->setSelected(true);
                }
                else{
                    w->setSelected(false);
                }
            }
        }
    }
}

// /////////////////////////////////////////////////
//        blLeftTwoSidedSingleWidgetContainer
// /////////////////////////////////////////////////
blLeftTwoSidedSingleWidgetContainer::blLeftTwoSidedSingleWidgetContainer(QWidget *widget, QWidget* parent)
    : QWidget(parent){


    m_widget = widget;

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    m_rightMargin = new QLabel;
    m_rightMargin->setFixedWidth(16);

    //layout->addWidget(m_topMargin, 0,0,1,3);
    //layout->addWidget(m_leftMargin, 1,0,1,1);
    layout->addWidget(widget, 0,0,1,1);
    layout->addWidget(m_rightMargin, 0,1,1,1, Qt::AlignRight);
    //layout->addWidget(m_bottomMargin, 2,0,1,3);

    this->setLayout(layout);

}

void blLeftTwoSidedSingleWidgetContainer::setSelected(bool selected){

    if (selected){
        m_rightMargin->setPixmap(QPixmap::fromImage(QImage("theme/bubblearrowsmall.png")));
    }
    else{
        m_rightMargin->setPixmap(QPixmap::fromImage(QImage("theme/bubbleDarkclose.png")));
    }
}

QWidget* blLeftTwoSidedSingleWidgetContainer::widget(){
    return m_widget;
}

void blLeftTwoSidedSingleWidgetContainer::mouseReleaseEvent ( QMouseEvent * ){
    emit clicked(this);
}
