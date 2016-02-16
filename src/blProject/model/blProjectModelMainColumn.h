/// \file blProjectModelMainColumn.h
/// \brief blProjectModelMainColumn
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include "blProjectModelColumn.h"

/// \class blProjectModelMainColumn
/// \brief Store and manage the data for a
/// main column of the project Model
class BLPROJECT_EXPORT blProjectModelMainColumn{

public:
    /// \fn blProjectModelMainColumn();
    /// \brief Constructor
    blProjectModelMainColumn();

    /// \fn blProjectModelMainColumn(QString file);
    /// \brief Constructor
    /// \param[in] file URL of the file containing the main column informations
    blProjectModelMainColumn(QString file);

public:
    // file
    /// \fn void setFile(QString file);
    /// \param[in] file URL of the file to store the main column info
    void setFile(QString file);
    /// \fn QString file();
    /// \return file URL of the file to store the main column info
    QString file();

public:
    // setters
    /// \fn void addColumn(QString name);
    /// \brief Add an empty column
    /// \param[in] name Name of the column
    void addColumn(QString name);
    void removeColumn(QString columnName);
    /// \fn void addColumn(QString name, blProjectModelColumn *data);
    /// \brief Add a column and load it data from a file
    /// \param[in] name Name of the column
    /// \param[in] data column data
    void addColumn(QString name, blProjectModelColumn &data);

    /// \fn QMap<QString, blProjectModelColumn*> columns();
    /// \return the map of the columns
    QMap<QString, blProjectModelColumn> columns();

    /// \fn blProjectModelColumn& column(QString name);
    /// \param[in] name Name of the column to get
    /// \return the column data
    blProjectModelColumn& column(QString name);

    /// \fn void setName(QString name);
    /// \param[in] name Name of the column
    void setName(QString name);
    /// \fn QString name();
    /// \return the name of the column
    QString name();

public:
    // IO
    /// \fn void load();
    /// \brief Load the main column info from the file
    void load();
    /// \fn void save();
    /// \brief Save the main column info into the file
    void save();

public:
    // queries
    bool isColumn(QString name);

private:
    QString m_name; ///< name of the column
    QString m_file; ///< file to store the main column info
    QMap<QString, blProjectModelColumn> m_columns; ///< list of column data
};
