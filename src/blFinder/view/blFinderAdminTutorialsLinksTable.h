#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialsLinkInfo.h"

class BLFINDER_EXPORT blFinderAdminTutorialsLinksTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminTutorialsLinksTable(QWidget *parent = 0);

signals:
    void removeLink(int, int);

public slots:
    void fillTable(QList<blFinderTutorialsLinkInfo> tutorialsLinkInfo);

private slots:
    void emitRemove(int id1, int id2);

private:
    QTableWidget *m_tableWidget;
};
