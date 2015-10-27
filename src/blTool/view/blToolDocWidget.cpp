#include "blToolDocWidget.h"

blToolDocWidget::blToolDocWidget(QWidget* parent) : QWidget(parent){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_htmlPage = new QWebView(this);
    layout->addWidget(m_htmlPage);
    this->setLayout(layout);
}

// public slots:
void blToolDocWidget::loadPage(QString page){

    page = page.replace("\\", "/");
    //qDebug() << "loadPage: " <<"file:///" + page;
    m_htmlPage->load( "file:///" + page);
}

void blToolDocWidget::setPageStyleSheet(QString cssFile){
    QWebSettings * settings = m_htmlPage->settings();
    QUrl myCssFileURL = QUrl::fromLocalFile(cssFile);
    qDebug() << "css url = " << myCssFileURL ;

    m_htmlPage->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    m_htmlPage->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    m_htmlPage->page()->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    m_htmlPage->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    settings->setUserStyleSheetUrl(myCssFileURL);
}


