/// \file blProjectData.h
/// \brief blProjectData
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include <QString>

/// \class blProjectInfo
/// \brief Contains the informations of a blProjectData
class BLPROJECTEDITOR_EXPORT blProjectData
{
public:
    /// \fn blProjectData();
    /// \brief Constructor
    blProjectData();
    /// \fn ~blProjectData();
    /// \brief Destructor
    ~blProjectData();

public:
    // setters
    /// \fn void setId(unsigned int id);
    /// \param[in] id Id of the project in the database
    void setId(unsigned int id);
    /// \fn void setUrl(QString url);
    /// \param[in] url Url of the project
    void setUrl(QString url);

public:
    // getters
    /// \fn unsigned int id();
    /// \return the Id of the data in the database
    unsigned int id();
    /// \fn QString url();
    ///\return  the url of the data
    QString url();


public:
    void print();

private:
    unsigned int m_id; ///< id of the tag in the project database
    QString m_url; ///< name

};
