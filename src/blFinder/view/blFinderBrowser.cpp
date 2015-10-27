#include "blFinderBrowser.h"


blFinderBrowser::blFinderBrowser(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *thisLayout = new QVBoxLayout;
    thisLayout->setContentsMargins(0,0,0,0);

    m_itemList = new blFinderItemList(this);
    m_tutorialView = new blFinderTutorialView(this);

    thisLayout->addWidget(m_itemList);
    thisLayout->addWidget(m_tutorialView);

    QWidget *totalWidget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(0,0,0,0);
    totalWidget->setLayout(thisLayout);
    this->setLayout(totalLayout);
    totalLayout->addWidget(totalWidget);
    totalWidget->setObjectName("blFinderItemList");

    connect(m_itemList, SIGNAL(section(int)), this, SIGNAL(section(int)));
    connect(m_itemList, SIGNAL(tutorial(int)), this, SIGNAL(tutorial(int)));
    connect(m_tutorialView, SIGNAL(openTool(QString)), this, SIGNAL(openTool(QString)));

    m_itemList->setVisible(false);
    m_tutorialView->setVisible(false);
}

void blFinderBrowser::setInfos(QList<blFinderTutorialInfo> infos, QString title){

    m_itemList->setInfos(infos, title);
    m_itemList->setVisible(true);
    m_tutorialView->setVisible(false);
}

void blFinderBrowser::setInfos(QList<blFinderSectionInfo> infos, QString title){

    m_itemList->setInfos(infos, title);
    m_itemList->setVisible(true);
    m_tutorialView->setVisible(false);
}

void blFinderBrowser::setTutorial(blFinderTutorialInfo tuto){

    m_tutorialView->setTutorial(tuto);
    m_itemList->setVisible(false);
    m_tutorialView->setVisible(true);
}
