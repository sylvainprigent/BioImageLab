#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialInfo.h"

class BLFINDER_EXPORT blFinderAdminTutorialsTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminTutorialsTable(QWidget *parent = 0);

signals:
    void edit(int id);
public:

public slots:
    void fillTable(QList<blFinderTutorialInfo> tutorialsInfo);

private:
    QTableWidget *m_tableWidget;
};
