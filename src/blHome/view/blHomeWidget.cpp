#include "blHomeWidget.h"
#include "blHomeWidgetTile.h"

blHomeWidget::blHomeWidget(QWidget *parent)
    : QWidget(parent){

    m_layout = new QVBoxLayout;
    m_layout->addWidget(new QWidget(this), 1, Qt::AlignTop);
    this->setLayout(m_layout);
}

void blHomeWidget::addSection(QString name){

    blHideableWidget *sectionWidget = new blHideableWidget(name, 2, this, true);
    m_layout->insertWidget(0, sectionWidget, 0, Qt::AlignTop);
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
