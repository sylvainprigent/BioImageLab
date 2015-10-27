#pragma once

#include <QtWidgets>
#include "blWidgetsExport.h"

class BLWIDGETS_EXPORT blButtonId : public QPushButton
{
    Q_OBJECT
public:
    explicit blButtonId(QString title, QWidget *parent = 0);

signals:
    void clicked(int id);

public:
    int id();

public slots:
    void setId(int id);

private slots:
    void emitClicked();

private:
    int m_id;
};
