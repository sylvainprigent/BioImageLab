/// \file blFileSearch.h
/// \brief blFileSearch
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QDir>

/// \class blFileSearch
/// \brief Get file list from directories
class BLPROJECT_EXPORT blFileSearch{

public:
    /// \fn blFileSearch();
    /// \brief Contructor
    blFileSearch();

public:
    /// \fn QStringList searchFiles(QString folderPath, bool recursive);
    /// \return the list of files in a directory
    /// \param[in] folderPath Directory path
    /// \param[in] recursive True if recursive search
    QStringList searchFiles(QString folderPath, bool recursive);
    /// \fn static QStringList removeRootPath(const QStringList pathList, const QString rootPath);
    /// \brief remove a root file path from a list of file
    /// \param[in]  pathList File path list
    /// \param[in] rootPath Root path to remove
    /// \return the list of path where the root path have been remove to each file path
    static QStringList removeRootPath(const QStringList pathList, const QString rootPath);
    /// \fn static QString removeRootPath(const QString path, const QString rootPath);
    /// \brief Remove a root path to an image path
    /// \param[in] path Original file path
    /// \param[in] rootPath Root path to remove
    /// \return the file path where the root path have been removed
    static QString removeRootPath(const QString path, const QString rootPath);

protected:
    // methods
    /// \fn void searchForImages(QDir dirImage, bool recursive);
    /// \brief Search files in a QDir
    /// \brief dirImage Directory to analyse
    /// \param[in] recursive True if recursive search
    void searchForImages(QDir dirImage, bool recursive);

protected:
    QStringList m_foundFiles; ///< list of founded files
};
