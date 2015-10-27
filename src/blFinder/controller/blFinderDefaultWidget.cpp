#include "blFinderDefaultWidget.h"
#include "../view/blFinderBar.h"
#include "../model/blFinderAccess.h"

blFinderDefaultWidget::blFinderDefaultWidget(QWidget *parent) : QWidget(parent)
{
    // global layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    // bar
    blFinderBar *bar = new blFinderBar(this);
    QStringList wordList = blFinderAccess::instance()->database()->allKeywords();
    bar->searchBar()->setAutoComplete(wordList);


    QSplitter *splitter = new QSplitter(this);
    m_centralWidget = new blFinderBrowser(this);
    splitter->addWidget(m_centralWidget);
    splitter->addWidget(bar);
    layout->addWidget(splitter);

    bar->setMaximumWidth(250);

    // connections
    connect(bar, SIGNAL(search(QString)), this, SLOT(searchKeyword(QString)));
    connect(bar, SIGNAL(category(int)), this, SLOT(searchSoftware(int)));
    connect(bar, SIGNAL(origin(int)), this, SLOT(origin(int)));
    connect(bar, SIGNAL(finder()), this, SLOT(finder()));
    connect(m_centralWidget, SIGNAL(section(int)), this, SLOT(finderSection(int)));
    connect(m_centralWidget, SIGNAL(tutorial(int)), this, SLOT(finderTutorial(int)));
    connect(m_centralWidget, SIGNAL(openTool(QString)), this, SIGNAL(openTool(QString)));
}

void blFinderDefaultWidget::setItems(QList<blFinderTutorialInfo> infos, QString title){
    m_centralWidget->setInfos(infos, title);
}

void blFinderDefaultWidget::setToolShedDir(QString toolShedDir){
    m_toolShedDir = toolShedDir;
}

void blFinderDefaultWidget::setFinderDir(QString finderDir){
    m_finderDir = finderDir;
}

void blFinderDefaultWidget::searchKeyword(QString keyword){

    QList<blFinderTutorialInfo> infos = blFinderAccess::instance()->database()->tutorialsByKeyword(keyword, m_toolShedDir);
    m_centralWidget->setInfos(infos, "Search: " + keyword);
}

void blFinderDefaultWidget::searchSoftware(int id){

    QString keyword = blFinderAccess::instance()->database()->keywordWord(id);
    QList<blFinderTutorialInfo> infos = blFinderAccess::instance()->database()->tutorialsByKeyword(keyword, m_toolShedDir);
    m_centralWidget->setInfos(infos, "Software: " + keyword);

}

void blFinderDefaultWidget::origin(int origin){

    QList<blFinderTutorialInfo> infos = blFinderAccess::instance()->database()->tutorialsByOrigin(origin, m_toolShedDir);
    m_centralWidget->setInfos(infos, "Origin: " +  blFinderAccess::instance()->database()->OriginName(origin));
}

void blFinderDefaultWidget::finder(){

    blFinderDatabase *db = blFinderAccess::instance()->database();
    // get root item (for title)
    blFinderSectionInfo root = db->root();
    // get child list
    QList<blFinderSectionInfo> infos = db->children(root.id(), m_finderDir);
    m_centralWidget->setInfos(infos, "Finder: " +  root.childrenTitle());
}

void blFinderDefaultWidget::finderSection(int sectionID){
    blFinderDatabase *db = blFinderAccess::instance()->database();
    blFinderSectionInfo root = db->section(sectionID);
    QList<blFinderSectionInfo> infos = db->children(sectionID, m_finderDir);
    if (infos.count() > 0){
        m_centralWidget->setInfos(infos, "Finder: " +  root.childrenTitle());
    }
    else{
        // get the tutorials under this section
        QList<blFinderTutorialInfo> tutos = db->childrenTutorials(sectionID, m_toolShedDir);
        m_centralWidget->setInfos(tutos, "Finder: " +  root.childrenTitle());

    }
}

void blFinderDefaultWidget::finderTutorial(int id){
     blFinderDatabase *db = blFinderAccess::instance()->database();
     blFinderTutorialInfo tuto = db->tutorialInfo(id, m_toolShedDir);
     m_centralWidget->setTutorial(tuto);
}
