#pragma once

#include <QtWidgets>
#include <QtWebKitWidgets/QWebView>
#include "blWidgetsExport.h"

class BLWIDGETS_EXPORT blWebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit blWebBrowser(QWidget *parent = 0);

signals:

public slots:
    void setHomePage(QString homePage, bool isWebURL);
    QWebView *webView();


private slots:
    void forward();
    void back();
    void home();

private:
    QWidget *createToolBar();

private:
    QWebView *m_webView;
    bool m_isWebURL;
    QString m_homeURL;
};
