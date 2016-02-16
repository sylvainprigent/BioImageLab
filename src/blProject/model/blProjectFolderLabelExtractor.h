/// \file blProjectFolderLabelExtractor.h
/// \brief blProjectFolderLabelExtractor
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtCore>

/// \class blProjectFolderLabelExtractor
/// \brief Defin functions to extract label from file paths
class BLPROJECT_EXPORT blProjectFolderLabelExtractor
{
public:
    /// \fn blProjectFolderLabelExtractor(QStringList files, QString rootPath);
    /// \brief Constructor
    /// \param[in] file File to extract the labels
    /// \param[in] rootPath Root path of the common folder of all the files
    blProjectFolderLabelExtractor(QStringList files, QString rootPath);

public:
    /// \fn QList<QStringList> run(QString regExps);
    /// \brief Run the label extraction
    /// \param[in] regExps Regular expression
    /// \return the list of labels for each input file
    QList<QStringList> run(QString regExps);
    //int labelsCount();
    //QStringList labelsTitle();
    /// \fn QStringList label(int i);
    /// \return the list of labels for line i
    /// \param[in] i line idx
    QStringList label(int i);


private:
    /// \fn QList<QStringList> pathLabelExtractor();
    /// \return the extracted labels from the files path
    QList<QStringList> pathLabelExtractor();
    /// \fn QList<QStringList> dataLabelExtractor();
    /// \return the date label for each input file
    QList<QStringList> dataLabelExtractor();
    /// \fn QStringList removeRootPath();
    /// \return the input files path where the root path have been removed
    QStringList removeRootPath();

private:
    QStringList m_files; ///< input files
    QStringList m_labelsTitle; ///< titles of the labels
    QStringList m_keyWords; ///< keywords to extract
    QList<QStringList> m_extractedLabels; ///< list of labels for each input file
    QString m_rootPath; ///< root directory af the files
};
