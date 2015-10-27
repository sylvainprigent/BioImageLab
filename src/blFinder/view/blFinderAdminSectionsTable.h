#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderSectionInfo.h"

class BLFINDER_EXPORT blFinderAdminSectionsTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminSectionsTable(QWidget *parent = 0);

signals:
    void edit(int);
public:

public slots:
    void fillTable(QList<blFinderSectionInfo> sectionInfo);

private:
    QTableWidget *m_tableWidget;
};
