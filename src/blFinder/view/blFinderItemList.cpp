#include "blFinderItemList.h"
#include "blFinderItem.h"
#include <QtWebEngineWidgets/QWebEngineView>

blFinderItemList::blFinderItemList(QWidget *parent) : QWidget(parent)
{
    m_layout = new blFlowLayout;


    QVBoxLayout *thisLayout = new QVBoxLayout;
    thisLayout->setContentsMargins(0,0,0,0);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setObjectName("blFinderItemListTitle");

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setObjectName("blFinderItemListScroll");
    scroll->setWidgetResizable(true);
    QWidget *container = new QWidget(this);
    container->setLayout(m_layout);
    scroll->setWidget(container);

    thisLayout->addWidget(m_titleLabel, 0, Qt::AlignTop);
    thisLayout->addWidget(scroll);

    QWidget *totalWidget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(0,0,0,0);
    totalWidget->setLayout(thisLayout);
    this->setLayout(totalLayout);
    totalLayout->addWidget(totalWidget);
    totalWidget->setObjectName("blFinderItemList");
}

void blFinderItemList::setInfos(QList<blFinderTutorialInfo> infos, QString title){

    this->freeLayout();
    for (int i = 0 ; i < infos.count() ; ++i){
        blFinderItem *item = new blFinderItem(infos[i]);
        m_layout->addWidget(item);
        connect(item, SIGNAL(clicked(int)), this, SIGNAL(tutorial(int)));
    }
    m_titleLabel->setText(title);
}

void blFinderItemList::setInfos(QList<blFinderSectionInfo> infos, QString title){

    this->freeLayout();
    for (int i = 0 ; i < infos.count() ; ++i){
        blFinderItem *item = new blFinderItem(infos[i]);
        m_layout->addWidget(item);
        connect(item, SIGNAL(clicked(int)), this, SIGNAL(section(int)));
    }
    m_titleLabel->setText(title);
}

void blFinderItemList::setTutorial(blFinderTutorialInfo tuto, QString title){
    this->freeLayout();

    QWebEngineView *htmlPage = new QWebEngineView(this);
    QString page = tuto.docUrl();
    page = page.replace("\\", "/");
    qDebug() << "loadPage: " <<"file:///" + page;
    htmlPage->load( "file:///" + page);

    m_layout->addWidget(htmlPage);
    m_titleLabel->setText(title);
}

void blFinderItemList::freeLayout(){
    QLayoutItem* item;
    while ( ( item = m_layout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}
