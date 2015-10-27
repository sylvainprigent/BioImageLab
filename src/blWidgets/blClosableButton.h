#pragma once

#include <QtWidgets>
#include "blWidgetsExport.h"

class BLWIDGETS_EXPORT blClosableButton : public QPushButton
{
    Q_OBJECT
public:
    explicit blClosableButton(bool closable = true, QWidget *parent = 0);

signals:
    void clicked(int id);
    void closed(int id);

public:
    int id();
    //QPushButton *button();

public slots:
    void setId(int id);
    //void setChecked(bool value);

private slots:
    void emitClicked();
    void emitClosed();

private:
    int m_id;
    //QPushButton *m_button;
};
