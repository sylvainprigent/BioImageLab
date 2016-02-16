/// \file blProjectControler.cpp
/// \brief blProjectControler
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectControler.h"
#include "blWidgets/blImageView.h"
#include "blProject/model/blCreateMiniature.h"

blProjectControler::blProjectControler(blProjectModel *model, blProjectView *view, QString viewersDir, QString binariesDir){

    m_model = model;
    m_view = view;
    m_toolExecViewer = new blToolExecViewer(viewersDir);
    m_toolExecViewer->setBinariesDir(binariesDir);

    connect(view, SIGNAL(dataChanged(QString,QString,unsigned int,QString)), this, SLOT(columnUpdateDataModel(QString,QString,uint,QString)));
    connect(view, SIGNAL(askSave()), this, SLOT(saveProject()));
    connect(view, SIGNAL(askDeleteColumn(QString)), this, SLOT(deleteColumn(QString)));
    connect(view, SIGNAL(askComputeThumbnails(QString)), this, SLOT(calculateColumnThumbnails(QString)));

    connect(m_toolExecViewer, SIGNAL(error(QString)), this, SLOT(showViewerExecError(QString)));
    connect(view, SIGNAL(openData(QString,QString,QString)), m_toolExecViewer, SLOT(run(QString,QString,QString)));


    m_thumbnailThread = new blCreateMiniatureThread(this);
    connect(m_thumbnailThread, SIGNAL(thumbnailCreated(QString, unsigned int, unsigned int, QString)),
            this, SLOT(editThumbnail(QString, unsigned int, unsigned int, QString)));
}

void blProjectControler::showViewerExecError(QString message){
    QMessageBox::critical(m_view, tr("Viewer error"), message);
}

void blProjectControler::setProjectName(QString projectName){
    m_model->setProjectName(projectName);
}

QString blProjectControler::projectName(){
    return m_model->projectName();
}

// Load / save
void blProjectControler::saveProject(){

    qDebug() << "blProjectControler::saveProject()";
    if (m_projectURL.isEmpty()){
        qDebug() << "cannot save the project ";
    }
    else{
        saveProject(m_projectURL);
    }
}

void blProjectControler::loadProject(QString projectURL){
    // 1- load data to model
    m_projectURL = projectURL;
    m_model->setProjectUrl(projectURL);
    m_model->load();

    // 2- set it to the vue
    QMap<QString, blProjectModelMainColumn> mainColumnsModel = m_model->mainColumns();
    QMapIterator<QString, blProjectModelMainColumn> i(mainColumnsModel);
    while (i.hasNext()) {
        i.next();

        qDebug() << "Load main column = " << i.key();
        blProjectModelMainColumn mainColumn = i.value();
        // 2.1- create a view main column
        m_view->addColumnTable(i.key());

        // 2.2 - Create the parameter widget
        blProjectViewColumn* dataColumn = m_view->column(i.key());
        QString compoFile = projectURL + QDir::separator() + i.key() + QDir::separator() + "composition.bl";
        QFile fileCompo(compoFile);
        if (fileCompo.exists()){
            dataColumn->headerWidget()->setParamVisible(true);
            dataColumn->headerWidget()->setTrashVisible(true);
            QFileInfo infoFile(fileCompo);
            QString lastModified = infoFile.lastModified().toString("dd.MM.yyyy hh:mm:ss");
            dataColumn->headerWidget()->parameterEditor()->setDate(lastModified);
            dataColumn->headerWidget()->parameterEditor()->setCompoUrl(compoFile);
            connect(dataColumn->headerWidget()->parameterEditor(), SIGNAL(askOpenCompo(QString)), m_view, SIGNAL(askOpenCompo(QString)));
        }
        else{
            dataColumn->headerWidget()->setParamVisible(false);
            dataColumn->headerWidget()->setTrashVisible(false);
        }

        // 2.3- Fill the main column with columns

        QMapIterator<QString, blProjectModelColumn> ic(mainColumn.columns());
        unsigned int columnCount = -1;
        while (ic.hasNext()) {
            ic.next();
            columnCount++;
            dataColumn->addColumn(ic.key(), ic.value().dataType());
            QString dataType = ic.value().dataType();
            QMapIterator<unsigned int, QString> ir(ic.value().data());

            qDebug() << "dataType = " << dataType;
            if (dataType == blProjectModelColumn::STRING || dataType == blProjectModelColumn::NUMBER){
                while (ir.hasNext()){
                    ir.next();
                    dataColumn->addTableItem(ir.key(),columnCount, new QTableWidgetItem(ir.value()));
                }
            }
            else if (dataType == blProjectModelColumn::IMAGE_URL){
                while (ir.hasNext()){
                    ir.next();
                    // create a image

                    //blImageView* imageView = new blImageView(ir.value(), ir.value());
                    blImageView* imageView = new blImageView(blCreateMiniature::getMiniature(ir.value()), ir.value());

                    // set it to the table
                    dataColumn->addView(ir.key(), columnCount, imageView);
                    dataColumn->addTableItem(ir.key(),columnCount, new QTableWidgetItem());
                }
            }
        }
    }
}

void blProjectControler::saveProject(QString projectURL){
    // save the model into a file
    m_model->setProjectUrl(projectURL);
    m_model->save();
    m_projectURL = projectURL;
}

// create
void blProjectControler::createProject(QString projectURL){
    // create an empty model
    m_model->setProjectUrl(projectURL);
}

void blProjectControler::addMainColumn(QString name){
    // add main column to the model
    blProjectModelMainColumn column;
    m_model->addMainColumn(name, column);

    // update the view
    m_view->addColumnTable(name);
}

void blProjectControler::addColumn(QString mainColumnName, QString columnName, bool isMultiLine, QString dataType){

    // add column to model
    blProjectModelColumn data(isMultiLine,dataType);
    m_model->mainColumn(mainColumnName).addColumn(columnName, data);

    // update the view
    blProjectViewColumn* viewColumn = m_view->column(mainColumnName);
    viewColumn->addColumn(columnName, dataType);
}

// columns operations setters
void blProjectControler::columnAddData(QString mainColumnName, QString columnName, unsigned int lineId, QString data, bool useDataType){

    if (!useDataType){
        // add data to the model
        m_model->mainColumn(mainColumnName).column(columnName).addData(lineId, data);

        // add data to the view
        blProjectViewColumn* dataColumn = m_view->column(mainColumnName);
        int id = dataColumn->columnIdx(columnName);
        if (id == -1){
            qDebug() << "ERROR: the column does not exists !";
        }
        else{
            dataColumn->addTableItem(lineId,id, new QTableWidgetItem(data));
        }
    }
    else{
        // add data to the model
        m_model->mainColumn(mainColumnName).column(columnName).addData(lineId, data);
        QString dataType = m_model->mainColumn(mainColumnName).column(columnName).dataType();

        // add data to the view
        blProjectViewColumn* dataColumn = m_view->column(mainColumnName);
        int id = dataColumn->columnIdx(columnName);
        if (id == -1){
            qDebug() << "ERROR: the column does not exists !";
        }
        else{
            if (dataType == blProjectModelColumn::STRING || dataType == blProjectModelColumn::NUMBER){
                dataColumn->addTableItem(lineId,id, new QTableWidgetItem(data));
            }
            else if (dataType == blProjectModelColumn::IMAGE_URL){
                // create a image
                blImageView* imageView = new blImageView(blCreateMiniature::getMiniature(data), data);
                // set it to the table
                dataColumn->addView(lineId, id, imageView);
                dataColumn->addTableItem(lineId,id, new QTableWidgetItem());
            }
        }
    }
}

void blProjectControler::columnAddData(QString mainColumnName, QString columnName, unsigned int lineId, float data){
    columnAddData(mainColumnName, columnName, lineId, QString::number(data));
}

void blProjectControler::columnUpdateDataModel(QString mainColumnName, QString columnName, unsigned int lineId, QString data){
    // add data to the model
    m_model->mainColumn(mainColumnName).column(columnName).addData(lineId, data);
}

void blProjectControler::columnUpdateData(QString mainColumnName, QString columnName, unsigned int lineId, QString data, bool useDataType){
    qDebug() << "blProjectControler::columnUpdateData" ;
    columnAddData(mainColumnName, columnName, lineId, data, useDataType);
}

void blProjectControler::columnUpdateData(QString mainColumnName, QString columnName, unsigned int lineId, float data){
    columnAddData(mainColumnName, columnName, lineId, QString::number(data));
}

void blProjectControler::columnUpdateDataType(QString mainColumnName, QString columnName, QString dataType){
    m_model->mainColumn(mainColumnName).column(columnName).setDataType(dataType);
}

// getters
blProjectView* blProjectControler::view(){
    return m_view;
}

blProjectModel* blProjectControler::model(){
    return m_model;
}

void blProjectControler::addSingleImage(QString imagePath){

    //qDebug() << "blProjectControler::addSingleImage begin";
    // 1- Copy the image
    QFileInfo fileInfo(imagePath);
    QString filename(fileInfo.fileName());
    QString newPath = m_projectURL + QDir::separator() + "Data" + QDir::separator() + filename;

    if (!QFile::copy(imagePath, newPath)){
        //qDebug() << "Unage to copy image \n" + newPath +"\n from \n"+ imagePath;
        emit addDataError("Unage to copy image \n" + newPath +"\n from \n"+ imagePath);
        return;
    }

    //qDebug() << "blProjectControler::addSingleImage add the image to project";
    // 2- add the image to project
    unsigned int tablesize = m_model->mainColumn("Data").column("Images").data().size();
    columnAddData("Data", "Images", tablesize, newPath, true);

    //qDebug() << "blProjectControler::addSingleImage add an empty line";
    // 3- add an empty line for all the other columns
    addEmptyLineToNonDataColumns();
    emit dataAdded();
}

void blProjectControler::addEmptyLineToNonDataColumns(){
    QMapIterator<QString, blProjectModelMainColumn> mainColumns(m_model->mainColumns());
    while (mainColumns.hasNext()) {
        mainColumns.next();
        //qDebug() << "main column = " << mainColumns.key();
        if (mainColumns.key() != "Data"){
            // add an empty line to each column
            blProjectModelMainColumn col = mainColumns.value();
            QMapIterator<QString, blProjectModelColumn> columns(col.columns());
            while( columns.hasNext() ){
                columns.next();
                //qDebug() << "column = " << columns.key();
                unsigned int csize = columns.value().data().count();
                columnAddData(mainColumns.key(), columns.key(), csize, "");
            }
        }
    }
}

void blProjectControler::addProject(blProjectControler* controler){

    unsigned int initialRowNumber = this->model()->mainColumn("Data").column("Images").data().count() -1;

    // 1- Copy the data
    qDebug() << "blProjectControler::addProject -> Copy the data";
    blProjectModelColumn column = controler->model()->mainColumn("Data").column("Images");
    controler->columnUpdateDataType("Data", "Images", blProjectModelColumn::IMAGE_URL);
    QMap<unsigned int, QString> map = column.data();
    QMapIterator<unsigned int, QString> it(map);
    unsigned int idx = map.count()-1;
    while (it.hasNext()) {
        it.next();
        idx++;

        QString path = it.value();
        QFileInfo fileInfo(path);
        QString filename(fileInfo.fileName());

        QString newPath = m_projectURL + QDir::separator() + "Data" + QDir::separator() + filename;

        if (!QFile::copy(path, newPath)){
            emit addDataError("Unage to copy image \n" + newPath +"\n from \n"+ path);
            return;
        }

        this->columnAddData("Data", "Images", idx, newPath, true);
    }

    // 2 addEmptyLineToNonDataColumns
    //qDebug() << "blProjectControler::addProject -> addEmptyLineToNonDataColumns";
    addEmptyLineToNonDataColumns();

    // 2- Add the labels
    //qDebug() << "blProjectControler::addProject -> Add the labels";
    bool cHaveLabels = false;
    QMap<QString, blProjectModelMainColumn> mainMapC = controler->model()->mainColumns();
    QMapIterator<QString, blProjectModelMainColumn> mainMapCi(mainMapC);
    while (mainMapCi.hasNext()) {
        mainMapCi.next();
        if (mainMapCi.key() == "Labels"){
            cHaveLabels = true;
            break;
        }
    }

    bool tHaveLabels = false;
    QMap<QString, blProjectModelMainColumn> mainMapT = this->model()->mainColumns();
    QMapIterator<QString, blProjectModelMainColumn> mainMapTi(mainMapT);
    while (mainMapTi.hasNext()) {
        mainMapTi.next();
        if (mainMapTi.key() == "Labels"){
            tHaveLabels = true;
            break;
        }
    }

    if (cHaveLabels && tHaveLabels){
        QMap<QString, blProjectModelColumn> mapT = this->model()->mainColumn("Labels").columns();
        QMapIterator<QString, blProjectModelColumn> mapTi(mapT);

        while( mapTi.hasNext() ){
            mapTi.next();

            QMap<QString, blProjectModelColumn> mapC = controler->model()->mainColumn("Labels").columns();
            QMapIterator<QString, blProjectModelColumn> mapCi(mapC);
            while( mapCi.hasNext() ){
                mapCi.next();

                if (mapTi.key() == mapCi.key()){
                    QMap<unsigned int, QString> mapDataC = mapCi.value().data();
                    QMapIterator<unsigned int, QString> mapDataCi(mapDataC);

                    unsigned int idx = initialRowNumber;
                    while (mapDataCi.hasNext()){
                        mapDataCi.next();
                        idx++;

                        //qDebug() << "add data = " << "Labels , "<< mapCi.key() << ", " << idx << ", " << mapDataCi.value();
                        this->columnUpdateData("Labels", mapCi.key(), idx, mapDataCi.value());
                    }
                }
            }
        }
    }

    //qDebug() << "blProjectControler::addProject -> done";
    this->saveProject(m_projectURL);
    emit dataAdded();

}

void blProjectControler::deleteColumn(QString columnName){
    qDebug() << "blProjectControler:: deleteColumn model" ;
    m_model->removeMainColumn(columnName);
    qDebug() << "blProjectControler:: deleteColumn view" ;
    m_view->removeMainColumn(columnName);
    qDebug() << "blProjectControler:: deleteColumn save" ;
    this->saveProject();
}

void blProjectControler::calculateColumnThumbnails(QString columnName){
    blProjectModelMainColumn mainColumn = m_model->mainColumn(columnName);

    QMapIterator<QString, blProjectModelColumn> ic(mainColumn.columns());
    blProjectViewColumn* dataColumn = m_view->column(columnName);
    unsigned int columnCount = -1;
    while (ic.hasNext()) {
        ic.next();
        columnCount++;


        QString dataType = ic.value().dataType();

        if (dataType == blProjectModelColumn::IMAGE_URL){

            QStringList imagesNames;
            QList<unsigned int> rowIdxs;

            QMapIterator<unsigned int, QString> ir(ic.value().data());
            while (ir.hasNext()){
                ir.next();
                imagesNames.append(ir.value());
                rowIdxs.append(ir.key());
            }

            m_thumbnailThread->setData(imagesNames, rowIdxs, columnCount, columnName);
            m_thumbnailThread->start();
        }
    }
}

void blProjectControler::editThumbnail(QString mainColumnName, unsigned int row, unsigned int col, QString imgName){

    blImageView* imageView = new blImageView(blCreateMiniature::getMiniature(imgName), imgName);

    blProjectViewColumn* dataColumn = m_view->column(mainColumnName);

    dataColumn->addView(row, col, imageView);
    dataColumn->addTableItem(row,col, new QTableWidgetItem());
}

void blProjectControler::addRemoveSubColumn(QString mainColumnName, QString subColumnName,bool add){
    if (add){
        this->addColumn(mainColumnName, subColumnName, false, blProjectModelColumn::STRING);
    }
    else{
        m_model->removeSubColumn(mainColumnName, subColumnName);
        m_view->removeSubColumn(mainColumnName, subColumnName);
    }
    emit addRemoveSubColumnDone();
}
