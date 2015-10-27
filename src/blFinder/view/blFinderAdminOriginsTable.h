#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderOriginInfo.h"

class BLFINDER_EXPORT blFinderAdminOriginsTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminOriginsTable(QWidget *parent = 0);

signals:
    void edit(int);
public:

public slots:
    void fillTable(QList<blFinderOriginInfo> authorInfo);

private:
    QTableWidget *m_tableWidget;
};
