#include "blToolHistoryBrowser.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>

blToolHistoryBrowser::blToolHistoryBrowser()
{

}

QList<blToolExecLog> blToolHistoryBrowser::getHistoryAll(){

    QList<blToolExecLog> history;
    QDirIterator it(m_historyDir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString fileName = it.next();
        if(fileName.startsWith("history_")){
            blToolExecLog fileData;
            fileData.load(m_historyDir + QDir::separator() + fileName);
            history.append(fileData);
        }
    }
    return history;
}

QList<blToolExecLog> blToolHistoryBrowser::getHistoryByTool(QString toolName){

    QList<blToolExecLog> history;
    QDirIterator it(m_historyDir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString fileName = it.next();
        if(fileName.startsWith("history_")){
            QStringList splitedName = fileName.split("_");
            if (splitedName.count() > 1){
                if (splitedName[1] == toolName){
                    blToolExecLog fileData;
                    fileData.load(m_historyDir + QDir::separator() + fileName);
                    history.append(fileData);
                }
            }
        }
    }
    return history;
}

QList<QStringList> blToolHistoryBrowser::getHistoryFileByTool(QString toolName){

    QList<QStringList> history;
    QDirIterator it(m_historyDir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString fileUrl = it.next();
        QFileInfo fileInfo(fileUrl);
        QString fileName = fileInfo.fileName();
        if(fileName.startsWith("history_")){
            QStringList splitedName = fileName.split("_");
            if (splitedName.count() > 1){
                if (splitedName[1] == toolName){
                    QStringList fileData;
                    fileData.append(m_historyDir + QDir::separator() + fileName);
                    fileData.append(toolName);
                    history.append(fileData);
                }
            }
        }
    }
    return history;
}

bool blToolHistoryBrowser::deleteHistory(QString fileUrl){

    // delete all the files inside the history
    blToolExecLog fileData;
    fileData.load(fileUrl);
    blioDataInfo *outputData = fileData.outputData();
    for(unsigned int i = 0 ; i < outputData->count() ; ++i){
        QStringList urls = outputData->at(i).inputUrls();
        for(int j = 0 ; j < urls.count() ; ++j){
            QFile fileToDelete(urls.at(j));
            if (fileToDelete.exists()){
                fileToDelete.remove();
            }
            else{
                //return false;
            }
        }
    }

    // delete the history file
    QFile fileToDelete(fileUrl);
    if (fileToDelete.exists()){
        fileToDelete.remove();
    }
    else{
        return false;
    }
    return true;
}

void blToolHistoryBrowser::setHistoryDir(QString dir){
    m_historyDir = dir;
}
