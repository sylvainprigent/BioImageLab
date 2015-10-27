#include "blToolExecGui.h"

#include "../blWidgets/blHideableWidget.h"
#include "blToolInputSelectorWidget.h"
#include "blToolParameterSelectorWidget.h"
#include "blToolRunWidget.h"

blToolExecGui::blToolExecGui(blToolInfo *toolInfo, QWidget *parent)
    : QWidget(parent){

    m_toolInfo = toolInfo;
    this->buildGui(toolInfo);
}

void blToolExecGui::buildGui(blToolInfo *toolInfo){

    // global Widget
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    QWidget* globalWidget = new QWidget(this);
    globalWidget->setLayout(layout);
    globalWidget->setObjectName("blToolExecGui");

    // global layout
    QVBoxLayout *globalLayout = new QVBoxLayout;
    globalLayout->setContentsMargins(0,0,0,0);
    globalLayout->setSpacing(0);
    this->setLayout(globalLayout);

    // title
    QWidget *titleWidget = new QWidget(this);
    QHBoxLayout * titleLayout = new QHBoxLayout;
    titleWidget->setLayout(titleLayout);
    QLabel *titlelabel = new QLabel("Tool", this);
    titlelabel->setObjectName("blToolExecGuiTitleLabel");
    titleLayout->addWidget(titlelabel);
    titleWidget->setFixedHeight(32);
    titleWidget->setObjectName("blToolExecGuiTitleWidget");
    globalLayout->addWidget(titleWidget);

    // scroll container
    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    globalLayout->addWidget(scroll);
    scroll->setWidget(globalWidget);

    // inputs gui
    blHideableWidget *inputsWidget = new blHideableWidget(tr("Inputs"), 1, this);
    m_inputSelectorWidget = new blToolInputSelectorWidget(toolInfo->getIO());
    inputsWidget->addWidget(m_inputSelectorWidget);
    layout->addWidget(inputsWidget, 0, Qt::AlignTop);

    // parameters gui
    blHideableWidget *parametersWidget = new blHideableWidget(tr("Parameters"), 1, this);
    m_parametersSelectorWidget = new blToolParameterSelectorWidget(toolInfo->parameters());
    parametersWidget->addWidget(m_parametersSelectorWidget);
    layout->addWidget(parametersWidget, 0, Qt::AlignTop);
    connect(m_parametersSelectorWidget, SIGNAL(help(QString)), this, SIGNAL(help(QString)));

    // run
    blHideableWidget *runWidgeth = new blHideableWidget(tr("Run"), 1, this);
    m_runWidget = new blToolRunWidget(this);
    runWidgeth->addWidget(m_runWidget);
    layout->addWidget(runWidgeth, 0, Qt::AlignTop);

    // exec log
    m_standardOutputViewer = new blToolStandardOutputViewer(this);
    m_standardOutputViewer->setVisible(false);
    layout->addWidget(m_standardOutputViewer, 1, Qt::AlignTop);

    // fill
    QWidget *fillWidget = new QWidget(this);
    fillWidget->setObjectName("blToolExecGuiFillWidget");
    layout->addWidget(fillWidget, 1, Qt::AlignTop);

    // hide parameters if there are no parameter
    if (toolInfo->parameters().count() < 1){
        parametersWidget->setVisible(false);
    }

    // connections
    connect(m_runWidget, SIGNAL(run()), this, SLOT(askRun()));
    connect(m_inputSelectorWidget, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
}

void blToolExecGui::askRun(){
    blioDataInfo* inputData = m_inputSelectorWidget->getData();
    blioParameters* parameters = m_parametersSelectorWidget->getData();

    m_runWidget->setRunning();
    emit run(m_toolInfo, inputData, parameters);
}

void blToolExecGui::processHasFinished(){
    m_runWidget->setRunFinished();
}

void blToolExecGui::setProgress(int progress){
    m_runWidget->setProgress(progress);
}

void blToolExecGui::updateError(QString data)
{
    m_standardOutputViewer->setVisible(true);
    m_standardOutputViewer->updateError(data);
}

void blToolExecGui::updateOutput(QString data)
{
    m_standardOutputViewer->setVisible(true);
    m_standardOutputViewer->updateOutput(data);
}
