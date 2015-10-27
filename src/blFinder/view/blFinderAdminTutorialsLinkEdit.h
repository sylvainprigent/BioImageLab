#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialsLinkInfo.h"
#include "../model/blFinderCategoryInfo.h"
#include "../model/blFinderTutorialInfo.h"

class BLFINDER_EXPORT blFinderAdminTutorialsLinkEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminTutorialsLinkEdit(QList<blFinderCategoryInfo> categories, QList<blFinderTutorialInfo> tutorials, QWidget *parent = 0);

signals:
    void editInfo(blFinderTutorialsLinkInfo info);
    void cancel();

private slots:
    void emitEditInfo();

private:
    int m_id;
    QComboBox *m_categoriesList;
    QComboBox *m_tutorialsList;

};
