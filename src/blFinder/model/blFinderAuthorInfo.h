#pragma once

#include <QtWidgets>
#include "blFinderExport.h"

class BLFINDER_EXPORT blFinderAuthorInfo
{

public:
    blFinderAuthorInfo();

public:
    // setters
    void setID(int id);
    void setName(QString name);
    void setFirstname(QString firstname);

public:
    // getters
    int id();
    QString name();
    QString firstname();

private:
    int m_id;
    QString m_name;
    QString m_firstname;
};
