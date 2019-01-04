/// \file blProjectIndex.h
/// \brief blProjectIndex
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2016
///
/// Copyright (C) BioImageLab 2016


#pragma once

#include <QtSql>
#include <qsqldatabase.h>
#include "blTagsInfo.h"
#include "blMainColumnInfo.h"
#include "blSubColumnInfo.h"
#include "blDataInfo.h"

/// \class blProjectIndex
/// \brief manage a database containing a project
/// list and informations
class blProjectIndex
{
public:
    /// \fn blProjectIndex();
    /// \brief Constructor
    blProjectIndex();
    /// \fn blProjectIndex(QString databaseFile);
    /// \brief Contructor that connect to the database
    /// \param[in] databaseFile Database to connect
    blProjectIndex(QString databaseFile);

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
    // add
    int addMainColumn(QString name, QString originUrl);
    int addSubColumn(QString name, int id_main_col, QString datatype);
    int addData(int line_idx, QString url, QString thumbnail_url, int id_main_col, int id_sub_col);

    // edit
    blMainColumnInfo setMainColumn(blMainColumnInfo info);
    void editMainColumn(int id, QString name, QString originUrl);
    void editSubColumn(int id, QString name, int id_main_col, QString datatype);
    void editData(int id, int line_idx, QString url, QString thumbnail_url, int id_main_col, int id_sub_col);
    blDataInfo setData(blDataInfo data);

    blSubColumnInfo setSubColumnInfo(blSubColumnInfo info);
    QList<blMainColumnInfo> mainColumns();
    QList<blSubColumnInfo> subColumns(int mainColumnId);

    int maxLineIdx();
    QList<blDataInfo> getDataLine(int lineIdx);
    QString getSubColDataType(int colId);
    // tags
    blTagInfo setTag(blTagInfo info);
    QList<blTagInfo> tags();
    QList<blTagInfo> setTags(blTagsInfo tags);
    bool isTag(int id);
    QString tagName(int tagId);
    int setTag(int id, QString name, int idColumn);
    int addTag(QString name, int id_subcol);

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

