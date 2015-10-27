#include "blToolHistoryBar.h"

blToolHistoryBar::blToolHistoryBar(QWidget *parent) : QWidget(parent)
{
   // titleWidget
    QWidget *titleWidget = new QWidget(this);
    QHBoxLayout * titleLayout = new QHBoxLayout;
    titleLayout->setContentsMargins(0,0,0,0);
    titleWidget->setLayout(titleLayout);
    QLabel *titlelabel = new QLabel("History", this);
    titlelabel->setObjectName("blToolHistoryBarTitleLabel");
    titleLayout->addWidget(titlelabel);
    titleWidget->setFixedHeight(32);
    titleWidget->setObjectName("blToolHistoryBarTitleWidget");

    // content
    QWidget *contentWidget = new QWidget(this);
    m_contentLayout = new QVBoxLayout;
    m_contentLayout->setContentsMargins(0,0,0,0);
    m_contentLayout->setSpacing(2);
    contentWidget->setLayout(m_contentLayout);

    m_contentLayout->addWidget(new QWidget(this), 1, Qt::AlignTop);

    // this widget
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(contentWidget);
    scroll->setObjectName("blToolHistoryBarScrollArea");
    //scroll->setStyleSheet(".QWidget{background-color: #404040;}");

    layout->addWidget(titleWidget);
    layout->addWidget(scroll);

    QWidget *thisWidget = new QWidget(this);
    thisWidget->setLayout(layout);
    QHBoxLayout* thislayout = new QHBoxLayout;
    thislayout->setContentsMargins(0,0,0,0);
    thislayout->addWidget(thisWidget);
    this->setLayout(thislayout);
    thisWidget->setObjectName("blToolHistoryBarContainer");

    m_lastId = 0;
}

void blToolHistoryBar::addHistory(QString fileUrl, QString toolName){
    blToolHistoryInfo history;
    history.setFileUrl(fileUrl);
    history.setToolName(toolName);
    QFileInfo filInfo(fileUrl);
    QString date = filInfo.lastModified().toString("dd/MM/yyyy HH:mm:ss");
    history.setLastModified(date);
    history.setId(m_lastId++);
    blToolHistoryBarWidget *w = new blToolHistoryBarWidget(history);
    m_contentLayout->insertWidget(0, w, 0, Qt::AlignTop);

    connect(w, SIGNAL(deleteHistory(blToolHistoryInfo)), this, SIGNAL(deleteHistory(blToolHistoryInfo)));
    connect(w, SIGNAL(deleteHistory(int)), this, SIGNAL(deleteHistory(int)));
    connect(w, SIGNAL(deleteHistory(QString)), this, SIGNAL(deleteHistory(QString)));
    connect(w, SIGNAL(openHistory(QString)), this, SIGNAL(openHistory(QString)));
}

void blToolHistoryBar::removeHistory(int id){
    for(int i = 0 ; i < m_contentLayout->count() ; ++i){
        QWidget* w = m_contentLayout->itemAt(i)->widget();
        blToolHistoryBarWidget* wh = qobject_cast<blToolHistoryBarWidget*>(w);
        if (wh != NULL){
            if (wh->id() == id){
                delete wh;
            }
        }
    }
}
