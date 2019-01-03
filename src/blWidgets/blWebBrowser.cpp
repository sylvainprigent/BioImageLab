#include "blWebBrowser.h"

blWebBrowser::blWebBrowser(QWidget *parent)
    : QWidget(parent){

    QVBoxLayout *thisLayout = new QVBoxLayout;
    thisLayout->setContentsMargins(0,0,0,0);

    QWidget *toolBar = this->createToolBar();
    toolBar->setMaximumHeight(48);
    m_webView = new QWebEngineView(this);

    thisLayout->addWidget(toolBar);
    thisLayout->addWidget(m_webView);


    QWidget *totalWidget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(0,0,0,0);
    totalWidget->setLayout(thisLayout);
    this->setLayout(totalLayout);
    totalLayout->addWidget(totalWidget);
    totalWidget->setObjectName("blWebBrowser");

}

QWidget *blWebBrowser::createToolBar(){

    QWidget* toolbar = new QWidget(this);

    QPushButton* backButton = new QPushButton(this);
    backButton->setFixedSize(32,32);
    connect(backButton, SIGNAL(pressed()), this, SLOT(back()));
    backButton->setObjectName("blWebBrowserBack");

    QPushButton* forwardButton = new QPushButton(this);
    forwardButton->setFixedSize(32,32);
    connect(forwardButton, SIGNAL(pressed()), this, SLOT(forward()));
    forwardButton->setObjectName("blWebBrowserForward");

    QPushButton* homeButton = new QPushButton(this);
    homeButton->setFixedSize(32,32);
    connect(homeButton, SIGNAL(pressed()), this, SLOT(home()));
    homeButton->setObjectName("blWebBrowserHome");

    QHBoxLayout *barLayout = new QHBoxLayout;
    barLayout->addWidget(backButton);
    barLayout->addWidget(forwardButton);
    barLayout->addWidget(homeButton);
    barLayout->addWidget(new QWidget(this));

    toolbar->setLayout(barLayout);
    return toolbar;
}

void blWebBrowser::forward(){
    m_webView->forward();
}

void blWebBrowser::back(){
    m_webView->back();
}

void blWebBrowser::home(){
    this->setHomePage(m_homeURL, m_isWebURL);
}

void blWebBrowser::setHomePage(QString pageURL, bool isWebURL){

    m_homeURL = pageURL;
    m_isWebURL = isWebURL;
    if (m_isWebURL){
        m_webView->load(pageURL);
    }
    else{
        m_homeURL = m_homeURL.replace("\\", "/");
        m_webView->load( "file:///" + m_homeURL);
    }
}

QWebEngineView *blWebBrowser::webView(){
    return m_webView;
}
