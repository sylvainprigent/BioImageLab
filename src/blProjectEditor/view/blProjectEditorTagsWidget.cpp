/// \file blProjectEditorTagsWidget.cpp
/// \brief blProjectEditorTagsWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorTagsWidget.h"
#include "blProjectEditorTagWidget.h"
#include <QtWidgets>

blProjectEditorTagsWidget::blProjectEditorTagsWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout* layout = new QVBoxLayout;
    this->setObjectName("blProjectEditorInfoWidget");

    QLabel *title = new QLabel(tr("Tags"), this);
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title);

    QWidget *addWidget = new QWidget(this);
    QHBoxLayout *addLayout = new QHBoxLayout;
    QPushButton *addButton = new QPushButton(tr("Add"), this);
    addButton->setObjectName("btnDefault");
    m_addEdit = new QLineEdit(this);
    addLayout->addWidget(m_addEdit, 1);
    addLayout->addWidget(addButton, 0, Qt::AlignLeft);
    addWidget->setLayout(addLayout);
    layout->addWidget(addWidget);

    QWidget *tagListWidget = new QWidget(this);
    m_tagListLayout = new QVBoxLayout;
    tagListWidget->setLayout(m_tagListLayout);
    layout->addWidget(tagListWidget);

    layout->addWidget(new QWidget(this), 1, Qt::AlignTop);
    this->setLayout(layout);

    connect(addButton, SIGNAL(released()), this, SLOT(emitAskAddTag()));

}

void blProjectEditorTagsWidget::setTags(QList<blProjectTag*> tags){

    for(int i = 0 ; i < tags.count() ; i++){
        blProjectEditorTagWidget *tagWidget = new blProjectEditorTagWidget(tags[i], this);
        connect(tagWidget, SIGNAL(askRemoveTag(blProjectTag*)), this, SIGNAL(askRemoveTag(blProjectTag*)));
        m_tagListLayout->addWidget(tagWidget);
    }
}

void blProjectEditorTagsWidget::addTag(blProjectTag *tag){
    blProjectEditorTagWidget *tagWidget = new blProjectEditorTagWidget(tag, this);
    connect(tagWidget, SIGNAL(askRemoveTag(blProjectTag*)), this, SIGNAL(askRemoveTag(blProjectTag*)));
    m_tagListLayout->insertWidget(0, tagWidget);
}

void blProjectEditorTagsWidget::removeTag(blProjectTag *tag){

    for (int i = 0 ; i < m_tagListLayout->count() ; i++){
        QLayoutItem* item = m_tagListLayout->itemAt(i);
        QWidget *widget = item->widget();
        if (widget){
            blProjectEditorTagWidget* tagWidget = qobject_cast<blProjectEditorTagWidget*>(widget);
            if (tagWidget){
                if (tagWidget->tag()->id() == tag->id()){
                    m_tagListLayout->removeItem(item);
                    delete item->widget();
                    delete item;
                }
            }
        }
    }

}

void blProjectEditorTagsWidget::emitAskAddTag(){
    blProjectTag *tag = new blProjectTag();
    tag->setName(m_addEdit->text());
    emit askAddTag(tag);
}
