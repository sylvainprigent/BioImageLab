#include "blFinderTutorialView.h"


blFinderTutorialView::blFinderTutorialView(QWidget *parent)
    :QWidget(parent){

    QVBoxLayout *thisLayout = new QVBoxLayout;
    thisLayout->setContentsMargins(0,7,0,0);

    QPushButton *openToolButton = new QPushButton(tr("Open"), this);
    openToolButton->setObjectName("btnPrimary");
    m_webView = new QWebView(this);

    thisLayout->addWidget(openToolButton, 1, Qt::AlignLeft);
    thisLayout->addWidget(m_webView);

    QWidget *totalWidget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(0,0,0,0);
    totalWidget->setLayout(thisLayout);
    this->setLayout(totalLayout);
    totalLayout->addWidget(totalWidget);
    totalWidget->setObjectName("blFinderTutorialView");

    connect(openToolButton, SIGNAL(pressed()), this, SLOT(emitOpenTool()));
}

void blFinderTutorialView::emitOpenTool(){
    emit openTool(m_xmlFile);
}

void blFinderTutorialView::setTutorial(blFinderTutorialInfo tuto){

    QString page = tuto.docUrl();
    m_xmlFile = tuto.xmlUrl();

    page = page.replace("\\", "/");
    //qDebug() << "loadPage: " <<"file:///" + page;
    m_webView->load( "file:///" + page);
}
