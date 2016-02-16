#ifndef BLTOOLHISTORYBROWSER_H
#define BLTOOLHISTORYBROWSER_H

#include "blToolCore/model/blToolExecLog.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolHistoryBrowser : public QObject
{
    Q_OBJECT
public:
    blToolHistoryBrowser();

public slots:
    QList<blToolExecLog> getHistoryAll();
    QList<blToolExecLog> getHistoryByTool(QString toolName);
    QList<QStringList> getHistoryFileByTool(QString toolName);

    bool deleteHistory(QString fileUrl);

public:
    // setters
    void setHistoryDir(QString dir);

private:
    QString m_historyDir;
};

#endif // BLTOOLHISTORYBROWSER_H
