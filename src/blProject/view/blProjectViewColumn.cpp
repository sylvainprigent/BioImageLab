/// \file blProjectViewColumn.cpp
/// \brief blProjectViewColumn
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectViewColumn.h"
#include <iostream>

blProjectViewColumn::blProjectViewColumn(QString title, QWidget *parent) :
    QWidget(parent)
{
    m_isChangingEnable = false;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    m_header = new blProjectViewColumnHeader(title);
    connect(m_header, SIGNAL(askDeleteColumn(QString)), this, SIGNAL(askDeleteColumn(QString)));
    connect(m_header, SIGNAL(askComputeThumbnails(QString)), this, SIGNAL(askComputeThumbnails(QString)));
    connect(m_header, SIGNAL(askAddRemoveColumns(QString)), this, SIGNAL(askAddRemoveColumns(QString)));
    layout->addWidget(m_header);
    connect(m_header, SIGNAL(visibleColumns(QStringList)), this, SLOT(showHideColumns(QStringList)));

    m_table = new QTableWidget(0,0,this);
    //m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setStretchLastSection( true );
    layout->addWidget(m_table);

    connect(m_table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(emitCellClicked(int,int)));
    connect(m_table, SIGNAL(cellChanged(int,int)), this, SLOT(emitDataChanged(int,int)));
    this->setLayout(layout);
    this->setMinimumWidth(150);
}

void blProjectViewColumn::addColumn(QString title, QString type){

    int column = m_table->columnCount();
    m_table->setColumnCount(column+1);
    m_table->setHorizontalHeaderItem(column, new QTableWidgetItem(title));
    m_header->addColumn(title);

    m_headerTitles.append(title);
    m_columnsType.append(type);
}

QStringList blProjectViewColumn::columnsType(){
    return m_columnsType;
}

void blProjectViewColumn::setColumnType(int c, QString type){
    m_columnsType[c] = type;
}

void blProjectViewColumn::setId(int id){
    m_id = id;
}

QString blProjectViewColumn::columnType(int c){
    return m_columnsType[c];
}

QString blProjectViewColumn::columnName(int c){
    return m_table->horizontalHeaderItem(c)->text();
}

int blProjectViewColumn::columnIdx(QString columnName){
    for (int i = 0 ; i < m_columnsType.count() ; ++i){
        if (columnName == m_table->horizontalHeaderItem(i)->text()){
            return i;
        }
    }
    return -1;
}


void blProjectViewColumn::addTableItem(int row, int column, QTableWidgetItem *item){
    if (row >= m_table->rowCount())
        m_table->setRowCount(m_table->rowCount()+1);
    m_table->setItem(row, column, item);

    m_table->setRowHeight(row, 150);
    //m_table->verticalHeader()->setResizeMode(QHeaderView::Fixed); // does not compile in Qt5
    m_table->verticalHeader()->setDefaultSectionSize(150);
}

void blProjectViewColumn::addView(int row, int column, QWidget *widget){
    if (row >= m_table->rowCount())
        m_table->setRowCount(m_table->rowCount()+1);
    m_table->setCellWidget(row, column, widget);

    m_table->setRowHeight(row, 150);
    //m_table->verticalHeader()->setResizeMode(QHeaderView::Fixed); // don't compile in Qt5
    m_table->verticalHeader()->setDefaultSectionSize(150);
    m_table->setItem(row,0, new QTableWidgetItem);
}

void blProjectViewColumn::showHideColumns(QStringList visibles){
    for (int i = 0 ; i < m_table->columnCount() ; ++i){
        m_table->setColumnHidden(i, true);
    }
    if (!visibles.isEmpty()){
        for (int i = 0 ; i < m_table->columnCount() ; ++i){
            for (int j = 0 ; j < visibles.size() ; ++j){
                if (m_table->horizontalHeaderItem(i)->text() ==  visibles[j]){
                    m_table->setColumnHidden(i, false);
                    break;
                }
            }
        }
    }
    else{
        emit asblide(m_header->title());
        //this->setVisible(false);
    }
}

void blProjectViewColumn::selectAll(){
    for (int i = 0 ; i < m_table->columnCount() ; ++i){
        m_table->setColumnHidden(i, false);
    }
    m_header->selector()->selectAll();
}

QTableWidget *blProjectViewColumn::table(){
    return m_table;
}

void blProjectViewColumn::resizeRow(int row, int oldHeight, int newHeight){
    if (oldHeight != newHeight )
        m_table->setRowHeight(row, newHeight);
}

void blProjectViewColumn::setTitle(QString title){
    m_header->setTitle(title);
}

QString blProjectViewColumn::title(){
    return m_header->title();
}

unsigned int blProjectViewColumn::columnsCount(){
    return m_table->columnCount();
}

void blProjectViewColumn::emitCellClicked(int m, int n){
    m_isChangingEnable = true;
    std::cout << "emit cell clicked at " << m_id << ", " << m << ", " << n << std::endl;
    emit cellClicked(m_id, m, n);
}

void blProjectViewColumn::emitDataChanged(int m, int n){
    if (m_isChangingEnable)
        emit dataChanged(m_header->title(), columnName(n), m, m_table->item(m,n)->text() );
}

blProjectViewColumnHeader *blProjectViewColumn::headerWidget(){
    return m_header;
}

void blProjectViewColumn::removeColumn(QString columnName){
    for(int i = 0 ; i < m_headerTitles.count() ; ++i){
        if ( m_headerTitles[i] == columnName ){
            m_table->removeColumn(i);
        }
    }
}
