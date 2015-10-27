#ifndef BLTOOLINPUTSELECTORWIDGET_H
#define BLTOOLINPUTSELECTORWIDGET_H

#include <QtWidgets>
#include "../model/blToolIO.h"
#include "../model/blioDataInfo.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolInputSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    blToolInputSelectorWidget(blToolIO toolIO, QWidget* parent = 0);

signals:
    void error(QString);

public:
    // getters
    blioDataInfo* inputsInfo();
    blioDataInfo *getData();

private:
    QTabWidget *m_tabWidget;
};

#endif // BLTOOLINPUTSELECTORWIDGET_H
