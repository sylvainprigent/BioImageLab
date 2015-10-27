#ifndef BLTOOLHISTORYBAR_H
#define BLTOOLHISTORYBAR_H

#include "blToolHistoryBarWidget.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolHistoryBar : public QWidget
{
    Q_OBJECT
public:
    explicit blToolHistoryBar(QWidget *parent = 0);

signals:
    void deleteHistory(blToolHistoryInfo);
    void deleteHistory(int);
    void deleteHistory(QString);
    void openHistory(QString historyFile);

public slots:
    void addHistory(QString fileUrl, QString toolName);
    void removeHistory(int id);

private:
    QVBoxLayout *m_contentLayout;
    int m_lastId;
};

#endif // BLTOOLHISTORYBAR_H
