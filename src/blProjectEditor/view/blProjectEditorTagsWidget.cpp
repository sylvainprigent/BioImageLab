/// \file blProjectEditorTagsWidget.cpp
/// \brief blProjectEditorTagsWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorTagsWidget.h"
#include <QtWidgets>

blProjectEditorTagsWidget::blProjectEditorTagsWidget(QWidget *parent) :
    QWidget(parent)
{

    QGridLayout *layout = new QGridLayout;
    this->setObjectName("blProjectEditorInfoWidget");

    QLabel *title = new QLabel(tr("Tags"), this);
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title, 0, 0, 1, 4);

    QPushButton *addButton = new QPushButton(tr("Add"), this);
    m_addEdit = new QLineEdit(this);
    layout->addWidget(m_addEdit, 1, 0, 1, 3, Qt::AlignRight);
    layout->addWidget(addButton, 1, 1, 1, 1);
    connect(addButton, SIGNAL(released()), this, SLOT(emitAskAddTag()));

    QWidget *tagListWidget = new QWidget(this);
    QVBoxLayout* m_tagListLayout = new QVBoxLayout;
    tagListWidget->setLayout(m_tagListLayout);
    layout->addWidget(tagListWidget, 2, 0, 1, 4);
    this->setLayout(layout);

}

void blProjectEditorTagsWidget::emitAskAddTag(){
    emit askAddTag(m_addEdit->text());
}
