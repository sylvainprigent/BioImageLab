#ifndef BLTOOLDOCWIDGET_H
#define BLTOOLDOCWIDGET_H

#include <QtWidgets>
#include <QtWebKitWidgets/QWebView>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolDocWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolDocWidget(QWidget *parent = 0);

public:
    void setPageStyleSheet(QString cssFile);

public slots:
    /// \fn void loadPage(QString page);
    /// \brief Load an html page
    /// \param[in] page URL of the page to be loaded
    void loadPage(QString page);

private:
    QWebView *m_htmlPage; ///< web page container

};

#endif // BLTOOLDOCWIDGET_H
