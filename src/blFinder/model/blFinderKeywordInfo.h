#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "blFinderCategoryInfo.h"

class BLFINDER_EXPORT blFinderKeywordInfo
{

public:
    blFinderKeywordInfo();

public:
    // setters
    void setID(int id);
    void setName(QString name);
    void setCategoryID(int id);
    void setCategoryName(QString name);

public:
    // getters
    int id();
    QString name();
    int categoryID();
    QString categoryName();

private:
    int m_id;
    QString m_name;
    int m_categoryID;
    QString m_categoryName;
};
