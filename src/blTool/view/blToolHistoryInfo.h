#ifndef BLTOOLHISTORYINFO_H
#define BLTOOLHISTORYINFO_H

#include <QString>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolHistoryInfo
{
public:
    blToolHistoryInfo();

public:
    // getters
    QString fileUrl();
    QString toolName();
    QString lastModified();
    int id();

public:
    // setters
    void setFileUrl(QString fileUrl);
    void setToolName(QString toolName);
    void setLastModified(QString lastModified);
    void setId(int id);

private:
    QString m_fileUrl;
    QString m_toolName;
    QString m_lastModified;
    int m_id;
};

#endif // BLTOOLHISTORYINFO_H
