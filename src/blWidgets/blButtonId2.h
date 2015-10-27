#pragma once

#include <QtWidgets>
#include "blWidgetsExport.h"

class BLWIDGETS_EXPORT blButtonId2 : public QPushButton
{
    Q_OBJECT
public:
    explicit blButtonId2(QString title, QWidget *parent = 0);

signals:
    void clicked(int id1, int id2);

public:
    int id1();
    int id2();

public slots:
    void setId1(int id);
    void setId2(int id);

private slots:
    void emitClicked();

private:
    int m_id1;
    int m_id2;
};
