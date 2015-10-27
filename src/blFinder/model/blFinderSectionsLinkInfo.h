#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "blFinderCategoryInfo.h"

class BLFINDER_EXPORT blFinderSectionsLinkInfo
{

public:
    blFinderSectionsLinkInfo();

public:
    // setters
    void setParentID(int id);
    void setParentName(QString name);
    void setChildID(int id);
    void setChildName(QString name);

public:
    // getters
    int parentID();
    QString parentName();
    int childID();
    QString childName();

private:
    int m_parentID;
    QString m_parentName;
    int m_childID;
    QString m_childName;
};
