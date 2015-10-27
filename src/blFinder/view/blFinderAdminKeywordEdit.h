#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderKeywordInfo.h"

class BLFINDER_EXPORT blFinderAdminKeywordEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminKeywordEdit(QList<blFinderCategoryInfo> categories, QWidget *parent = 0);

signals:
    void editInfo(blFinderKeywordInfo info);
    void cancel();
    void remove(int id);

public:
    void setInfo(blFinderKeywordInfo info);

private slots:
    void emitEditInfo();
    void emitRemove();

private:
    int m_id;
    QLineEdit *m_name;
    QComboBox *m_categoriesList;

private:
    QPushButton *m_removeButton;
};
