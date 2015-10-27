#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderSectionInfo.h"
#include "../model/blFinderSectionsLinkInfo.h"

class BLFINDER_EXPORT blFinderAdminSectionsLinkEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminSectionsLinkEdit(QList<blFinderSectionInfo> sections, QWidget *parent = 0);

signals:
    void editInfo(blFinderSectionsLinkInfo info);
    void cancel();

private slots:
    void emitEditInfo();

private:
    int m_id;
    QComboBox *m_parentSectionsList;
    QComboBox *m_childSectionsList;

};
