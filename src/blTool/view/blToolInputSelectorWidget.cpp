#include "blToolInputSelectorWidget.h"

#include "blToolInputWidget.h"

blToolInputSelectorWidget::blToolInputSelectorWidget(blToolIO toolIO,QWidget *parent)
    :QWidget(parent){

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);

    // add the file tab
    QWidget *fileTab = new QWidget(this);
    QGridLayout *fileLayout = new QGridLayout;
    fileLayout->setContentsMargins(0,0,0,0);
    fileTab->setLayout(fileLayout);
    for(unsigned int i = 0 ; i < toolIO.inputsCount() ; ++i){

        QLabel *title = new QLabel(toolIO.inputNameAt(i), this);
        blToolInputBrowser *browser = new blToolInputBrowser(this);
        browser->setDatatype(toolIO.inputTypeAt(i));
        browser->setKey(toolIO.inputNameAt(i));
        browser->setHelpButtonVisible(false);
        fileLayout->addWidget(title, i, 0);
        fileLayout->addWidget(browser, i, 1);
    }
    m_tabWidget->addTab(fileTab, tr("File"));

    // add the directory tab
    QWidget *dirTab = new QWidget(this);
    QGridLayout *dirLayout = new QGridLayout;
    dirLayout->setContentsMargins(0,0,0,0);
    dirTab->setLayout(dirLayout);
    for(unsigned int i = 0 ; i < toolIO.inputsCount() ; ++i){

        QLabel *title = new QLabel(toolIO.inputNameAt(i), this);
        blToolInputBrowser *browser = new blToolInputBrowser(this, true);
        browser->setDatatype(toolIO.inputTypeAt(i));
        browser->setKey(toolIO.inputNameAt(i));
        browser->setHelpButtonVisible(false);
        dirLayout->addWidget(title, i, 0);
        dirLayout->addWidget(browser, i, 1);
    }
    m_tabWidget->addTab(dirTab, tr("Directory"));
}

blioDataInfo *blToolInputSelectorWidget::getData(){

    blioDataInfo * io = new blioDataInfo;

    // get the files
    if (m_tabWidget->currentIndex() == 0){
        QLayout *layout = m_tabWidget->currentWidget()->layout();
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
    // get the files from directories
    else if(m_tabWidget->currentIndex() == 1){
        QLayout *layout = m_tabWidget->currentWidget()->layout();
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
            io->print();
            return io;
        }
        else{
            emit error(tr("There are no input widget !"));
            return io;
        }
        return io;
    }
    return io;
}
