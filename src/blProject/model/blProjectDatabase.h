/// \file blProjectDatabase.h
/// \brief blProjectDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtSql>
#include "blProjectInfo.h"

/// \class blProjectDatabase
/// \brief manage a database containing the blProjects
/// list and informations
class BLPROJECT_EXPORT blProjectDatabase
{
public:
    /// \fn blProjectDatabase();
    /// \brief Constructor
    blProjectDatabase();
    /// \fn blProjectDatabase(QString databaseFile);
    /// \brief Contructor that connect to the database
    /// \param[in] databaseFile Database to connect
    blProjectDatabase(QString databaseFile);

public:
    // IO
    /// \fn void setDatabaseFile(QString databaseFile);
    /// \param[in] databaseFile Address of the database
    void setDatabaseFile(QString databaseFile);
    /// \fn void connect();
    /// \brief Connect to the database
    void connect();

public:
    // queries
    /// \fn void createDatabase();
    /// \brief Create the table of the database
    void createDatabase();
    /// \fn QList<blProjectInfo*> allProjects();
    /// \return the list of all the projects in the database
    QList<blProjectInfo*> allProjects();
    /// \fn bool addProject(blProjectInfo* projectInfo);
    /// \brief Add a project to the database
    /// \param[in] blProjectInfo Project to add
    bool addProject(blProjectInfo* projectInfo);
    /// \fn bool updateProjectURL(blProjectInfo* projectInfo);
    /// \brief Modify the URL of the project
    /// \param[in] projectInfo project to be updated
    bool updateProjectURL(blProjectInfo* projectInfo);
    /// \fn blProjectInfo* findProjectById(unsigned int id);
    /// \return the informations of the project of id "id"
    blProjectInfo* findProjectById(unsigned int id);
    /// \fn blProjectInfo* findProjectByName(QString name);
    /// \return the informations of the project of name "name"
    blProjectInfo* findProjectByName(QString name);
    /// \fn bool removeProject(int id);
    /// \brief Remove a project
    /// \param[i] id Id of the project to remove
    bool removeProject(int id);


public:
    /// \fn viewTable(const QString tableName = "projects");
    /// \brief Plot the table in the console for debug
    /// \param[in] tableName name of the table to view
    void viewTable(const QString tableName = "projects");
    /// \fn viewTableHeader(const QString tableName, const QString orientation)
    /// \brief View the headers of a table in the console
    /// \param[in] tableName Name of the table to view
    /// \param[in] orientation Orientation of the view (horizontal, vertical)
    void viewTableHeader(const QString tableName, const QString orientation);
    /// \fn void viewTablesList();
    /// \brief View the list of tables in the console
    void viewTablesList();

protected:
    QString m_databaseFile; ///< database file
    QSqlDatabase m_db; ///< database
    QString m_connectionName; ///< connection name
};
