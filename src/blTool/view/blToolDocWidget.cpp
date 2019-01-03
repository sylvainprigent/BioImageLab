#include "blToolDocWidget.h"

blToolDocWidget::blToolDocWidget(QWidget* parent) : QWidget(parent){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_htmlPage = new blWebBrowser(this);
    layout->addWidget(m_htmlPage);
    this->setLayout(layout);
}

// public slots:
void blToolDocWidget::loadPage(QString page){
    //qDebug() << "load page = " << page;
    m_htmlPage->setHomePage(page, false);
}

void blToolDocWidget::setPageStyleSheet(QString cssFile){
    QWebEngineSettings * settings = m_htmlPage->webView()->settings();
    QUrl myCssFileURL = QUrl::fromLocalFile(cssFile);
    qDebug() << "css url = " << myCssFileURL ;

    m_htmlPage->webView()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    m_htmlPage->webView()->page()->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    //m_htmlPage->webView()->page()->settings()->setAttribute(QWebEngineSettings::OfflineWebApplicationCacheEnabled, true);
    //m_htmlPage->webView()->page()->setLinkDelegationPolicy(QWebEnginePage::DelegateAllLinks);
    //settings->setUserStyleSheetUrl(myCssFileURL);
}


