#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderSectionsLinkInfo.h"

class BLFINDER_EXPORT blFinderAdminSectionsLinksTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminSectionsLinksTable(QWidget *parent = 0);

signals:
    void removeLink(int, int);

public slots:
    void fillTable(QList<blFinderSectionsLinkInfo> sectionLinkInfo);

private slots:
    void emitRemove(int id1, int id2);

private:
    QTableWidget *m_tableWidget;
};
