/// \file blProjectWidget.h
/// \brief blProjectWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"

#include <QWidget>
#include <QTableWidget>

#include "blProject/model/blProjectInfo.h"
#include "blProject/view/blProjectBrowserWidget.h"

class blProjectNewFormWidget;
class blProjectControler;

/// \class blProjectWidget
/// \brief Widget organized with tab that contains
/// the projects widgets
class BLPROJECT_EXPORT blProjectWidget : public QWidget{
    Q_OBJECT
    
public:
    /// \fn blProjectWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    blProjectWidget(QString viewerDir, QString binariesDir, QWidget *parent = 0);
    /// \fn ~blProjectWidget();
    /// \brief Destructor
    ~blProjectWidget();

    void setProjectsRootPath(QString projectsRootPath);

signals:
    void askOpenWorkflow(QString);

public slots:
    /// \fn void openProject(blProjectInfo* info);
    /// \brief open a project
    /// \param[in] info Informations of the project to open
    void openProject(blProjectInfo* info);
    /// \fn void deleteProject(blProjectInfo* info);
    /// \brief delete a project from the database and remove it content folder
    ////// \param[in] info Informations of the project to delete
    void deleteProject(blProjectInfo* info);
    /// \fn void openNewProjectForm();
    /// \brief Open a new tab with a blProjectNewFormWidget
    void openNewProjectForm();



private slots:
    /// \fn void deleteCurentTab();
    /// \brief close the tab curent
    void deleteCurentTab();
    /// \fn void createProject(blProjectControler* controler,blProjectNewFormWidget* form);
    /// \brief Create a new project from a controler
    /// \param[in] controler Controler containing the project data
    /// \param[in] form Pointer to the form that is at the origin of the project creation
    void createProject(blProjectControler* controler,blProjectNewFormWidget* form);
    /// \fn void openProject(blProjectControler* controler);
    /// \brief Open a project from a controler
    /// \param[in] controler Controler containing the project
    void openProject(blProjectControler* controler);
    /// \fn void removeProcessingTab(int index);
    /// \brief Close the tab of index "index"
    /// \param[in] index Index of the tab to close
    void removeProcessingTab(int index);

    /// \fn void deleteCurentTabProject(QString projectName);
    /// \brief close a project tab
    /// \param[in] projectName Name of the project to be closed
    void deleteCurentTabProject(QString projectName);

private:
    // internal methods
    /// \fn void createTab();
    /// \brief Create the tab widget and add
    /// a blProjectBrowserWidget
    void createTab();

private:
    QString m_viewerDir, m_binariesDir;
    QTabWidget* m_tab; ///< tab containing all the widgets
    blProjectBrowserWidget *m_projectBrowserWidget; ///< project browser
    QStringList m_openedProjectList;
    QString m_projectsRootPath;
};
