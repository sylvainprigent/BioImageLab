#ifndef BLTOOLINPUTSELECTORWIDGET_H
#define BLTOOLINPUTSELECTORWIDGET_H

#include <QtWidgets>
#include "blToolCore/model/blToolIO.h"
#include "blToolCore/model/blioDataInfo.h"
#include "blToolCore/model/blioParameters.h"
#include "blToolCore/model/blToolInfo.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolInputSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    blToolInputSelectorWidget(blToolIO toolIO, QWidget* parent = 0);

signals:
    void changeOutputDir(QString);
    void error(QString);
    void progressHasFinished(QString,QString);

public:
    // getters
    blioDataInfo *getData();

public:
    void saveOutputMetaData(int processId, QString outputDir, blioDataInfo* inputs, blioDataInfo* outputs, blioParameters* params, blToolInfo* toolinfo);
    void progressFinished(int processId, QString toolName);
private:
    QTabWidget *m_tabWidget;

};

#endif // BLTOOLINPUTSELECTORWIDGET_H
