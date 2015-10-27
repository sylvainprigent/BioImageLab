#pragma once

#include "blFinderItemList.h"
#include "blFinderTutorialView.h"

class BLFINDER_EXPORT blFinderBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderBrowser(QWidget *parent = 0);

signals:
    void tutorial(int id);
    void section(int id);
    void openTool(QString xmlUrl);

public slots:
    void setInfos(QList<blFinderTutorialInfo> infos, QString title = "");
    void setInfos(QList<blFinderSectionInfo> infos, QString title = "");
    void setTutorial(blFinderTutorialInfo tuto);

private:
    blFinderItemList *m_itemList;
    blFinderTutorialView *m_tutorialView;

};
