/// \file blProjectNewFormWidgetFilter.cpp
/// \brief blProjectNewFormWidgetFilter
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectNewFormWidgetFilter.h"
#include "blProjectNewFormWidgetFilterSingle.h"

blProjectNewFormWidgetFilter::blProjectNewFormWidgetFilter(QWidget *parent) : QWidget (parent)
{

    m_layout = new QVBoxLayout;

    // title
    QLabel *title = new QLabel(tr("Filters"));
    title->setObjectName("blLabelFormHeader1");
    m_layout->addWidget(title);

    // More
    QPushButton *moreButton = new QPushButton(tr("More"));
    moreButton->setObjectName("btnPrimary");
    connect(moreButton, SIGNAL(clicked()), this, SLOT(addFilter()));
    m_layout->addWidget(moreButton, 0, Qt::AlignLeft);

    // View
    QPushButton *viewButton = new QPushButton(tr("View"));
    viewButton->setObjectName("btnPrimary");
    connect(viewButton, SIGNAL(clicked()), this, SLOT(emitViewFiltering()));
    m_layout->addWidget(viewButton, 0, Qt::AlignRight);

    this->setLayout(m_layout);

    // first filter
    m_countor = 0;
    addFilter();
}


// private slots
void blProjectNewFormWidgetFilter::addFilter(){
    m_countor++;

    //qDebug() << "m_layout->count()-2 = " << m_layout->count()-2;
    //qDebug() << "m_countor = " << m_countor;
    blProjectNewFormWidgetFilterSingle *filterWidget = new blProjectNewFormWidgetFilterSingle("Filter " + QString::number(m_countor), m_countor);
    m_layout->insertWidget(m_layout->count()-2, filterWidget);
    connect(filterWidget, SIGNAL(close(int)), this, SLOT(closeFilter(int)));
}

void blProjectNewFormWidgetFilter::emitViewFiltering(){
    emit askViewFiltering();
}

void blProjectNewFormWidgetFilter::closeFilter(int idx){

    for (int i = 1 ; i < m_layout->count() ; ++i){
        blProjectNewFormWidgetFilterSingle *wc = dynamic_cast<blProjectNewFormWidgetFilterSingle*>(m_layout->itemAt(i)->widget());
        if (wc){
            if (wc->idx() == idx){
                delete wc;
            }
        }
    }
    for (int i = 1 ; i < m_layout->count() ; ++i){
        blProjectNewFormWidgetFilterSingle *wc = dynamic_cast<blProjectNewFormWidgetFilterSingle*>(m_layout->itemAt(i)->widget());
        if (wc){
            if (wc->idx() > idx){
                wc->decreaseIdxByOne();
            }
        }
    }
    m_countor--;
}

QList<QStringList> blProjectNewFormWidgetFilter::getFiltersInfo(){

    QList<QStringList> infos;
    for (int i = 1 ; i < m_layout->count() ; ++i){
        blProjectNewFormWidgetFilterSingle *wc = dynamic_cast<blProjectNewFormWidgetFilterSingle*>(m_layout->itemAt(i)->widget());
        if (wc){
            QStringList info = wc->getFilterInfo();
            infos.append(info);
        }
    }
    return infos;
}
