/// \file blProjectView.cpp
/// \brief blProjectView
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include <iostream>

#include "blProjectView.h"
#include "blProjectViewColumn.h"
#include "blProject/model/blProjectDatabase.h"
#include "blProject/model/blProjectModelColumn.h"
#include "blWidgets/blImageView.h"

blProjectView::blProjectView(QWidget *parent) :
    QWidget(parent)
{

    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(25);

    createTable();
    this->setLayout(m_layout);

    // Create column selector
    m_selectorWidget = new blProjectViewColumnSelector;
    m_selectorWidget->setToolTip(tr("Show/hide columns"));
    connect(m_selectorWidget, SIGNAL(visibleColumns(QStringList)), this, SLOT(showHideColumns(QStringList)));

}

blProjectViewColumnSelector *blProjectView::selectorWidget(){
    return m_selectorWidget;
}

void blProjectView::createTable(){

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setLayout(layout);


    m_splitter = new QSplitter;
    m_splitter->setChildrenCollapsible(false);

    m_layout->addWidget(widget);

    QString splitterStyle = QString("QSplitter::handle { ")+
            QString(" background-color: white;")+
            QString("}")+

            QString("QSplitter::handle:horizontal {")+
            QString("    width: 1px; ")+
            QString("}")+

            QString("QSplitter::handle:vertical {")+
            QString("    height: 1px; ")+
            QString("}")+

            QString("QSplitter::handle:pressed {")+
            QString(" background-color: white;")+
            QString("}");

    m_splitter->setStyleSheet(splitterStyle);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(m_splitter);
    layout->addWidget(scroll);
}

void blProjectView::addColumnTable(QString name){

    blProjectViewColumn *columnTable = new blProjectViewColumn(name);
    connect(columnTable, SIGNAL(askDeleteColumn(QString)), this, SIGNAL(askDeleteColumn(QString)));
    connect(columnTable, SIGNAL(askComputeThumbnails(QString)), this, SIGNAL(askComputeThumbnails(QString)));
    connect(columnTable, SIGNAL(askAddRemoveColumns(QString)), this, SIGNAL(askAddRemoveColumns(QString)));

    m_selectorWidget->addColumn(name);
    m_splitter->addWidget(columnTable);
    columnTable->table()->verticalHeader()->setVisible(false);
    connect(columnTable, SIGNAL(asblide(QString)), this, SLOT(hideColumn(QString)));

    if (m_columnsTables.count() > 0){
        connect(m_columnsTables[0]->table()->verticalHeader(), SIGNAL(sectionResized(int,int,int)), columnTable, SLOT(resizeRow(int, int, int)));
    }
    for (int i = 0 ; i < m_columnsTables.size() ; ++i){
        connect(m_columnsTables[i]->table()->verticalScrollBar(), SIGNAL(valueChanged(int)), columnTable->table()->verticalScrollBar(), SLOT(setValue(int)));
        connect(columnTable->table()->verticalScrollBar(), SIGNAL(valueChanged(int)), m_columnsTables[i]->table()->verticalScrollBar(), SLOT(setValue(int)));
    }
    connect(columnTable, SIGNAL(cellClicked(int,int,int)), this, SLOT(showHoverableWidget(int, int, int)));
    m_columnsTables.append(columnTable);
    columnTable->setId(m_columnsTables.size()-1);

    connect(columnTable, SIGNAL(dataChanged(QString,QString, unsigned int,QString)), this, SIGNAL(dataChanged(QString,QString, unsigned int,QString)));
}

void blProjectView::hideColumn(QString columnName){
    for (int i = 0 ; i < m_columnsTables.count() ; ++i){
        if ( m_columnsTables[i]->title() == columnName){
            m_columnsTables[i]->setVisible(false);
            break;
        }
    }
    m_selectorWidget->setChecked(columnName, false);
}

void blProjectView::removeMainColumn(QString columnName){
    for (int i = 0 ; i < m_columnsTables.count() ; ++i){
        if ( m_columnsTables[i]->title() == columnName){
            blProjectViewColumn *w = m_columnsTables[i];
            m_columnsTables.removeAt(i);
            delete w;
            break;
        }
    }
    m_selectorWidget->removeColumn(columnName);
}

void blProjectView::removeSubColumn(QString mainColumnName, QString subColumnName){
    for (int i = 0 ; i < m_columnsTables.count() ; ++i){
        if ( m_columnsTables[i]->title() == mainColumnName){
            blProjectViewColumn *w = m_columnsTables[i];
            w->removeColumn(subColumnName);
            break;
        }
    }
}

void blProjectView::showHideColumns(QStringList columnsNames ){

    for (int i = 0 ; i < m_columnsTables.count() ; ++i){
        m_columnsTables[i]->setVisible(false);
    }
    for (int i = 0 ; i < m_columnsTables.count() ; ++i){
        for (int j = 0 ; j < columnsNames.count() ; ++j){
            if ( m_columnsTables[i]->title() == columnsNames[j]){
                m_columnsTables[i]->setVisible(true);
                m_columnsTables[i]->selectAll();
                break;
            }
        }
    }
}

blProjectViewColumn * blProjectView::column(QString name){

    for (int i = 0 ; i < m_columnsTables.count() ; ++i){
        if ( m_columnsTables[i]->title() == name){
            return m_columnsTables[i];
        }
    }
    return NULL;
}

/*
void blProjectView::setToolBarVisible(bool visible){
    m_toolBar->setVisible(visible);
}
*/

void blProjectView::showHoverableWidget(int id, int row, int column){


    std::cout << "showHoverableWidget at: " << id << ", " << row << ", " << column << std::endl;
    if (m_columnsTables.at(id)->columnType(column) == blProjectModelColumn::IMAGE_URL){


        // get the image URL
        QString imageURL = dynamic_cast<blImageView*>(m_columnsTables.at(id)->table()->cellWidget(row, column))->text();

        // view the image
        QFileInfo file(imageURL);
        emit openData("image", imageURL, file.fileName());
    }
}
