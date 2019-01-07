/// \file blProjectEditorTagWidget.cpp
/// \brief blProjectEditorTagWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorTagWidget.h"
#include <QtWidgets>

blProjectEditorTagWidget::blProjectEditorTagWidget(blProjectTag *tag, QWidget *parent) :
    QWidget(parent)
{

    m_tag = tag;

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    QLabel *label = new QLabel(this);
    label->setText(tag->name());
    layout->addWidget(label, 1, Qt::AlignLeft);

    QPushButton *removeButton = new QPushButton(tr("Remove"), this);
    removeButton->setObjectName("btnDanger");
    layout->addWidget(removeButton, 0, Qt::AlignRight);
    connect(removeButton, SIGNAL(released()), this, SLOT(emitAskRemoveTag()));

    this->setLayout(layout);

}

void blProjectEditorTagWidget::emitAskRemoveTag(){

    int response = QMessageBox::question(this,"Delete tag", "Are you sure you want to delete the tag: " + m_tag->name() + " ?", QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes){
        emit askRemoveTag(m_tag);
    }

}

blProjectTag* blProjectEditorTagWidget::tag(){
    return m_tag;
}
