#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderSectionInfo.h"

class BLFINDER_EXPORT blFinderAdminSectionEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminSectionEdit(QWidget *parent = 0);

signals:
    void editInfo(blFinderSectionInfo info);
    void cancel();
    void remove(int id);

public:
    void setInfo(blFinderSectionInfo info);

private slots:
    void emitEditInfo();
    void emitRemove();

private:
    int m_id;
    QLineEdit *m_name;
    QLineEdit *m_description;
    QLineEdit *m_imageUrl;
    QLineEdit *m_childrenTitle;
    QLineEdit *m_displayOrder;

private:
    QPushButton *m_removeButton;
};
