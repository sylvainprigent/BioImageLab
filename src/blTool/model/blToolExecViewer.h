#ifndef BLTOOLEXECVIEWER_H
#define BLTOOLEXECVIEWER_H

#include "blToolInfo.h"
#include "blioDataInfo.h"
#include "blioParameters.h"
#include <QThread>
#include <QProcess>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolExecViewer : public QObject
{
    Q_OBJECT
public:
    blToolExecViewer(QString viewersDirectory, QObject* parent = 0);
    ~blToolExecViewer();

signals:
    void error(QString message);

public slots:


public slots:
    // run
    void run(QString dataType, QString url, QString description);

private:
    QList<blToolInfo*> m_toolsInfo;
    QProcess* m_process;
};

#endif // BLTOOLEXECVIEWER_H
