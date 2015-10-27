#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "blFinderTutorialInfo.h"

class BLFINDER_EXPORT blFinderTutorialsLinkInfo
{

public:
    blFinderTutorialsLinkInfo();

public:
    // setters
    void setCategoryID(int id);
    void setCategoryName(QString name);
    void setTutorialID(int id);
    void setTutorialName(QString name);

public:
    // getters
    int categoryID();
    QString categoryName();
    int tutorialID();
    QString tutorialName();

private:
    int m_categoryID;
    QString m_categoryName;
    int m_tutorialID;
    QString m_tutorialName;
};
