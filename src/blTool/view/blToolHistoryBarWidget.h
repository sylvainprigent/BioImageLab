#ifndef BLTOOLHISTORYBARWIDGET_H
#define BLTOOLHISTORYBARWIDGET_H

#include <QtWidgets>
#include "../view/blToolHistoryInfo.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolHistoryBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolHistoryBarWidget(blToolHistoryInfo history, QWidget *parent = 0);

signals:
    void openHistory(blToolHistoryInfo);
    void deleteHistory(blToolHistoryInfo);
    void deleteHistory(int id);
    void deleteHistory(QString historyFile);
    void openHistory(QString historyFile);

public:
    int id();

private slots:
    void askOpenHistory();
    void askDeleteHistory();

private:
    blToolHistoryInfo m_history;
};

#endif // BLTOOLHISTORYBARWIDGET_H
