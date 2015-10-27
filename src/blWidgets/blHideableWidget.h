#ifndef BLHIDEABLEWIDGET_H
#define BLHIDEABLEWIDGET_H

#include <QtWidgets>
#include "blWidgetsExport.h"
#include "blFlowLayout.h"

class BLWIDGETS_EXPORT blHideableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blHideableWidget(QString title, int level = 1, QWidget *parent = 0, bool useFlowLayout = false);

signals:

public:
    void addWidget(QWidget* widget);
    void setUseAnimation(bool useAnimation);

private slots:
    void switchView();

private:
    QWidget *m_hideableWidget;
    QVBoxLayout *m_layout;
    blFlowLayout *m_flowLayout;
    QPushButton *m_button;
    bool m_useFlowLayout;

    bool m_isVisible;
    int m_height;
    QPropertyAnimation *m_animation;
    bool m_useAnimation;

};

#endif // BLHIDEABLEWIDGET_H
