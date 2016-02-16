#include "blToolInputSelectorWidgetDir.h"

#include "blToolInputWidget.h"

blToolInputSelectorWidgetDir::blToolInputSelectorWidgetDir(blToolIO toolIO,QWidget *parent)
    :blToolInputSelectorWidgetInterface(toolIO, parent){

    QGridLayout *dirLayout = new QGridLayout;
    dirLayout->setContentsMargins(0,0,0,0);
    this->setLayout(dirLayout);
    for(unsigned int i = 0 ; i < toolIO.inputsCount() ; ++i){

        QLabel *title = new QLabel(toolIO.inputNameAt(i), this);
        blToolInputBrowser *browser = new blToolInputBrowser(this, true);
        browser->setDatatype(toolIO.inputTypeAt(i));
        browser->setKey(toolIO.inputNameAt(i));
        browser->setHelpButtonVisible(false);
        dirLayout->addWidget(title, i, 0);
        dirLayout->addWidget(browser, i, 1);
    }
}

blioDataInfo *blToolInputSelectorWidgetDir::getData(){
    blioDataInfo * io = new blioDataInfo;

    QLayout *layout = this->layout();
    // 1- get the list of the directories
    QStringList dataTypes;
    QStringList keys;
    QStringList values;
    for (int i = 0; i < layout->count(); ++i) {
        QWidget *w = layout->itemAt(i)->widget();
        blToolInputWidget* wt = qobject_cast<blToolInputWidget*>(w);
        if(wt != NULL){
            dataTypes.append(wt->datatype());
            keys.append(wt->key());
            values.append(wt->value());
        }
    }

    if (values.count() > 0){
        // Check that all the directories have the same number of files
        QList<int> filesNum;
        QList<QFileInfoList> fLists;
        for (int i = 0 ; i < values.count() ; i++){
            QDir directory = QDir(values[i]);
            QFileInfoList fList = directory.entryInfoList(QDir::Files, QDir::Name);
            fLists.append(fList);
            filesNum.append(fList.count());
        }
        int num = filesNum[0];
        for (int i = 1 ; i < values.count() ; i++){
            if (filesNum[i] != num){
                emit error(tr("The input folders does not have the same number of files !"));
                return io;
            }
        }
        // add ios
        for(int f = 0 ; f < num ; ++f ){
            blioDataList dataList;
            for (int i = 0 ; i < values.count() ; i++){
                dataList.add(dataTypes[i], keys[i], fLists[i].at(f).absoluteFilePath());
            }
            io->add(dataList);
        }
        //io->print();
        return io;
    }
    else{
        emit error(tr("There are no input widget !"));
        return io;
    }
    return io;
}

void blToolInputSelectorWidgetDir::progressFinished(int processId, QString toolName){
    emit progressHasFinished(m_historyLogFile, toolName);
}
