#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialInfo.h"
#include <QtWebEngineWidgets/QWebEngineView>

class BLFINDER_EXPORT blFinderTutorialView : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderTutorialView(QWidget *parent = 0);

signals:
    void openTool(QString xmlFile);

public slots:
    void setTutorial(blFinderTutorialInfo tuto);

private slots:
    void emitOpenTool();

private:
   QWebEngineView *m_webView;

private:
   QString m_xmlFile;

};
