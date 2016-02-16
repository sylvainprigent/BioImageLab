#ifndef BLTOOLEXECLOG_H
#define BLTOOLEXECLOG_H

#include "blioDataInfo.h"
#include "blioParameters.h"
#include "blToolInfo.h"
#include "blToolCoreExport.h"

class BLTOOLCORE_EXPORT blToolExecLog
{
public:
    blToolExecLog();

public:
    // setters
    void setInputData(blioDataInfo* data);
    void setOutputData(blioDataInfo* data);
    void setParameters(blioParameters* parameters);
    void setToolInfo(blToolInfo* toolInfo);

    // getters
    blioDataInfo* inputData();
    blioDataInfo* outputData();
    blioParameters* parameters();
    blToolInfo* toolInfo();

    // load/save
    void print();
    void saveas(QString fileUrl);
    void load(QString fileUrl);

private:
    blioDataInfo* m_inputData;
    blioDataInfo* m_outputData;
    blioParameters* m_parameters;
    blToolInfo* m_toolInfo;

};

#endif // BLTOOLEXECLOG_H
