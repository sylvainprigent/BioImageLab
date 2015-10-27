/// \file blMultipleLineEdit.cpp
/// \brief blMultipleLineEdit
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2015

#include "blMultipleLineEdit.h"


blMultipleLineEdit::blMultipleLineEdit(QWidget *parent) :
    QWidget(parent)
{

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);

    QWidget* lineEditArea = new QWidget(this);
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    //m_layout->setSpacing(1);
    lineEditArea->setLayout(m_layout);

    QPushButton *button = new QPushButton(tr("Add"), this);

    layout->addWidget(lineEditArea);
    layout->addWidget(button, 0, Qt::AlignLeft);

    connect(button, SIGNAL(pressed()), this, SLOT(addLineEdit()));
}

void blMultipleLineEdit::addLineEdit(bool closable){

    blClosableLineEdit *lineEdit = new blClosableLineEdit(closable, this);
    m_layout->addWidget(lineEdit);
}

QStringList blMultipleLineEdit::texts(){
    QStringList tags;
    for (int i = 0 ; i < m_layout->count() ; ++i){
        if (m_layout->itemAt(i)->widget()){
            blClosableLineEdit *w = dynamic_cast<blClosableLineEdit *>(m_layout->itemAt(i)->widget());
            if (w){
                QString curentTag = w->text();
                curentTag = curentTag.simplified();
                curentTag.replace( " ", "" );
                tags.append(curentTag);
            }
        }
    }
    return tags;
}

void blMultipleLineEdit::removeAll(){
    QLayoutItem* item;
    while ( ( item = m_layout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}

// ////////////////////////////////////////////////
//  blClosableLineEdit
// ////////////////////////////////////////////////
blClosableLineEdit::blClosableLineEdit(bool closable, QWidget *parent)
    :QWidget(parent){

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);


    m_lineEdit = new QLineEdit(this);
    layout->addWidget(m_lineEdit);

    if (closable){
        QPushButton *icon = new QPushButton(tr("Remove"));
        layout->addWidget(icon);
        connect(icon, SIGNAL(pressed()), this, SLOT(autoDesctroy()));
    }

    this->setLayout(layout);
}

QString blClosableLineEdit::text(){
    return m_lineEdit->text();
}

void blClosableLineEdit::autoDesctroy(){
    delete this;
}

