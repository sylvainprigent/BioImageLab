#ifndef BLTOOLEXEC_H
#define BLTOOLEXEC_H

#include "blToolInfo.h"
#include "blioDataInfo.h"
#include "blioParameters.h"
#include <QThread>
#include <QProcess>
#include "blToolCoreExport.h"

class BLTOOLCORE_EXPORT blToolExec : public QThread
{
    Q_OBJECT
public:
    blToolExec();

signals:
    void processHasFinished(QString, QString);
    void processHasFinished();
    void startedProcess();
    void progress(int);
    void processError(QString);
    void processVerbose(QString);
    void progressOutput(int, QString, blioDataInfo*, blioDataInfo*, blioParameters*, blToolInfo*);
    void processFinished(int, QString);

public slots:
    void processError(QProcess::ProcessError error);

public slots:
    // run
    void run();
    void run(blToolInfo* toolInfo, blioDataInfo *inputData, blioParameters* parameters);

private slots:
    void updateError();
    void updateText();

public:
    // setters
    void setToolInfo(blToolInfo* toolInfo);
    void setInputDataInfo(blioDataInfo* inputsInfo);
    void setParameters(blioParameters* parameters);
    void setBinariesDir(QString dir);

public slots:
    // settings
    void setOutputDir(QString outputDir);

private:
    // internal methods
    unsigned int getNextIndexFile(QString prefix);
    void runCommand(QString cmd);

private:
    blToolInfo* m_toolInfo;
    blioDataInfo* m_inputsInfo;
    blioParameters* m_parameters;
    QString m_outputDir;

private:
    blioDataInfo* m_outputData;
    QProcess* m_process;
    QString m_historyLogFile;
    QString m_binariesDir;
};

#endif // BLTOOLEXEC_H
