#pragma once

#include <QtWidgets>
#include "blFinderExport.h"

class BLFINDER_EXPORT blFinderAdminBar : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminBar(QWidget *parent = 0);

signals:
    void authorsList();
    void authorAdd();
    void categoriesList();
    void categoriesAdd();
    void keywordsList();
    void keywordsAdd();
    void tutorialsList();
    void tutorialAdd();
    void sectionsList();
    void sectionsAdd();
    void sectionsLinks();
    void sectionsLinksAdd();
    void tutorialsLinks();
    void tutorialsLinksAdd();
    void originsList();
    void originAdd();

private slots:
    void createAuthorArea();
    void createIndexArea();
    void createFinderArea();
    void createTutorialsArea();

private:
    QGridLayout *m_contentLayout;
};
