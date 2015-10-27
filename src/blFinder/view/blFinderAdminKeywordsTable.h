#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderKeywordInfo.h"

class BLFINDER_EXPORT blFinderAdminKeywordsTable : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminKeywordsTable(QWidget *parent = 0);

signals:
    void edit(int);
public:

public slots:
    void fillTable(QList<blFinderKeywordInfo> keywordInfo);

private:
    QTableWidget *m_tableWidget;
};
