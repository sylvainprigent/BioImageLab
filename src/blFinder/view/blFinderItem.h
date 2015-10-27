#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialInfo.h"
#include "../model/blFinderSectionInfo.h"

class BLFINDER_EXPORT blFinderItem : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderItem(blFinderTutorialInfo info, QWidget *parent = 0);
    explicit blFinderItem(blFinderSectionInfo info, QWidget *parent = 0);

signals:
    void clicked(int id);

private slots:

protected:
    /// \fn virtual void mouseReleaseEvent(QMouseEvent *);
    /// \brief Reimplement from QWidget to handle left click event
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    int m_id;
};
