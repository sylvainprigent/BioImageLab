/// \file blProjectEditorDatabase.h
/// \brief blProjectEditorDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioImageLab 2019


#pragma once

#include <QtSql>
#include <qsqldatabase.h>
#include "blProjectTag.h"
#include "blProjectData.h"
#include "blProjectContent.h"

/// \class blProjectTagDatabase
/// \brief manage a database containing a project tags
/// list and informations
class blProjectEditorDatabase
{
public:
    /// \fn blProjectEditorDatabase();
    /// \brief Constructor
    blProjectEditorDatabase();
    /// \fn blProjectIndex(QString databaseFile);
    /// \brief Contructor that connect to the database
    /// \param[in] databaseFile Database to connect
    blProjectEditorDatabase(QString databaseFile);

public:
    // IO
    /// \fn void blProjectIndex(QString databaseFile);
    /// \param[in] databaseFile Address of the database
    void setDatabaseFile(QString databaseFile);
    /// \fn void connect();
    /// \brief Connect to the database
    void connect();
    void disconnect();

public:
    // create
    /// \fn void createDatabase();
    /// \brief Create the table of the database
    void createDatabase();

public:
    // queries

    // tags
    blProjectTag* setTag(blProjectTag *tag);
    QList<blProjectTag*> getTags();
    QList<blProjectTag*> setTags(QList<blProjectTag*> tags);
    bool isTag(int id);
    QString tagName(int tagId);
    int removeTag(blProjectTag *tag);

    // data
    blProjectData* setData(blProjectData* data);
    QList<blProjectData*> getData();
    bool isData(int id);

    // data tags
    void setDataTag(int id_data, int id_tag, QString value);
    blProjectTagValue* getDataTag(int id_data, int id_tag);
    bool isDataTag(int id_data, int id_tag);

    // content
    blProjectContent* getContent();

public:
    void viewDatabase();
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
