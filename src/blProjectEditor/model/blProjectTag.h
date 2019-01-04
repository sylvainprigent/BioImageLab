/// \file blProjectTag.h
/// \brief blProjectTag
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectCoreExport.h"
#include <QString>

/// \class blProjectInfo
/// \brief Contains the informations of a blProjectTag
class BLPROJECTCORE_EXPORT blProjectTag
{
public:
    /// \fn blProjectTag();
    /// \brief Constructor
    blProjectTag();
    /// \fn ~blProjectTag();
    /// \brief Destructor
    ~blProjectTag();

public:
    // setters
    /// \fn void setId(unsigned int id);
    /// \param[in] id Id of the project in the database
    void setId(unsigned int id);
    /// \fn void setName(QString name);
    /// \param[in] name Name of the project
    void setName(QString name);

public:
    // getters
    /// \fn unsigned int id();
    /// \return the Id of the project in the database
    unsigned int id();
    /// \fn QString name();
    ///\return  the name of the project
    QString name();


public:
    void print();

private:
    unsigned int m_id; ///< id of the tag in the project database
    QString m_name; ///< name

};
