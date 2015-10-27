#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderCategoryInfo.h"

class BLFINDER_EXPORT blFinderAdminCategoryEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminCategoryEdit(QWidget *parent = 0);

signals:
    void editInfo(blFinderCategoryInfo info);
    void cancel();
    void remove(int id);

public:
    void setInfo(blFinderCategoryInfo info);

private slots:
    void emitEditInfo();
    void emitRemove();

private:
    int m_id;
    QLineEdit *m_name;

private:
    QPushButton *m_removeButton;
};
