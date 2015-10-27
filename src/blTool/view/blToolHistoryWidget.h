#ifndef BLTOOLHISTORY_H
#define BLTOOLHISTORY_H

#include <QtWidgets>

#include "../model/blToolExecLog.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolHistoryWidget(QString historyFile, QWidget *parent = 0);

signals:
    void openData(QString, QString, QString);

public slots:

private:
    QWidget* toolTable(blToolInfo* toolInfo);
    QWidget* parametersTable(blioParameters* parameters);
    QWidget* ioTable(QString title, blioDataInfo* data, bool isInput);

private:
    blToolExecLog m_history;

};

#endif // BLTOOLHISTORY_H
