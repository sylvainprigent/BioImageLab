/// \file blProjectEditorAccess.h
/// \brief blProjectEditorAccess
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include <blCore/blSingleton.h>
#include "blProjectEditorDatabase.h"

/// \class blIndexationAccess
/// \brief Singleton that allow to access the worflow
/// index and database
class BLPROJECTEDITOR_EXPORT blProjectEditorAccess : public blSingleton<blProjectEditorAccess>{

    friend class blSingleton<blProjectEditorAccess>;

private:
    /// \fn blProjectEditorAccess();
    /// \brief Constructor
    blProjectEditorAccess();
    /// \fn ~blProjectEditorAccess();
    /// \brief Desctructor
    ~blProjectEditorAccess();

public:
    /// \fn void setDatabaseFile(QString databaseFile);
    /// \param[in] databaseFile File containing the workflow database
    void setDatabaseFile(QString databaseFile);

public:
    /// \fn void load();
    /// \brief Load the index and connect to the database
    void load();

public:
    // getters
    /// \fn blProjectDatabase *database();
    /// \return a pointer to the database manager
    blProjectEditorDatabase *database();

private:
    QString m_databaseFile; ///< database file
    QString m_indexFile; ///< index file
    blProjectEditorDatabase* m_database; ///< database
};
