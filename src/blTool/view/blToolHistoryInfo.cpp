#include "blToolHistoryInfo.h"

blToolHistoryInfo::blToolHistoryInfo()
{

}

QString blToolHistoryInfo::fileUrl(){
    return m_fileUrl;
}

QString blToolHistoryInfo::toolName(){
    return m_toolName;
}

QString blToolHistoryInfo::lastModified(){
    return m_lastModified;
}

int blToolHistoryInfo::id(){
    return m_id;
}

void blToolHistoryInfo::setFileUrl(QString fileUrl){
    m_fileUrl = fileUrl;
}

void blToolHistoryInfo::setToolName(QString toolName){
    m_toolName = toolName;
}

void blToolHistoryInfo::setLastModified(QString lastModified){
    m_lastModified = lastModified;
}

void blToolHistoryInfo::setId(int id){
    m_id = id;
}

