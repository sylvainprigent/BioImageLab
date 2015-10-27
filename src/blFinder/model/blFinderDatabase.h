/// \file blFinderDatabase.h
/// \brief blFinderDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#pragma once

#include <QtSql>
#include <qsqldatabase.h>

#include "blFinderAuthorInfo.h"
#include "blFinderCategoryInfo.h"
#include "blFinderKeywordInfo.h"
#include "blFinderSectionInfo.h"
#include "blFinderSectionsLinkInfo.h"
#include "blFinderTutorialInfo.h"
#include "blFinderOriginInfo.h"
#include "blFinderTutorialsLinkInfo.h"

/// \class blFinderDatabase
/// \brief manage a database containing the tools
/// list and informations
class BLFINDER_EXPORT blFinderDatabase
{
public:
    /// \fn blFinderDatabase();
    /// \brief Constructor
    blFinderDatabase();
    /// \fn blFinderDatabase(QString databaseFile);
    /// \brief Contructor that connect to the database
    /// \param[in] databaseFile Database to connect
    blFinderDatabase(QString databaseFile);

public:
    // IO
    /// \fn void setDatabaseFile(QString databaseFile);
    /// \param[in] databaseFile Address of the database
    void setDatabaseFile(QString databaseFile);
    /// \fn void connect();
    /// \brief Connect to the database
    void connect();

public:
    // create
    /// \fn void createDatabase();
    /// \brief Create the table of the database
    void createDatabase();

    void addTestEntries();

public:
    // queries authors
    void editAuthor(blFinderAuthorInfo authorInfo);
    QList<blFinderAuthorInfo> authors();
    blFinderAuthorInfo authorInfo(int id);
    void deleteAuthor(int id);
    QString authorFullName(int id);
    QString authorShortName(int id);
    // queries categories
    QList<blFinderCategoryInfo> categories();
    blFinderCategoryInfo categoryInfo(int id);
    void editCategory(blFinderCategoryInfo info);
    QString categoryName(int id);
    int categoryId(QString name);
    void deleteCategory(int id);
    // queries keywords
    QList<blFinderKeywordInfo> keywords();
    QStringList allKeywords();
    blFinderKeywordInfo keywordInfo(int id);
    void editKeyword(blFinderKeywordInfo info);
    void deleteKeyword(int id);
    QString keywordWord(int id);
    int keywordId(QString word);
    QList<blFinderKeywordInfo> keywordsByCategory(QString category);
    // queries section
    void editSection(blFinderSectionInfo info);
    QList<blFinderSectionInfo> sections();
    blFinderSectionInfo sectionInfo(int id);
    QString sectionName(int id);
    void deleteSection(int id);
    // queries sections links
    QList<blFinderSectionsLinkInfo> sectionsLinks();
    void editSectionsLink(blFinderSectionsLinkInfo info);
    void deleteSectionsLink(int id1, int id2);
    // queries tutorials links
    QList<blFinderTutorialsLinkInfo> tutorialsLinks();
    void editTutorialsLink(blFinderTutorialsLinkInfo info);
    void deleteTutorialsLink(int id1, int id2);
    // queries tutorials
    void editTutorial(blFinderTutorialInfo info);
    QList<blFinderTutorialInfo> tutorials();
    blFinderTutorialInfo tutorialInfo(int id, QString toolShedDir = "");
    QList<int> tutorialAuthors(int id);
    QList<int> tutorialKeywords(int id);
    void deleteTutorial(int id);
    QString tutorialTitle(int id);
    // queries origins
    QList<blFinderOriginInfo> origins();
    blFinderOriginInfo OriginInfo(int id);
    void editOrigin(blFinderOriginInfo info);
    QString OriginName(int id);
    void deleteOrigin(int id);
    //   finder queries
    QList<blFinderTutorialInfo> tutorialsByKeyword(QString keyword, QString toolshedDir = "");
    QList<blFinderTutorialInfo> tutorialsByOrigin(int origin, QString toolshedDir);
    blFinderSectionInfo root();
    blFinderSectionInfo section(int id);
    QList<blFinderSectionInfo> children(int section, QString toolshedDir = "");
    QList<blFinderTutorialInfo> childrenTutorials(int section, QString toolshedDir = "");

public:
    /// \fn viewTable(const QString tableName = "Tools");
    /// \brief Plot the table in the console for debug
    /// \param[in] tableName name of the table to view
    void viewTable(const QString tableName = "Tools");
    /// \fn viewTableHeader(const QString tableName, const QString orientation)
    /// \brief View the headers of a table in the console
    /// \param[in] tableName Name of the table to view
    /// \param[in] orientation Orientation of the view (horizontal, vertical)
    void viewTableHeader(const QString tableName, const QString orientation);
    /// \fn void viewTablesList();
    /// \brief View the list of tables in the console
    void viewTablesList();

protected:
    QString m_databaseFile; ///< database file
    QSqlDatabase m_db; ///< database
    QString m_connectionName; ///< connection name
};
