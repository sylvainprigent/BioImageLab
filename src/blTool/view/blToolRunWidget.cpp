#include "blToolRunWidget.h"

blToolRunWidget::blToolRunWidget(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;

    m_runButton = new QPushButton(tr("Execute"), this);
    m_runButton->setObjectName("btnPrimary");
    m_progressBar = new QProgressBar(this);

    layout->addWidget(m_runButton, 0, Qt::AlignLeft);
    layout->addWidget(m_progressBar);

    this->setLayout(layout);

    m_progressBar->setRange(0, 0);
    m_progressBar->setVisible(false);
    connect(m_runButton, SIGNAL(pressed()), this, SIGNAL(run()));
}

void blToolRunWidget::setProgressRange(int minValue, int maxValue){
    m_progressBar->setRange(minValue, maxValue);
}

void blToolRunWidget::setProgress(int value){
    if (value == 100){
        m_progressBar->setVisible(false);
    }
    else{
        m_progressBar->setRange(0, 100);
        m_progressBar->setVisible(true);
        m_progressBar->setValue(value);
    }
}

void blToolRunWidget::setRunning(){
    m_progressBar->setVisible(true);
    m_runButton->setEnabled(false);
}

void blToolRunWidget::setRunFinished(){
    m_progressBar->setVisible(false);
    m_runButton->setEnabled(true);
}
