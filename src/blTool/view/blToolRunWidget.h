#ifndef BLTOOLRUNWIDGET_H
#define BLTOOLRUNWIDGET_H

#include <QtWidgets>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolRunWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolRunWidget(QWidget *parent = 0);

signals:
    void run();

public slots:
    void setProgressRange(int minValue, int maxValue);
    void setProgress(int value);

    void setRunning();
    void setRunFinished();

private:
    QPushButton *m_runButton;
    QProgressBar *m_progressBar;
};

#endif // BLTOOLRUNWIDGET_H
