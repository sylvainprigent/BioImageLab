/// \file blProjectFolderFilter.h
/// \brief blProjectFolderFilter
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtCore>

/// \class blProjectFolderFilter
/// \brief Select some files from a folder given filters on the file names
/// defined by "start with", "end by" and "contains"
class BLPROJECT_EXPORT blProjectFolderFilter
{
public:
    /// \fn blProjectFolderFilter(QString folderPath, bool isRecursive, QList<QStringList> filtersInfos);
    /// \brief Constructor
    /// \param[in] folderPath Folder to extract the files
    /// \param[in] isRecursive True to recursively analyse the folder
    /// \param[in] filtersInfos filters to use
    blProjectFolderFilter(QString folderPath, bool isRecursive, QList<QStringList> filtersInfos);

public:
    /// \fn QStringList run();
    /// \brief Run the filtering
    QStringList run();

private:
    /// \fn QStringList filter(QString starts, QString contains, QString ends);
    /// \brief Run one filter
    /// \param[in] starts Begining of the filenames to extract
    /// \param[in] contains String that must contain the filenames to extract
    /// \param[in] ends Ending of the filenames to extract
    QStringList filter(QString starts, QString contains, QString ends);
    /// \fn bool findInCurent(QString path);
    /// \param[in] path File to test
    /// \return true if the path is in the curent path list
    bool findInCurent(QString path);

private:
    QString m_folderPath; ///< input folder
    bool m_isRecursive; ///< recursive analysis of the folder
    QList<QStringList> m_filtersInfos; ///< filters to use
    QStringList m_curentFiles; ///< extracted files
};
