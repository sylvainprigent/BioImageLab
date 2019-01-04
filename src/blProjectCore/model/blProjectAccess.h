/// \file blProjectAccess.h
/// \brief blProjectAccess
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectCoreExport.h"
#include <blCore/blSingleton.h>
#include "blProjectDatabase.h"

/// \class blIndexationAccess
/// \brief Singleton that allow to access the worflow
/// index and database
class BLPROJECTCORE_EXPORT blProjectAccess : public blSingleton<blProjectAccess>{

    friend class blSingleton<blProjectAccess>;

private:
    /// \fn blProjectAccess();
    /// \brief Constructor
    blProjectAccess();
    /// \fn ~blProjectAccess();
    /// \brief Desctructor
    ~blProjectAccess();

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
    blProjectDatabase *database();

private:
    QString m_databaseFile; ///< database file
    QString m_indexFile; ///< index file
    blProjectDatabase* m_database; ///< database
};
