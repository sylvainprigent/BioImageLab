#ifndef BLTOOLINPUTSELECTORWIDGETDIR_H
#define BLTOOLINPUTSELECTORWIDGETDIR_H

#include "blToolInputSelectorWidgetInterface.h"

class BLTOOL_EXPORT blToolInputSelectorWidgetDir : public blToolInputSelectorWidgetInterface
{
    Q_OBJECT
public:
    blToolInputSelectorWidgetDir(blToolIO toolIO, QWidget* parent = 0);

signals:
    void error(QString);

public:
    blioDataInfo *getData();
    void progressFinished(int processId, QString toolName);
};

#endif // BLTOOLINPUTSELECTORWIDGETDIR_H
