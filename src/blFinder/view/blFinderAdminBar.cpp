#include "blFinderAdminBar.h"

blFinderAdminBar::blFinderAdminBar(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *title = new QLabel(tr("Finder admin"), this);
    title->setObjectName("blFinderAdminBarTitle");
    QWidget *content = new QWidget(this);
    m_contentLayout = new QGridLayout;
    content->setLayout(m_contentLayout);

    layout->addWidget(title);
    layout->addWidget(content);
    layout->addWidget(new QWidget(this), 1, Qt::AlignTop);

    // authors area
    createAuthorArea();
    createIndexArea();
    createFinderArea();
    createTutorialsArea();
    m_contentLayout->addWidget(new QWidget, 12, 0, 1, 2, Qt::AlignLeft );

    QWidget *container = new QWidget(this);
    container->setLayout(layout);

    QHBoxLayout *containerLayout = new QHBoxLayout;
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->addWidget(container);
    this->setLayout(containerLayout);
    container->setObjectName("blFinderAdminBar");
}

void blFinderAdminBar::createAuthorArea(){

    QLabel *title = new QLabel(tr("Authors"));
    title->setObjectName("blFinderAdminBarSubTitle");

    QPushButton *authorList = new QPushButton(tr("Authors"), this);
    authorList->setObjectName("btnLink");
    QPushButton *authorAdd = new QPushButton(tr("Add"), this);
    authorAdd->setObjectName("btnLink");

    m_contentLayout->addWidget(title,0, 0, 1, 2);
    m_contentLayout->addWidget(authorList, 1, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(authorAdd, 1, 1, 1, 1,Qt::AlignLeft);

    connect(authorList, SIGNAL(pressed()), this, SIGNAL(authorsList()));
    connect(authorAdd, SIGNAL(pressed()), this, SIGNAL(authorAdd()));
}

void blFinderAdminBar::createIndexArea(){

    QLabel *title = new QLabel(tr("Index"));
    title->setObjectName("blFinderAdminBarSubTitle");

    QPushButton *categoriesList = new QPushButton(tr("Categories"), this);
    categoriesList->setObjectName("btnLink");
    QPushButton *categoriesAdd = new QPushButton(tr("Add"), this);
    categoriesAdd->setObjectName("btnLink");
    QPushButton *keywordsList = new QPushButton(tr("Keywords"), this);
    keywordsList->setObjectName("btnLink");
    QPushButton *keywordsAdd = new QPushButton(tr("Add"), this);
    keywordsAdd->setObjectName("btnLink");

    m_contentLayout->addWidget(title, 2, 0, 1, 2);
    m_contentLayout->addWidget(categoriesList, 3, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(categoriesAdd, 3, 1, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(keywordsList, 4, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(keywordsAdd, 4, 1, 1, 1,Qt::AlignLeft);

    connect(categoriesList, SIGNAL(pressed()), this, SIGNAL(categoriesList()));
    connect(categoriesAdd, SIGNAL(pressed()), this, SIGNAL(categoriesAdd()));
    connect(keywordsList, SIGNAL(pressed()), this, SIGNAL(keywordsList()));
    connect(keywordsAdd, SIGNAL(pressed()), this, SIGNAL(keywordsAdd()));
}

void blFinderAdminBar::createFinderArea(){

    QLabel *title = new QLabel(tr("Finder"));
    title->setObjectName("blFinderAdminBarSubTitle");

    QPushButton *sectionsList = new QPushButton(tr("Sections"), this);
    sectionsList->setObjectName("btnLink");
    QPushButton *sectionsAdd = new QPushButton(tr("Add"), this);
    sectionsAdd->setObjectName("btnLink");

    QPushButton *sectionsLinks = new QPushButton(tr("Sections links"), this);
    sectionsLinks->setObjectName("btnLink");
    QPushButton *sectionsLinksAdd = new QPushButton(tr("Add"), this);
    sectionsLinksAdd->setObjectName("btnLink");

    QPushButton *tutorialsLinks = new QPushButton(tr("Tutorials links"), this);
    tutorialsLinks->setObjectName("btnLink");
    QPushButton *tutorialsLinksAdd = new QPushButton(tr("Add"), this);
    tutorialsLinksAdd->setObjectName("btnLink");

    m_contentLayout->addWidget(title, 5, 0, 1, 2);
    m_contentLayout->addWidget(sectionsList, 6, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(sectionsAdd, 6, 1, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(sectionsLinks, 7, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(sectionsLinksAdd, 7, 1, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(tutorialsLinks, 8, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(tutorialsLinksAdd, 8, 1, 1, 1,Qt::AlignLeft);

    connect(sectionsList, SIGNAL(pressed()), this, SIGNAL(sectionsList()));
    connect(sectionsAdd, SIGNAL(pressed()), this, SIGNAL(sectionsAdd()));
    connect(sectionsLinks, SIGNAL(pressed()), this, SIGNAL(sectionsLinks()));
    connect(sectionsLinksAdd, SIGNAL(pressed()), this, SIGNAL(sectionsLinksAdd()));
    connect(tutorialsLinks, SIGNAL(pressed()), this, SIGNAL(tutorialsLinks()));
    connect(tutorialsLinksAdd, SIGNAL(pressed()), this, SIGNAL(tutorialsLinksAdd()));
}

void blFinderAdminBar::createTutorialsArea(){

    QLabel *title = new QLabel(tr("Authors"));
    title->setObjectName("blFinderAdminBarSubTitle");


    QPushButton *originsList = new QPushButton(tr("Origins"), this);
    originsList->setObjectName("btnLink");
    QPushButton *originAdd = new QPushButton(tr("Add"), this);
    originAdd->setObjectName("btnLink");

    QPushButton *tutorialList = new QPushButton(tr("Tutorials"), this);
    tutorialList->setObjectName("btnLink");
    QPushButton *tutorialAdd = new QPushButton(tr("Add"), this);
    tutorialAdd->setObjectName("btnLink");

    m_contentLayout->addWidget(title, 9, 0, 1, 2);
    m_contentLayout->addWidget(originsList, 10, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(originAdd, 10, 1, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(tutorialList, 11, 0, 1, 1,Qt::AlignLeft);
    m_contentLayout->addWidget(tutorialAdd, 11, 1, 1, 1,Qt::AlignLeft);

    connect(tutorialList, SIGNAL(pressed()), this, SIGNAL(tutorialsList()));
    connect(tutorialAdd, SIGNAL(pressed()), this, SIGNAL(tutorialAdd()));
    connect(originsList, SIGNAL(pressed()), this, SIGNAL(originsList()));
    connect(originAdd, SIGNAL(pressed()), this, SIGNAL(originAdd()));
}
