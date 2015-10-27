#pragma once

#include <QtWidgets>
#include "blFinderExport.h"

class BLFINDER_EXPORT blFinderSectionInfo
{

public:
    blFinderSectionInfo();

public:
    // setters
    void setID(int id);
    void setName(QString name);
    void setDescription(QString desc);
    void setImageUrl(QString url);
    void setChildrenTitle(QString title);
    void setDisplayOrder(int order);

public:
    // getters
    int id();
    QString name();
    QString description();
    QString imageUrl();
    QString childrenTitle();
    int displayOrder();

private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_imageUrl;
    QString m_childrenTitle;
    int m_displayOrder;
};
