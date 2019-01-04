/// \file blProjectBrowserWidgetToolBar.h
/// \brief blProjectBrowserWidgetToolBar
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectBrowserExport.h"
#include <QWidget>

/// \class blProjectBrowserWidgetToolBar
/// \brief Widget containing a toolbar to
/// store the project borwser actions
class BLPROJECTBROWSER_EXPORT blProjectBrowserWidgetToolBar : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectBrowserWidgetToolBar(QWidget *parent = 0);
    /// \brief Contructor
    /// \param[in] parent Qt parent system
    explicit blProjectBrowserWidgetToolBar(QWidget *parent = 0);
    
signals:
    /// \fn void askNewProject();
    /// \brief Signal emited when the widget "new project"
    /// is clicked
    void askNewProject();

private slots:
    /// \fn void emitNewProject();
    /// \brief Slot that emit askNewProject
    void emitNewProject();
};
