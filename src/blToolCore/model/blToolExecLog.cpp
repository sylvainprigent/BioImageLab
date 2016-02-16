#include "blToolExecLog.h"
#include <QFile>
#include <iostream>

blToolExecLog::blToolExecLog()
{
    m_inputData = NULL;
    m_outputData = NULL;
    m_parameters = NULL;
    m_toolInfo = NULL;
}

// setters
void blToolExecLog::setInputData(blioDataInfo* data){
    m_inputData = data;
}

void blToolExecLog::setOutputData(blioDataInfo* data){
    m_outputData = data;
}

void blToolExecLog::setParameters(blioParameters* parameters){
    m_parameters = parameters;
}

void blToolExecLog::setToolInfo(blToolInfo* toolInfo){
    m_toolInfo = toolInfo;
}

// getters
blioDataInfo* blToolExecLog::inputData(){
    return m_inputData;
}

blioDataInfo* blToolExecLog::outputData(){
    return m_outputData;
}

blioParameters* blToolExecLog::parameters(){
    return m_parameters;
}

blToolInfo* blToolExecLog::toolInfo(){
    return m_toolInfo;
}

// load/save
void blToolExecLog::saveas(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << *m_inputData;
    out << *m_outputData;
    out << *m_parameters;
    out << *m_toolInfo;
}

void blToolExecLog::print(){
    std::cout << "- log tool exec file, content:" << std::endl;

    std::cout << "-- Tool info" << std::endl;
    m_toolInfo->print();

    std::cout << "-- Parameters" << std::endl;
    m_parameters->print();

    std::cout << "-- Input data" << std::endl;
    m_inputData->print();

    std::cout << "-- Output data" << std::endl;
    m_outputData->print();
}

void blToolExecLog::load(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    m_inputData = new blioDataInfo;
    m_outputData = new blioDataInfo;
    m_parameters = new blioParameters;
    m_toolInfo = new blToolInfo;
    in >> *m_inputData ;
    in >> *m_outputData;
    in >> *m_parameters ;
    in >> *m_toolInfo;
}
