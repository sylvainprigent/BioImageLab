#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../../blWidgets/blSearchBarWidget.h"

class BLFINDER_EXPORT blFinderBar : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderBar(QWidget *parent = 0);

signals:
    void finder();
    void origin(int);
    void category(int);
    void search(QString);

public:
    blSearchBarWidget *searchBar();

private slots:
    void createSearchArea();
    void createFinderArea();
    void createOrigin();
    void createCategoriesArea();

private:
    QGridLayout *m_contentLayout;
    blSearchBarWidget *m_searchBar;
};
