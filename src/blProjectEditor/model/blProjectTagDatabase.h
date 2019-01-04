/// \file blProjectTagDatabase.h
/// \brief blProjectTagDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioImageLab 2019


#pragma once

#include <QtSql>
#include <qsqldatabase.h>
#include "blProjectTag.h"

/// \class blProjectTagDatabase
/// \brief manage a database containing a project tags
/// list and informations
class blProjectTagDatabase
{
public:
    /// \fn blProjectTagDatabase();
    /// \brief Constructor
    blProjectTagDatabase();
    /// \fn blProjectIndex(QString databaseFile);
    /// \brief Contructor that connect to the database
    /// \param[in] databaseFile Database to connect
    blProjectTagDatabase(QString databaseFile);

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
    blTagInfo setTag(blTagInfo info);
    QList<blTagInfo> tags();
    QList<blTagInfo> setTags(blTagsInfo tags);
    bool isTag(int id);
    QString tagName(int tagId);
    int setTag(int id, QString name, int idColumn);
    int addTag(QString name, int id_subcol);

public:
    void printTable();

protected:
    QString m_databaseFile; ///< database file
    QSqlDatabase m_db; ///< database
    QString m_connectionName; ///< connection name
};
