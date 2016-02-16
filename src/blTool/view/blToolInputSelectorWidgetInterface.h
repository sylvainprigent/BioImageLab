#ifndef BLTOOLINPUTSELECTORWIDGETINTERFACE_H
#define BLTOOLINPUTSELECTORWIDGETINTERFACE_H

#include <QtWidgets>
#include "blToolCore/model/blToolIO.h"
#include "blToolCore/model/blioDataInfo.h"
#include "blToolCore/model/blioParameters.h"
#include "blToolCore/model/blToolInfo.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolInputSelectorWidgetInterface : public QWidget
{
    Q_OBJECT
public:
    blToolInputSelectorWidgetInterface(blToolIO toolIO, QWidget* parent = 0);

signals:
    void changeOutputDir(QString);
    void error(QString);
    void progressHasFinished(QString historyFile, QString toolName);

public:
    virtual blioDataInfo *getData() = 0;
    virtual void saveOutputMetaData(int processId, QString outputDir, blioDataInfo* inputs, blioDataInfo* outputs, blioParameters* params, blToolInfo* toolinfo);
    virtual void progressFinished(int processId, QString toolName) = 0;

protected:
    QString m_historyLogFile;
};

#endif // BLTOOLINPUTSELECTORWIDGETINTERFACE_H
