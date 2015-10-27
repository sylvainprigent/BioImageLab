#pragma once

#include <QtWidgets>
#include "blFinderExport.h"

class BLFINDER_EXPORT blFinderOriginInfo
{

public:
    blFinderOriginInfo();

public:
    // setters
    void setID(int id);
    void setName(QString name);

public:
    // getters
    int id();
    QString name();

private:
    int m_id;
    QString m_name;
};
