#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderAuthorInfo.h"

class BLFINDER_EXPORT blFinderAdminAuthorEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminAuthorEdit(QWidget *parent = 0);

signals:
    void editInfo(blFinderAuthorInfo info);
    void cancel();
    void remove(int id);

public:
    void setInfo(blFinderAuthorInfo info);

private slots:
    void emitEditInfo();
    void emitDelete();

private:
    int m_id;
    QLineEdit *m_name;
    QLineEdit *m_firstname;
    QPushButton *m_deleteButton;
};
