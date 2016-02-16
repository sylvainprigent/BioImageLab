/// \file blProjectBrowserWidgetList.h
/// \brief blProjectBrowserWidgetList
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include "blProject/model/blProjectInfo.h"

#include <QWidget>
#include <QTableWidget>

/// \class blProjectBrowserWidgetList
/// \brief Widget that shows the projects as a list
class BLPROJECT_EXPORT blProjectBrowserWidgetList : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectBrowserWidgetList(QWidget *parent = 0);
    /// \brief COnstructor
    /// \param[in] parent Qt parent system
    explicit blProjectBrowserWidgetList(QList<blProjectInfo *> &projects, QWidget *parent = 0);
    
signals:
    /// \fn void askOpenProject(blProjectInfo* info);
    /// \brief Signal emited when a project item is double clicked
    /// \param[in] info Info of the clicked project
    void askOpenProject(blProjectInfo* info);

    /// \fn void askDeleteProject(blProjectInfo* info);
    /// \brief Signal emited when a project trash item is clicked
    /// \param[in] info Info of the clicked project
    void askDeleteProject(blProjectInfo* info);

    /// \fn void askNewProject();
    /// \brief Signal emitted when the user click on
    /// the new project button
    void askNewProject();

public slots:
    /// \fn void setProjects(QList<blProjectInfo*> &projects);
    /// \brief The content of the table is free before seting new projects
    /// \param[in] projects Projects info to set into the table
    void setProjects(QList<blProjectInfo*> &projects);
    /// \fn void addProjects(QList<blProjectInfo*> &projects);
    /// \param[in] projects Projects info to append at the end of the table
    void addProjects(QList<blProjectInfo*> &projects);
    /// \fn void rowDeletedFeedBack(bool success, QString message)
    /// \brief Refresh the table project list
    void rowDeletedFeedBack(bool success, QString message);

private slots:
    /// \fn void emitCellDoubleClicked(int r, int c);
    /// \brief Emit the signal askOpenProject
    /// \param[in] r row index of the clicked cell of the table
    /// \param[in] c column index of the clicked cell of the table
    void emitCellDoubleClicked(int r, int c);

    /// \fn void emitCellClicked(int r, int c);
    /// \brief Emit the signal askOpenProject
    /// \param[in] r row index of the clicked cell of the table
    /// \param[in] c column index of the clicked cell of the table
    void emitCellClicked(int r, int c);

    void deleteProject(int r);
    void openProject(int r);

private:
    // internal methods
    /// \fn void createTable();
    /// \brief Create the table widget
    /// \return the table widget
    void createTable();
    /// \fn QWidget* emptyListWidget();
    /// \return an information widget to imform that there are no projects
    QWidget* emptyListWidget();
    /// \fn void freeProjectTable();
    /// \brief Remove all the content of the table
    void freeProjectTable();

private:
    // widgets
    QTableWidget* m_table; ///< table to view the project list
    QWidget* m_emptyListWidget; ///< information widget to imform that there are no projects
    
    // data
    QList<blProjectInfo *> m_projects; ///< list of the projects
    unsigned int m_rowTodelete;
};
