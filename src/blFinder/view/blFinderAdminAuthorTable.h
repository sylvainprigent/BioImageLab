#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderAuthorInfo.h"

class BLFINDER_EXPORT blFinderAdminAuthorTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminAuthorTable(QWidget *parent = 0);

signals:
    void edit(int id);
public:

public slots:
    void fillTable(QList<blFinderAuthorInfo> authorInfo);

private:
    QTableWidget *m_tableWidget;
};
