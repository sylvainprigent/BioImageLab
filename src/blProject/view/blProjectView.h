/// \file blProjectView.h
/// \brief blProjectView
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>
#include "blProjectViewColumnSelector.h"
#include "blProjectViewColumn.h"

/// \class blProjectView
/// \brief Widget showing a table to vew a project
class BLPROJECT_EXPORT blProjectView : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectView(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    explicit blProjectView(QWidget *parent = 0);
    
signals:
    void dataChanged(QString mainColumnName, QString columnName, unsigned int lineIdx, QString data);
    void askSave();
    void askAddProject(blProjectView*);
    void askDeleteColumn(QString);
    void askComputeThumbnails(QString);
    void askOpenCompo(QString);
    void askAddRemoveColumns(QString);
    void openData(QString, QString, QString);
    
public slots:
    void addColumnTable(QString name);
    void removeMainColumn(QString columnName);
    void removeSubColumn(QString mainColumnName, QString subColumnName);

public:
    blProjectViewColumn * column(QString name);
    blProjectViewColumnSelector *selectorWidget();

private slots:
    void showHideColumns(QStringList columnsNames );
    void hideColumn(QString columnName);
    void showHoverableWidget(int id, int row, int column);

private:
    QVBoxLayout *m_layout; ///< layout
    blProjectViewColumnSelector *m_selectorWidget; ///< selector widget
    QList<blProjectViewColumn *> m_columnsTables; ///< coloms table list
    QSplitter *m_splitter; ///< splitter between tables

private:
    /// \fn void createTable();
    /// \brief Create the table
    void createTable();
};
