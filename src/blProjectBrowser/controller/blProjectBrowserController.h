/// \file blProjectBrowserController.h
/// \brief blProjectWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include <QWidget>
#include <QTableWidget>

#include <blProjectCore>
#include "../view/blProjectBrowserWidget.h"

#include "blProjectBrowserExport.h"

/// \class blProjectWidget
/// \brief Widget organized with tab that contains
/// the projects widgets
class BLPROJECTBROWSER_EXPORT blProjectBrowserController : public QWidget{
    Q_OBJECT
    
public:
    /// \fn blProjectBrowserController(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    blProjectBrowserController(QWidget *parent = 0);
    /// \fn ~blProjectWidget();
    /// \brief Destructor
    ~blProjectBrowserController();

signals:
    void askOpenProject(blProjectInfo *projectInfo);
    void askNewProject();

public slots:
    void deleteProject(blProjectInfo* project);

protected:
    blProjectBrowserWidget* m_projectBrowserWidget;

};
