#include "blToolStandardOutputViewer.h"
#include "../blWidgets/blHideableWidget.h"

blToolStandardOutputViewer::blToolStandardOutputViewer(QWidget *parent)
    :QWidget(parent){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    blHideableWidget *header = new blHideableWidget(tr("Execution Log"), 1, this);
    layout->addWidget(header);
    this->setLayout(layout);
    m_textEdit = new QTextEdit(this);
    m_textEdit->setMinimumHeight(150);
    header->addWidget(m_textEdit);
}

void blToolStandardOutputViewer::updateOutput(QString data){
    m_textEdit->append(data);
}

void blToolStandardOutputViewer::updateError(QString data){
    m_textEdit->append(data);
}
