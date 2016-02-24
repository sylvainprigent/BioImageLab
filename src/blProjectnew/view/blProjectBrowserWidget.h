/// \file blProjectBrowserWidget.h
/// \brief blProjectBrowserWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectnewExport.h"
#include <QWidget>
#include "blProjectBrowserWidgetToolBar.h"
#include "blProjectBrowserWidgetList.h"

/// \class blProjectBrowserWidget
/// \brief Widget that shows the list of project
/// and a tool bar to create a new project
class BLPROJECTNEW_EXPORT blProjectBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectBrowserWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectBrowserWidget(bool useNewProjectIcone = true, bool useEmptyWidget = true, QWidget *parent = 0);
    
signals:
    /// \fn void askNewProject();
    /// \brief Signal emitted when the user click on
    /// the new project button
    void askNewProject();
    /// \fn void askDeleteProject(blProjectInfo* info);
    /// \brief Signal emitted when the user click on the trash button
    /// \param[in] info Info of the project to delete
    void askDeleteProject(blProjectInfo* info);
    /// \fn void askOpenProject(blProjectInfo* info);
    /// \brief Signal emitted when a project is clicked
    /// \param[in] info Info of the project to open
    void askOpenProject(blProjectInfo* info);

public slots:
    void rowDeletedFeedBack(bool success, QString message);

private:
    // methods
    /// \fn void createWidget();
    /// \brief Create this widget
    void createWidget();

private:
    // attributs
    blProjectBrowserWidgetToolBar *m_toolbar; ///< tool bar
    blProjectBrowserWidgetList *m_table; ///< table to view project list
    bool m_useNewProjectIcone; ///< true to add the "new project" button
    bool m_useEmptyWidget;
};
