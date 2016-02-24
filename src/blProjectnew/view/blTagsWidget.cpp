/// \file blTagsWidget.cpp
/// \brief blTagsWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) blimbio 2014

#include "blTagsWidget.h"
#include "blWidgets/blFlowLayout.h"
#include "blWidgets/blClickableIcon.h"
#include "../model/blTagsInfo.h"

// ////////////////////////////////////////////////
//                blTagManagerWidget
// ////////////////////////////////////////////////
blTagManagerWidget::blTagManagerWidget(QWidget *parent) : QWidget(parent){

    QGridLayout *tagLayout = new QGridLayout;
    tagLayout->setContentsMargins(0,0,0,0);
    this->setLayout(tagLayout);

    m_addTagEdit = new QLineEdit(this);
    m_addTagButton = new QPushButton(tr("add"), this);
    m_addTagButton->setObjectName("btnDefault");
    connect(m_addTagButton, SIGNAL(released()), this, SLOT(addTag()));
    tagLayout->addWidget(m_addTagEdit, 0, 1, 1, 1);
    tagLayout->addWidget(m_addTagButton, 0, 2, 1, 1);

    m_tags = new blTagsWidget(this);
    connect(m_tags, SIGNAL(tagAdded()), this, SIGNAL(tagAdded()));
    tagLayout->addWidget(m_tags, 1, 0, 1, 2);
}

void blTagManagerWidget::addTag(){
    if (m_addTagEdit->text() != ""){
        m_tags->addTag(m_tags->lastId()+1, m_addTagEdit->text(), false);
    }
    m_addTagEdit->setText("");
}

void blTagManagerWidget::setTags(QList<blTagInfo> tags){
    for(int i = 0 ; i < tags.count() ; ++i){
        blTagInfo tagi = tags[i];
        m_tags->addTag(tagi.id(), tagi.name(), false);
    }
}

blTagsInfo blTagManagerWidget::getTagsInfo(){
    return m_tags->tagsInfo();
}


// ////////////////////////////////////////////////
//                blTagManagerWidget
// ////////////////////////////////////////////////
blTagsWidget::blTagsWidget(QWidget *parent) :
    QWidget(parent)
{

    m_layout = new blFlowLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(1);
    this->setLayout(m_layout);
}

void blTagsWidget::addTag(int id, QString tag, bool closable){
    blTagContainer *label = new blTagContainer(id, " " + tag + " ", closable);
    m_layout->addWidget(label);
    emit tagAdded();
}

void blTagsWidget::addTags(QList<int> id, QStringList tags, bool closable){
    for (int i = 0 ; i < tags.size() ; ++i){
        addTag(id[i], tags[i], closable);
    }
}

int blTagsWidget::lastId(){
    int lastIdVal = 0;
    for (int i = 0 ; i < m_layout->count() ; ++i){
        if (m_layout->itemAt(i)->widget()){
            blTagContainer *w = dynamic_cast<blTagContainer *>(m_layout->itemAt(i)->widget());
            if (w){
                int curentTagId = w->id();
                if(curentTagId > lastIdVal){
                    lastIdVal = curentTagId;
                }
            }
        }
    }
    return lastIdVal;
}

blTagsInfo blTagsWidget::tagsInfo(){
    blTagsInfo tags;
    for (int i = 0 ; i < m_layout->count() ; ++i){
        if (m_layout->itemAt(i)->widget()){
            blTagContainer *w = dynamic_cast<blTagContainer *>(m_layout->itemAt(i)->widget());
            if (w){
                int curentTagId = w->id();
                QString curentTag = w->name();
                curentTag = curentTag.simplified();
                curentTag.replace( " ", "" );
                blTagInfo curentTagInfo;
                curentTagInfo.setId(curentTagId);
                curentTagInfo.setName(curentTag);
                tags.set(curentTagId, curentTagInfo);
            }
        }
    }
    return tags;
}

QStringList blTagsWidget::tags(){
    QStringList tags;
    for (int i = 0 ; i < m_layout->count() ; ++i){
        if (m_layout->itemAt(i)->widget()){
            blTagContainer *w = dynamic_cast<blTagContainer *>(m_layout->itemAt(i)->widget());
            if (w){
                QString curentTag = w->name();
                curentTag = curentTag.simplified();
                curentTag.replace( " ", "" );
                tags.append(curentTag);
            }
        }
    }
    return tags;
}

void blTagsWidget::removeAllTags(){
    QLayoutItem* item;
    while ( ( item = m_layout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}

// ////////////////////////////////////////////////
//  blTagContainer
// ////////////////////////////////////////////////
blTagContainer::blTagContainer(int id, QString name, bool closable){

    m_id = id;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    m_label = new QLabel(name);
    layout->addWidget(m_label);

    if (closable){
        blClickableIcon *icon = new blClickableIcon("theme/close.png", "", 12,12,1);
        layout->addWidget(icon);
        connect(icon, SIGNAL(clicked()), this, SLOT(autoDesctroy()));
    }

    QWidget *thisWidget = new QWidget;
    thisWidget->setLayout(layout);

    thisWidget->setStyleSheet("QWidget{background-color: #585858;}");
    m_label->setStyleSheet("QLabel{background-color: #ffffff; border: 1px solid #585858;}");

    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->addWidget(thisWidget);
    this->setLayout(totalLayout);
}

int blTagContainer::id(){
    return m_id;
}

void blTagContainer::setId(int id){
    m_id = id;
}

QString blTagContainer::name(){
    return m_label->text();
}
void blTagContainer::setName(QString name){
    m_label->setText(name);
}

void blTagContainer::autoDesctroy(){
    delete this;
}

