/// \file blProjectModel.h
/// \brief blProjectModel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QString>
#include <QObject>
#include "blProjectModelMainColumn.h"

/// \class blProjectModel
/// \brief Define the methods manage
/// read and write project data
class BLPROJECT_EXPORT blProjectModel : public QObject
{
    Q_OBJECT
public:
    /// \fn blProjectModel();
    /// \brief Constructor
    blProjectModel(QObject* parent =0);

    /// \fn blProjectModel();
    /// \brief Constructor
    /// \param[in] projectUrl URL of the project folder
    blProjectModel(QString projectUrl, QObject *parent = 0);

public:
    // name

    /// \fn void setProjectName(QString projectName);
    /// \param[in] projectName Name of the project
    void setProjectName(QString projectName);
    /// \fn QString projectName();
    /// \retun the name of the project
    QString projectName();

public:
    // IO
    /// void setProjectUrl(QString projectUrl);
    /// \param[in] projectUrl URL of the project folder
    void setProjectUrl(QString projectUrl);
    /// QString projectUrl();
    /// \return URL of the project folder
    QString projectUrl();
    /// \fn void load();
    /// \brief Load the project data from a folder
    void load();
    /// \fn void save();
    /// \brief Save the project data from a folder
    void save();

public:
    // getters/setters
    /// \fn void addMainColumn(QString name, blProjectModelMainColumn);
    /// \brief Add a new column to the project
    /// \param[in] name Column name
    /// \param[in] column Column data
    void addMainColumn(QString name, blProjectModelMainColumn& column);
    /// \fn blProjectModelMainColumn& mainColumn(QString name);
    /// \return Main column with the name "name"
    /// \param[in] name Name of the main column to get
    blProjectModelMainColumn& mainColumn(QString name);
    /// \fn QString mainColumnFolder(QString folderName);
    /// \brief create the folder that contains the data of a main column
    /// if it not exists
    /// \param[in] name of the column
    /// \return the URL of the folder
    QString mainColumnFolder(QString folderName);
    /// \fn QMap<QString, blProjectModelMainColumn>& mainColumns();
    /// \return the main columns map
    QMap<QString, blProjectModelMainColumn>& mainColumns();

    QStringList mainColumnsName();
    QStringList columnsName(QString mainColumn);
    blProjectModelColumn columnData(QString mainColumnName, QString subColumnName);
    void removeMainColumn(QString columnName);
    void removeSubColumn(QString mainColumnName, QString subColumnName);

public:
    // queries
    void createColumnIfNotExists(QString mainColumnName, QString columnName);
    bool isMainColumn(QString name);
    bool isColumn(QString mainColumnName, QString columnName);

private:
    QString m_projectName; ///< name of the project
    QString m_projectUrl; ///< project URL
    QMap<QString, blProjectModelMainColumn> m_mainColumns; ///< map of the main columns
};
