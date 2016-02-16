#include "blToolInputSelectorWidget.h"

#include "blToolInputSelectorWidgetFile.h"
#include "blToolInputSelectorWidgetDir.h"
#include "blToolIOPluginInterface.h"

blToolInputSelectorWidget::blToolInputSelectorWidget(blToolIO toolIO,QWidget *parent)
    :QWidget(parent){

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);

    // add the file tab
    blToolInputSelectorWidgetFile *fileTab = new blToolInputSelectorWidgetFile(toolIO, this);
    connect(fileTab, SIGNAL(progressHasFinished(QString,QString)), this, SIGNAL(progressHasFinished(QString,QString)));
    m_tabWidget->addTab(fileTab, tr("File"));

    // add the directory tab
    blToolInputSelectorWidgetDir *dirTab = new blToolInputSelectorWidgetDir(toolIO, this);
    connect(dirTab, SIGNAL(progressHasFinished(QString,QString)), this, SIGNAL(progressHasFinished(QString,QString)));
    m_tabWidget->addTab(dirTab, tr("Directory"));

    // add the plugin tabs
    QDir pluginsDir = QDir(qApp->applicationDirPath());
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            blToolIOPluginInterface* pluginc = qobject_cast<blToolIOPluginInterface*>(plugin);
            if (pluginc){

                blToolInputSelectorWidgetInterface* plugW = pluginc->selectorWidget(toolIO, this);
                connect(plugW, SIGNAL(progressHasFinished(QString, QString)), this, SIGNAL(progressHasFinished(QString,QString)));
                connect(plugW, SIGNAL(changeOutputDir(QString)), this, SIGNAL(changeOutputDir(QString)));
                m_tabWidget->addTab(plugW, pluginc->name());
            }
        }
    }
}

blioDataInfo *blToolInputSelectorWidget::getData(){

    QWidget* w = m_tabWidget->currentWidget();
    blToolInputSelectorWidgetInterface* wt = qobject_cast<blToolInputSelectorWidgetInterface*>(w);
    if(wt != NULL){
        return wt->getData();
    }
    return new blioDataInfo();
}

void blToolInputSelectorWidget::saveOutputMetaData(int processId, QString outputDir, blioDataInfo* inputs, blioDataInfo* outputs,
                                                   blioParameters* params, blToolInfo* toolinfo){

    QWidget* w = m_tabWidget->currentWidget();
    blToolInputSelectorWidgetInterface* wt = qobject_cast<blToolInputSelectorWidgetInterface*>(w);
    if(wt != NULL){
        return wt->saveOutputMetaData(processId, outputDir, inputs, outputs, params, toolinfo);
    }
}

void blToolInputSelectorWidget::progressFinished(int processId, QString toolName){
    QWidget* w = m_tabWidget->currentWidget();
    blToolInputSelectorWidgetInterface* wt = qobject_cast<blToolInputSelectorWidgetInterface*>(w);
    if(wt != NULL){
      wt->progressFinished(processId, toolName);
    }
}

