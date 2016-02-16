#ifndef BLTOOLINPUTSELECTORWIDGETFILE_H
#define BLTOOLINPUTSELECTORWIDGETFILE_H

#include "blToolInputSelectorWidgetInterface.h"

class BLTOOL_EXPORT blToolInputSelectorWidgetFile : public blToolInputSelectorWidgetInterface
{
    Q_OBJECT
public:
    blToolInputSelectorWidgetFile(blToolIO toolIO, QWidget* parent = 0);

public:
    blioDataInfo * getData();
    void progressFinished(int processId, QString toolName);
};

#endif // BLTOOLINPUTSELECTORWIDGETFILE_H
