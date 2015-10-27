#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderOriginInfo.h"

class BLFINDER_EXPORT blFinderAdminOriginEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminOriginEdit(QWidget *parent = 0);

signals:
    void editInfo(blFinderOriginInfo info);
    void cancel();
    void remove(int id);

public:
    void setInfo(blFinderOriginInfo info);

private slots:
    void emitEditInfo();
    void emitRemove();

private:
    int m_id;
    QLineEdit *m_name;

private:
    QPushButton *m_removeButton;
};
