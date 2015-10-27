#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderAuthorInfo.h"
#include "../model/blFinderCategoryInfo.h"
#include "../model/blFinderKeywordInfo.h"
#include "../model/blFinderSectionInfo.h"
#include "../model/blFinderSectionsLinkInfo.h"
#include "../model/blFinderTutorialInfo.h"
#include "../model/blFinderOriginInfo.h"
#include "../model/blFinderTutorialsLinkInfo.h"

class BLFINDER_EXPORT blFinderAdminDefaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminDefaultWidget(QWidget *parent = 0);

signals:

public:

private slots:
    // authors
    void authors();
    void authorAdd();
    void authorUpdate(int id);
    void editAuthor(blFinderAuthorInfo info);
    void removeAuthor(int id);

    // categories
    void categories();
    void categoryAdd();
    void categoryUpdate(int id);
    void editCategory(blFinderCategoryInfo info);
    void removeCategory(int id);

    // keywords
    void keywords();
    void keywordAdd();
    void keywordUpdate(int id);
    void editKeyword(blFinderKeywordInfo info);
    void removeKeyword(int id);

    // sections
    void sections();
    void sectionAdd();
    void sectionUpdate(int id);
    void editSection(blFinderSectionInfo info);
    void removeSection(int id);

    // sections links
    void sectionsLinks();
    void sectionsLinksAdd();
    void editSectionsLink(blFinderSectionsLinkInfo info);
    void removeSectionsLink(int id1, int id2);

    // origins
    void origins();
    void originAdd();
    void originUpdate(int id);
    void editOrigin(blFinderOriginInfo info);
    void removeOrigin(int id);

    // tutorials
    void tutorials();
    void tutorialAdd();
    void tutorialUpdate(int id);
    void editTutorial(blFinderTutorialInfo info);
    void removeTutorial(int id);

    // tutorials links
    void tutorialsLinks();
    void tutorialsLinksAdd();
    void editTutorialsLink(blFinderTutorialsLinkInfo info);
    void removeTutorialsLink(int id1, int id2);

private:
    void setCentralWidget(QWidget * widget, bool alignTop = true);

private:
    QVBoxLayout *m_layout;
};
