/// \file blSettingsAccess.h
/// \brief blSettingsAccess
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blCoreExport.h"
#include "blSingleton.h"
#include "blSettingsGroups.h"


/// \class blIndexationAccess
/// \brief Singleton that allow to access the worflow
/// index and database
class BLCORE_EXPORT blSettingsAccess : public blSingleton<blSettingsAccess>{

    friend class blSingleton<blSettingsAccess>;

private:
    /// \fn blSettingsAccess();
    /// \brief Constructor
    blSettingsAccess();
    /// \fn ~blSettingsAccess();
    /// \brief Desctructor
    ~blSettingsAccess();

public:
    /// \fn void setSettingsFile(QString fileUrl);
    /// \param[in] fileUrl File containing the settings
    void setSettingsFile(QString fileUrl);

public:
    /// \fn void load();
    /// \brief Load the settings
    void load();
    void save();

public:
    // getters
    /// \fn blSettingsGroups *settings();
    /// \return a pointer to the settings container
    blSettingsGroups *settings();

private:
    QString m_fileUrl; ///< settings file
    blSettingsGroups *m_settings; ///< settings containers
};
