#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../view/blFinderBrowser.h"

class BLFINDER_EXPORT blFinderDefaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderDefaultWidget(QWidget *parent = 0);

signals:
    void openTool(QString xmlUrl);

public:
    void setToolShedDir(QString toolShedDir);
    void setFinderDir(QString finderDir);

public slots:
    void setItems(QList<blFinderTutorialInfo> infos, QString title = "");
    void finder();

private slots:
    void searchKeyword(QString keyword);
    void searchSoftware(int id);
    void origin(int origin);
    void finderSection(int sectionID);
    void finderTutorial(int id);

private:
    QString m_toolShedDir;
    QString m_finderDir;

private:
    QVBoxLayout *m_layout;
    blFinderBrowser *m_centralWidget;
};
