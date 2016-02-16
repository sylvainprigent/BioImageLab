#include "blToolInputSelectorWidgetInterface.h"

#include "blToolInputWidget.h"
#include "blToolCore/model/blToolExecLog.h"

blToolInputSelectorWidgetInterface::blToolInputSelectorWidgetInterface(blToolIO toolIO,QWidget *parent)
    :QWidget(parent){

}

void blToolInputSelectorWidgetInterface::saveOutputMetaData(int processId, QString outputDir, blioDataInfo* inputs, blioDataInfo* outputs, blioParameters* params, blToolInfo* toolinfo){

    m_historyLogFile = outputDir + QDir::separator() + "history_"+ toolinfo->name() +"_"+ QString::number(processId)+".dat";
    blToolExecLog history;

    history.setInputData(inputs);
    history.setOutputData(outputs);
    history.setParameters(params);
    history.setToolInfo(toolinfo);
    history.saveas(m_historyLogFile);
}
