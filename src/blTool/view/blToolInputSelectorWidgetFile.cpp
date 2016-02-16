#include "blToolInputSelectorWidgetFile.h"

#include "blToolInputWidget.h"

blToolInputSelectorWidgetFile::blToolInputSelectorWidgetFile(blToolIO toolIO,QWidget *parent)
    :blToolInputSelectorWidgetInterface(toolIO, parent){

    QGridLayout *fileLayout = new QGridLayout;
    fileLayout->setContentsMargins(0,0,0,0);
    this->setLayout(fileLayout);
    for(unsigned int i = 0 ; i < toolIO.inputsCount() ; ++i){

        QLabel *title = new QLabel(toolIO.inputNameAt(i), this);
        blToolInputBrowser *browser = new blToolInputBrowser(this);
        browser->setDatatype(toolIO.inputTypeAt(i));
        browser->setKey(toolIO.inputNameAt(i));
        browser->setHelpButtonVisible(false);
        fileLayout->addWidget(title, i, 0);
        fileLayout->addWidget(browser, i, 1);
    }
}

blioDataInfo * blToolInputSelectorWidgetFile::getData(){

    blioDataInfo * io = new blioDataInfo;

    QLayout *layout = this->layout();
    blioDataList dataList;
    for (int i = 0; i < layout->count(); ++i) {
        QWidget *w = layout->itemAt(i)->widget();
        blToolInputWidget* wt = qobject_cast<blToolInputWidget*>(w);
        if(wt != NULL){
            dataList.add(wt->datatype(), wt->key(), wt->value());
        }
    }
    io->add(dataList);
    return io;
}

void blToolInputSelectorWidgetFile::progressFinished(int processId, QString toolName){
    emit progressHasFinished(m_historyLogFile, toolName);
}
