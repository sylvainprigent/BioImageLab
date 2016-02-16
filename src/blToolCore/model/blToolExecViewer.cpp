#include "blToolExecViewer.h"

#include <QDebug>
#include <QDir>

#include "blToolExecLog.h"
#include "blToolParser.h"

blToolExecViewer::blToolExecViewer(QString viewersDirectory, QObject *parent)
    :QObject(parent){

    // parse all the viewers
    QFileInfo dirViewer(viewersDirectory);
    if (dirViewer.exists()){
        blToolParser parser;
        m_toolsInfo = parser.getToolsInfo(viewersDirectory);
    }
    m_process = new QProcess(this);
}

blToolExecViewer::~blToolExecViewer(){
    for(int i = m_toolsInfo.count()-1 ; i >= 0  ; --i){
        delete m_toolsInfo[i];
    }
}

void blToolExecViewer::run(QString dataType, QString url, QString description){

    //qDebug() << "m_toolsInfo count = " << m_toolsInfo.count();
    //qDebug() << "url = " << url;

    // 1- Find the viewer for the given dataType
    blToolInfo *toolInfo = NULL;
    QFileInfo fi(url);
    QString extension = fi.suffix();  // ext = "gz"
    for(int i = 0 ; i < m_toolsInfo.count() ; ++i){
        if ( m_toolsInfo.at(i)->datatype().contains(extension)){
            toolInfo = m_toolsInfo.at(i);
            break;
        }
    }

    // 2- Parse the viewer cmd
    if (toolInfo == NULL){
        emit error("Connot find any viewer for the datatype: " + dataType);
        return;
    }
    QString cmd = toolInfo->command();
    cmd.replace("$binaryDir", m_binariesDir);
    cmd.replace("$data", "\""+url+"\"");
    cmd.replace("$description", "\""+description+"\"");

#ifdef Q_OS_WIN32
  cmd = cmd.replace("/", "\\");
#endif

    qDebug() << "Viewer cmd : " << cmd;
    // 3- Exec the viewer
    if (!m_process->startDetached(cmd)){
        emit error("Cannot start the viewer with command line: " + cmd);
    }
}

void blToolExecViewer::setBinariesDir(QString dir){
    m_binariesDir = dir;
}
