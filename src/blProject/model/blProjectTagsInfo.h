/// \file blProjectInfo.h
/// \brief blProjectInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QString>

/// \class blProjectTagsInfo
/// \brief Contains the informations of a blProject
class BLPROJECT_EXPORT blProjectTagsInfo
{
public:
    /// \fn blProjectInfo();
    /// \brief Constructor
    blProjectTagsInfo();
    /// \fn ~blProjectInfo();
    /// \brief Destructor
    ~blProjectTagsInfo();

public:
    // setters
    /// \fn void setId(unsigned int id);
    /// \param[in] id Id of the project in the database
    void setId(unsigned int id);
    /// \fn void setName(QString name);
    /// \param[in] name Name of the project
    void setName(QString name);
    /// \fn void setUrl(QString url);
    /// \param[in] url URL of the folder containing the project
    void setUrl(QString url);
    /// \fn void setCreatedDate(QString createdDate);
    /// \param[in] createdDate Creation date of the project
    void setCreatedDate(QString createdDate);
    /// \fn void setLastModifiedDate(QString lastModifiedDate);
    /// \param[in] lastModifiedDate Last modification date of the project
    void setLastModifiedDate(QString lastModifiedDate);

    void setDescription(QString description);
    void setTypeId(int typeId);

public:
    // getters
    /// \fn unsigned int id();
    /// \return the Id of the project in the database
    unsigned int id();
    /// \fn QString name();
    ///\return  the name of the project
    QString name();
    /// \fn QString url();
    /// \return the URL of the folder containing the project
    QString url();
    /// \fn QString createdDate();
    /// \return the creation date of the project
    QString createdDate();
    /// \fn QString lastModifiedDate();
    /// \return the last modification date of the project
    QString lastModifiedDate();

    QString description();
    int typeId();

public:
    void print();
private:
    unsigned int m_id; ///< id of the project in the database
    QString m_name; ///< name
    QString m_url; ///< folder url
    QString m_createdDate; ///< created date
    QString m_lastModifiedDate; ///< last modified date
    int m_typeId; ///< type of the project (for data import)
    QString m_description; ///< description of the project
};
