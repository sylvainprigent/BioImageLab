/// \file blFinderAccess.h
/// \brief blFinderAccess
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#pragma once

#include "blSingleton.h"
#include "blFinderDatabase.h"

/// \class blFinderAccess
/// \brief Singleton that allow to access the workflow
///  database
class BLFINDER_EXPORT blFinderAccess : public blSingleton<blFinderAccess>{

    friend class blSingleton<blFinderAccess>;

private:
    /// \fn blFinderAccess();
    /// \brief Constructor
    blFinderAccess();
    /// \fn ~blFinderAccess();
    /// \brief Desctructor
    ~blFinderAccess();

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
    /// \fn blFinderDatabase *database();
    /// \return a pointer to the database manager
    blFinderDatabase *database();

private:
    QString m_databaseFile; ///< database file
    blFinderDatabase* m_database; ///< database
};
