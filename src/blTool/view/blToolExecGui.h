#ifndef BLTOOLEXECGUI_H
#define BLTOOLEXECGUI_H

#include <QtWidgets>
#include "blToolCore/model/blToolInfo.h"
#include "../view/blToolRunWidget.h"
#include "../view/blToolInputSelectorWidget.h"
#include "../view/blToolParameterSelectorWidget.h"
#include "../view/blToolStandardOutputViewer.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolExecGui : public QWidget
{
    Q_OBJECT
public:
    blToolExecGui(blToolInfo* toolInfo, QWidget* parent = 0);

signals:
    void run(blToolInfo*, blioDataInfo*, blioParameters*);
    void help(QString);
    void changeOutputDir(QString);
    void error(QString);
    void processHasFinished(QString, QString);

public slots:
    void processHasFinished();
    void setProgress(int progress);
    void updateError(QString data);
    void updateOutput(QString data);
    void saveOutputMetaData(int processId, QString outputDir, blioDataInfo*inputs, blioDataInfo*outputs, blioParameters*params, blToolInfo*toolinfo);
    void progressFinished(int processId, QString toolName);

private slots:
    void askRun();

private:
    void buildGui(blToolInfo *toolInfo);

private:
    blToolInfo* m_toolInfo;
    blToolRunWidget *m_runWidget;
    blToolInputSelectorWidget *m_inputSelectorWidget;
    blToolParameterSelectorWidget *m_parametersSelectorWidget;
    blToolStandardOutputViewer *m_standardOutputViewer;
};

#endif // BLTOOLEXECGUI_H
