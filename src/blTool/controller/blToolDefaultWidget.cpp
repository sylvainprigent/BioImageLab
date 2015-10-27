#include "blToolDefaultWidget.h"
#include "../view/blToolHistoryWidget.h"

blToolDefaultWidget::blToolDefaultWidget(blToolInfo* toolInfo, QString historyUrl, QString viewersDir, QWidget *parent) : QWidget(parent)
{
    m_toolInfo = toolInfo;
    m_historyDir = historyUrl;
    m_viewersDir = viewersDir;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(this->createExecArea());
    splitter->addWidget(this->createCentralArea());
    splitter->addWidget(this->createHistoryArea());

    layout->addWidget(splitter);
    this->setLayout(layout);

    // connections
    connect(m_execWidget, SIGNAL(run(blToolInfo*,blioDataInfo*,blioParameters*)),
            m_toolExec, SLOT(run(blToolInfo*,blioDataInfo*,blioParameters*)));
    connect(m_toolExec, SIGNAL(processHasFinished()),
            m_execWidget, SLOT(processHasFinished()));
    connect(m_execWidget, SIGNAL(help(QString)), m_docWidget, SLOT(loadPage(QString)));
    connect(m_toolExec, SIGNAL(progress(int)), m_execWidget, SLOT(setProgress(int)));
    connect(m_toolExec, SIGNAL(processHasFinished(QString, QString)), m_historyBar, SLOT(addHistory(QString, QString)));
    connect(m_toolExec, SIGNAL(processVerbose(QString)), m_execWidget, SLOT(updateOutput(QString)));
    connect(m_toolExec, SIGNAL(processError(QString)), m_execWidget, SLOT(updateError(QString)));
    connect(m_historyBar, SIGNAL(deleteHistory(QString)), m_history, SLOT(deleteHistory(QString)));
    connect(m_historyBar, SIGNAL(deleteHistory(int)), m_historyBar, SLOT(removeHistory(int)));
    connect(m_historyBar, SIGNAL(openHistory(QString)), this, SLOT(openHistory(QString)));
}

QWidget* blToolDefaultWidget::createExecArea(){

    // model
    m_toolExec = new blToolExec();
    m_toolExec->setOutputDir(m_historyDir);

    // view
    m_execWidget = new blToolExecGui(m_toolInfo);
    m_docWidget = new blToolDocWidget(this);
    m_docWidget->loadPage(m_toolInfo->doc());

    return m_execWidget;
}

QWidget* blToolDefaultWidget::createCentralArea(){
    m_centralWidget = new QTabWidget(this);
    m_centralWidget->setTabsClosable(true);
    connect(m_centralWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));

    // add the doc widget
    m_centralWidget->addTab(m_docWidget, tr("Help"));
    QTabBar *tabBar = m_centralWidget->findChild<QTabBar *>();
    tabBar->tabButton(0, QTabBar::RightSide)->resize(0, 0);

    return m_centralWidget;
}

QWidget* blToolDefaultWidget::createHistoryArea(){

    // instanciate model and view
    m_history = new blToolHistoryBrowser;
    m_history->setHistoryDir(m_historyDir);
    m_historyBar = new blToolHistoryBar(this);

    // initialize the history list
    QList<QStringList> tools = m_history->getHistoryFileByTool(m_toolInfo->name());
    for (int i = 0 ; i < tools.count() ; ++i){
        m_historyBar->addHistory(tools[i][0], tools[i][1]);
    }

    // initialize the tool viewer exec model
    m_toolExecViewer = new blToolExecViewer(m_viewersDir);
    connect(m_toolExecViewer, SIGNAL(error(QString)), this, SLOT(showViewerExecError(QString)));

    return m_historyBar;
}

void blToolDefaultWidget::openHistory(QString historyFile){

    blToolHistoryWidget* widget = new blToolHistoryWidget(historyFile);
    connect(widget, SIGNAL(openData(QString,QString,QString)), m_toolExecViewer, SLOT(run(QString,QString,QString)));
    m_centralWidget->addTab(widget, tr("History"));
    m_centralWidget->setCurrentWidget(widget);

}

void blToolDefaultWidget::closeTab(int index){
    QWidget* widget = m_centralWidget->widget(index);

    widget->deleteLater();
    m_centralWidget->removeTab(index);
}

void blToolDefaultWidget::showViewerExecError(QString message){
    QMessageBox::critical(this, tr("Viewer error"), message);
}
