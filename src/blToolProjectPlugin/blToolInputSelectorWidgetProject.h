#ifndef BLTOOLINPUTSELECTORWIDGETPROJECT_H
#define BLTOOLINPUTSELECTORWIDGETPROJECT_H

#include "blTool/view/blToolInputSelectorWidgetInterface.h"
#include "blToolProjectPluginExport.h"
#include "blToolInputWidgetProject.h"

class BLTOOLPROJECTPLUGIN_EXPORT blToolInputSelectorWidgetProject : public blToolInputSelectorWidgetInterface
{
    Q_OBJECT
public:
    blToolInputSelectorWidgetProject(blToolIO toolIO, QWidget* parent = 0);

signals:
    void error(QString);

public:
    blioDataInfo *getData();
    void saveOutputMetaData(int processId, QString outputDir, blioDataInfo* inputs, blioDataInfo* outputs, blioParameters* params, blToolInfo* toolinfo);
    void progressFinished(int processId, QString toolName);

private slots:
    void setProjectNameToSelectors(QString projectName);
    void changeColumnOutputDir(QString);

private:
    void getProjectsList();

private:
    QComboBox* m_projectSelector;
    QLineEdit *m_outputColumnName;
    QList<blToolInputWidgetProject*> m_selectors;

private:
    blProjectModel *m_projectModel;
};

#endif // BLTOOLINPUTSELECTORWIDGETPROJECT_H
