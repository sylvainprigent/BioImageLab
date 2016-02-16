/// \file blProjectViewColumnSelector.cpp
/// \brief blProjectViewColumnSelector
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectViewColumnSelector.h"

blProjectViewColumnSelector::blProjectViewColumnSelector(QWidget *parent) :
    QPushButton(parent)
{
    this->setFixedSize(32,32);
    this->setObjectName("blProjectTableColumnSelectorWidget");
    connect(this, SIGNAL(clicked()), this, SLOT(showSelector()));

    createSelector();
}

void blProjectViewColumnSelector::createSelector(){

    m_selector = new QWidget();
    m_selector->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    //m_selector->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //m_selector->setVisible(false);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setSizeConstraint(QLayout::SetMinimumSize);

    m_selectAllBox = new QCheckBox(tr("Select all"));
    totalLayout->addWidget(m_selectAllBox, 0, Qt::AlignLeft);
    connect(m_selectAllBox, SIGNAL(clicked(bool)), this, SLOT(selectAllClicked(bool)));

    QWidget *columnList = new QWidget;
    m_columnListLayout = new QVBoxLayout;
    m_columnListLayout->setContentsMargins(0,0,0,0);
    columnList->setLayout(m_columnListLayout);
    totalLayout->addWidget(columnList, 0, Qt::AlignRight);

    QPushButton *okButton = new QPushButton(tr("Ok"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(hideSelector()));
    totalLayout->addWidget(okButton, 0, Qt::AlignRight);

    m_selector->setLayout(totalLayout);

    m_selectrorScroll = new QScrollArea;

    m_selectrorScroll->setWidgetResizable(true);
    m_selectrorScroll->setContentsMargins(0,0,0,0);
    m_selectrorScroll->setWidget(m_selector);
    m_selectrorScroll->setVisible(false);
    m_selectrorScroll->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
}

void blProjectViewColumnSelector::addColumn(QString columnName){

    QCheckBox *selectBox = new QCheckBox(columnName);
    m_columnListLayout->addWidget(selectBox, 0, Qt::AlignLeft);
    selectBox->setChecked(true);
    connect(selectBox, SIGNAL(clicked()), this, SLOT(uncheckSelectAll()));
    if (m_columnListLayout->count() > 5){
        m_selectrorScroll->setMinimumHeight(300);
    }
}

void blProjectViewColumnSelector::removeColumn(QString columnName){
    for (int i = 0 ; i < m_columnListLayout->count() ; ++i){
        QCheckBox *selectBox = dynamic_cast<QCheckBox*>(m_columnListLayout->itemAt(i)->widget());
        if (selectBox){
            if (selectBox->text() == columnName){
                m_columnListLayout->removeWidget(selectBox);
                delete selectBox;
            }
        }
    }
}

void blProjectViewColumnSelector::showSelector(){

    m_selectrorScroll->setVisible(true);
    int x = m_selectrorScroll->cursor().pos().x();
    int y = m_selectrorScroll->cursor().pos().y();

    const int width = QApplication::desktop()->width();
    if (width -x < m_selectrorScroll->width() ){
        x = width - m_selectrorScroll->width();
    }

    m_selectrorScroll->move(x,y);
}

void blProjectViewColumnSelector::hideSelector(){
    m_selectrorScroll->setVisible(false);

    // get the list of checked columns
    QStringList checkedColumns;
    for (int i = 0 ; i < m_columnListLayout->count() ; ++i){
        QCheckBox *box = dynamic_cast<QCheckBox*>(m_columnListLayout->itemAt(i)->widget());
        if (box){
            if (box->isChecked()){
                checkedColumns.append(box->text());
            }
        }
    }
    emit visibleColumns(checkedColumns);
}

void blProjectViewColumnSelector::selectAllClicked(bool checked){

    for (int i = 0 ; i < m_columnListLayout->count() ; ++i){
        QCheckBox *box = dynamic_cast<QCheckBox*>(m_columnListLayout->itemAt(i)->widget());
        if (box){
            box->setChecked(checked);
        }
    }
}

void blProjectViewColumnSelector::uncheckSelectAll(){
    m_selectAllBox->setChecked(false);
}

void blProjectViewColumnSelector::selectAll(){
    selectAllClicked(true);
    m_selectAllBox->setChecked(true);
}

void blProjectViewColumnSelector::setChecked(QString title, bool checked){

    for (int i = 0 ; i < m_columnListLayout->count() ; ++i){
        QCheckBox *box = dynamic_cast<QCheckBox*>(m_columnListLayout->itemAt(i)->widget());
        if (box){
            if (box->text() == title){
                box->setChecked(checked);
                return;
            }
        }
    }
}
