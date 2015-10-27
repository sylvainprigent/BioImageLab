/// \file blMultipleComboBox.cpp
/// \brief blMultipleComboBox
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2015

#include "blMultipleComboBox.h"


blMultipleComboBox::blMultipleComboBox(QStringList comboList, QList<int> comboIds, QWidget *parent) :
    QWidget(parent)
{

    m_comboList = comboList;
    m_comboIds = comboIds;
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QWidget* lineEditArea = new QWidget(this);
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    //m_layout->setSpacing(1);
    lineEditArea->setLayout(m_layout);

    QPushButton *button = new QPushButton(tr("Add"), this);
    button->setObjectName("btnDefault");

    layout->addWidget(lineEditArea);
    layout->addWidget(button, 0, Qt::AlignLeft);

    connect(button, SIGNAL(pressed()), this, SLOT(buttonAddComboBox()));

}

void blMultipleComboBox::buttonAddComboBox(){
    this->addComboBox("", true);
}

void blMultipleComboBox::addComboBox(QString curentTxt, bool closable){

    blClosableComboBox *comboBox = new blClosableComboBox(m_comboList, m_comboIds, closable, this);
    if (curentTxt != ""){
        comboBox->setCurrentText(curentTxt);
    }
    m_layout->addWidget(comboBox);
}

QStringList blMultipleComboBox::texts(){
    QStringList tags;
    for (int i = 0 ; i < m_layout->count() ; ++i){
        if (m_layout->itemAt(i)->widget()){
            blClosableComboBox *w = dynamic_cast<blClosableComboBox *>(m_layout->itemAt(i)->widget());
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

QList<int> blMultipleComboBox::indexes(){
    QList<int> tags;
    for (int i = 0 ; i < m_layout->count() ; ++i){
        if (m_layout->itemAt(i)->widget()){
            blClosableComboBox *w = dynamic_cast<blClosableComboBox *>(m_layout->itemAt(i)->widget());
            if (w){
                int curentTag = w->index();
                tags.append(curentTag);
            }
        }
    }
    return tags;
}

void blMultipleComboBox::removeAll(){
    QLayoutItem* item;
    while ( ( item = m_layout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}

// ////////////////////////////////////////////////
//  blClosableComboBox
// ////////////////////////////////////////////////
blClosableComboBox::blClosableComboBox(QStringList comboList, QList<int> comboIds, bool closable, QWidget *parent)
    :QWidget(parent){

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_comboBox = new QComboBox(this);
    for (int i = 0 ; i < comboList.count() ; ++i){
        m_comboBox->addItem(comboList[i], comboIds[i]);
    }
    layout->addWidget(m_comboBox);

    if (closable){
        QPushButton *icon = new QPushButton(tr("Remove"));
        icon->setObjectName("btnPrimary");
        icon->setMaximumWidth(75);
        layout->addWidget(icon);
        connect(icon, SIGNAL(pressed()), this, SLOT(autoDesctroy()));
    }

    this->setLayout(layout);
}

int blClosableComboBox::index(){
    return m_comboBox->currentData().toInt();
}

QString blClosableComboBox::text(){
    return m_comboBox->currentText();
}

void blClosableComboBox::autoDesctroy(){
    delete this;
}

void blClosableComboBox::setCurrentText(QString text){
    m_comboBox->setCurrentText(text);
}
