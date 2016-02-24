#include "blHomeWidget.h"
#include "blHomeWidgetTile.h"

blHomeWidget::blHomeWidget(QWidget *parent)
    : QWidget(parent){

    m_layout = new QVBoxLayout;
    m_layout->addWidget(new QWidget(this), 1, Qt::AlignTop);
    this->setLayout(m_layout);
}

void blHomeWidget::addSection(QString name, int strech, bool useFlowLayout){

    blHideableWidget *sectionWidget = new blHideableWidget(name, 2, this, useFlowLayout);
    m_layout->insertWidget(0, sectionWidget, strech, Qt::AlignTop);
    m_sectionsNames.append(name);
    m_sectionsWidgets.append(sectionWidget);
}

void blHomeWidget::addTile(QString section, blHomeTileInfo info){

    for (int i = 0 ; i < m_sectionsNames.count() ; ++i){
        if (m_sectionsNames[i] == section){
            blHomeWidgetTile *tile = new blHomeWidgetTile(info, this);
            m_sectionsWidgets[i]->addWidget(tile);
            connect(tile, SIGNAL(clicked(blHomeTileInfo)), this, SIGNAL(action(blHomeTileInfo)));
            break;
        }
    }
}

void blHomeWidget::addWidget(QString section, QWidget *widget){

    for (int i = 0 ; i < m_sectionsNames.count() ; ++i){
        if (m_sectionsNames[i] == section){
            m_sectionsWidgets[i]->addWidget(widget);
            break;
        }
    }
}
