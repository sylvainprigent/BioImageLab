/// \file blProjectViewColumn.h
/// \brief blProjectViewColumn
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include "blProjectViewColumnHeader.h"

/// \class blProjectViewColumn
/// \brief Widget that view one main column of a project
class BLPROJECT_EXPORT blProjectViewColumn : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectViewColumn(QString title, QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] title Column title
    /// \param[in] parent Qt parent system
    explicit blProjectViewColumn(QString title, QWidget *parent = 0);
    
signals:
    void asblide(QString title);
    void cellClicked(int id, int m, int n);
    void dataChanged(QString mainColumnName, QString columnName, unsigned int lineIdx, QString data);
    void askDeleteColumn(QString);
    void askComputeThumbnails(QString);
    void askShowParametersColumn(QString);
    void askAddRemoveColumns(QString);

public slots:
    void addColumn(QString title, QString type);
    void addView(int row, int column, QWidget *widget);
    void addTableItem(int row, int column, QTableWidgetItem *item);
    void resizeRow(int row, int oldHeight, int newHeight);
    void setTitle(QString title);
    void selectAll();
    QStringList columnsType();
    QString columnType(int c);
    QString columnName(int c);
    int columnIdx(QString columnName);
    void setColumnType(int c, QString type);
    void setId(int id);
    void removeColumn(QString columnName);

private slots:
    void showHideColumns(QStringList visibles);
    void emitCellClicked(int m, int n);
    void emitDataChanged(int m, int n);

public:
    QTableWidget* table();
    blProjectViewColumnHeader *headerWidget();
    QString title();
    unsigned int columnsCount();

private:
    int m_rowNum;///< number of rows
    int m_colNum; ///< number of columns
    QString m_type; ///< data type

private:
    QTableWidget *m_table; ///< table
    blProjectViewColumnHeader *m_header; ///< header
    QStringList m_columnsType; ///< type
    QStringList m_headerTitles; ///< titles of columns
    int m_id; ///< id
    bool m_isChangingEnable; ///< enable cells edition

};
