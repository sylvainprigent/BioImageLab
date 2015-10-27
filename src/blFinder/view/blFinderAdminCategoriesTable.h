#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderCategoryInfo.h"

class BLFINDER_EXPORT blFinderAdminCategoriesTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminCategoriesTable(QWidget *parent = 0);

signals:
    void edit(int);
public:

public slots:
    void fillTable(QList<blFinderCategoryInfo> authorInfo);

private:
    QTableWidget *m_tableWidget;
};
