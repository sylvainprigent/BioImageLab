#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialInfo.h"
#include "../model/blFinderSectionInfo.h"
#include "../../blWidgets/blFlowLayout.h"

class BLFINDER_EXPORT blFinderItemList : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderItemList(QWidget *parent = 0);

signals:
    void tutorial(int id);
    void section(int id);

public slots:
    void setInfos(QList<blFinderTutorialInfo> infos, QString title = "");
    void setInfos(QList<blFinderSectionInfo> infos, QString title = "");
    void setTutorial(blFinderTutorialInfo tuto, QString title = "");

private:
    void freeLayout();

private:
    blFlowLayout *m_layout;
    QLabel *m_titleLabel;
};
