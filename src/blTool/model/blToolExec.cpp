#include "blToolExec.h"

#include <QDebug>
#include <QDir>

#include "blToolExecLog.h"

blToolExec::blToolExec()
{
    m_outputData = NULL;
    /// \todo there is a memory leak here
    m_process = new QProcess;
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(updateError()));
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateText()));

}

// setters
void blToolExec::setToolInfo(blToolInfo* toolInfo){
    m_toolInfo = toolInfo;
}

void blToolExec::setInputDataInfo(blioDataInfo* inputsInfo){
    m_inputsInfo = inputsInfo;
}

void blToolExec::setParameters(blioParameters* parameters){
    m_parameters = parameters;
}

// settings
void blToolExec::setOutputDir(QString outputDir){
    m_outputDir = outputDir;
}

void blToolExec::run(blToolInfo* toolInfo, blioDataInfo *inputData, blioParameters* parameters){

    m_toolInfo = toolInfo;
    m_inputsInfo = inputData;
    m_parameters = parameters;
    this->start();
}

// run
void blToolExec::run(){

    emit startedProcess();
    m_outputData = new blioDataInfo();
    QString cmdOrigin = m_toolInfo->command();
    QString cmd;
    int inputCount = m_inputsInfo->count();
    for (unsigned int i = 0 ; i < m_inputsInfo->count() ; ++i ){
        // initial command
        cmd = m_toolInfo->command();
        cmd += " ";

        // parse inputs
        blioDataList dataList = m_inputsInfo->at(i);
        for (unsigned int c =0 ; c < dataList.count() ; ++c){
            cmd = cmd.replace("$" + dataList.idAt(c) + " ", ""+dataList.urlAt(c)+"" + " ", Qt::CaseSensitive);
        }

        // parse parameters
        for (unsigned int c =0 ; c < m_parameters->count() ; ++c){
            cmd = cmd.replace("$" + m_parameters->keyAt(c) + " ", m_parameters->valueAt(c)  + " ", Qt::CaseSensitive);
        }

        // parse output
        blToolIO ios = m_toolInfo->getIO();
        blioDataList outputDataList;
        int indexFile = this->getNextIndexFile("data_");
        for (unsigned int t = 0 ; t < ios.outputsCount() ; ++t){
            QString generatedURL = m_outputDir + QDir::separator() + "data_" + QString::number(indexFile+t) + "." + ios.outputTypeAt(t);
            cmd = cmd.replace("$" + ios.outputNameAt(t) + " ", ""+generatedURL+""  + " ", Qt::CaseSensitive);
            outputDataList.add(ios.outputTypeAt(t), ios.outputNameAt(t), generatedURL);
        }
        m_outputData->add(outputDataList);
/*
#ifdef Q_OS_WIN32
  cmd = cmd.replace("/", "\\");
#endif
*/
        // run cmd
        this->runCommand(cmd);
        emit progress( int((float(i) / float(inputCount)) * 100.0));
    }

    // save exec file
    m_historyLogFile = m_outputDir + QDir::separator() + "history_"+ m_toolInfo->name() +"_"+ QString::number(getNextIndexFile("history_"))+".dat";
    blToolExecLog history;

    m_toolInfo->setCommand(cmd);
    history.setInputData(m_inputsInfo);
    history.setOutputData(m_outputData);
    history.setParameters(m_parameters);
    history.setToolInfo(m_toolInfo);
    history.saveas(m_historyLogFile);
    m_toolInfo->setCommand(cmdOrigin);
    this->processFinished(0);

}

void blToolExec::processFinished(int){

    emit processHasFinished(m_historyLogFile, m_toolInfo->name());
    emit processHasFinished();
}

void blToolExec::runCommand(QString cmd){

    qDebug() << "cmd = " << cmd;
    m_process->start(cmd);
    m_process->waitForFinished();
}

void blToolExec::processError(QProcess::ProcessError error){
    qDebug() << error;
}

unsigned int blToolExec::getNextIndexFile(QString prefix){
    QStringList files = QDir( m_outputDir ).entryList();
    unsigned int maxi = 0;

    for(int i = 0 ; i < files.count() ; ++i){
        QString curentFile = files[i];
        if (curentFile.startsWith(prefix)){
            int posUnderscore = curentFile.lastIndexOf("_");
            int posdot = curentFile.indexOf(".");
            unsigned int num = curentFile.mid(posUnderscore+1, posdot-posUnderscore-1).toInt();
            if (num > maxi){
                maxi = num;
            }
        }
    }
    return maxi+1;
}

//slots
void blToolExec::updateError()
{
    QByteArray data = m_process->readAllStandardError();
    //qDebug() << "process error = " << data;
    emit processError(QString(data));
}

void blToolExec::updateText()
{
    QByteArray data = m_process->readAllStandardOutput();
    //qDebug() << "process verbose = " << data;
    emit processVerbose(QString(data));
}
