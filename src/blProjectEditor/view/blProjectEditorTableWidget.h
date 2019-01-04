/// \file blProjectEditorTableWidget.h
/// \brief blProjectEditorTableWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectCore/model/blProjectInfo.h"
#include <QWidget>

/// \class blProjectEditorTableWidget
/// \brief Widget that shows the list of data
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorTableWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorTableWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorTableWidget(QWidget *parent = 0);

signals:
    void askImportData();

protected:
    QWidget* emptyListWidget();

protected:
    QWidget* m_emptyTableWidget;
};
