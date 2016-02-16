/// \file blProjectViewTab.cpp
/// \brief blProjectViewTab
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectViewTab.h"
#include "blProjectLabelSplitter.h"

blProjectViewTab::blProjectViewTab(blProjectControler* controler, QWidget* parent) :
    blHoverableWidget(parent)
{
    m_controler = controler;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    createToolBar();
    layout->addWidget(m_toolBar);
    layout->addWidget(controler->view());
    this->setLayout(layout);

    m_addImageWidgetCreated = false;
    m_addRemoveSubColumnWidgetCreated = false;

    connect(m_controler, SIGNAL(dataAdded()), this, SLOT(hideHoverAddImagesWidget()));
    connect(m_controler, SIGNAL(addRemoveSubColumnDone()), this, SLOT(hideHoverAddRemoveSubColumnWidget()));
    connect(m_controler, SIGNAL(addDataError(QString)), this, SLOT(displayAddDataError(QString)));
    connect(m_controler->view(), SIGNAL(askAddRemoveColumns(QString)), this, SLOT(addRemoveColumns(QString)));
}

void blProjectViewTab::createToolBar(){

    m_toolBar = new QToolBar;

    // create actions
    QToolButton* saveAction = new QToolButton(this);
    saveAction->setObjectName("blProjectSaveButton");
    saveAction->setToolTip(tr("Save"));
    connect(saveAction, SIGNAL(released()), m_controler, SLOT(saveProject()));

    QToolButton* addImageAction = new QToolButton(this);
    addImageAction->setObjectName("blProjectAddImageButton");
    addImageAction->setToolTip(tr("Add image(s)"));
    connect(addImageAction, SIGNAL(released()), this, SLOT(addImages()));

    QToolButton* editLabelAction = new QToolButton(this);
    editLabelAction->setObjectName("blProjectEditLabelButton");
    editLabelAction->setToolTip(tr("Edit labels(s)"));
    connect(editLabelAction, SIGNAL(released()), this, SLOT(editLabels()));

    m_toolBar->addWidget(saveAction);
    m_toolBar->addWidget(addImageAction);
    m_toolBar->addWidget(editLabelAction);

    //m_toolBar->setStyleSheet("background-color: #f1f1f1; border: 0px solid #ffffff;");
}

void blProjectViewTab::createAddImagesWidget(){

    if (!m_addImageWidgetCreated){
        m_addImageWidget = new blProjectAddImageWidget("","");
        m_hoverWidgetAddImage = new blHoverWidget(this);
        m_hoverWidgetAddImage->addWidget(m_addImageWidget);
        connect(m_hoverWidgetAddImage, SIGNAL(askClose()), this, SLOT(hideHoverAddImagesWidget()));
        connect(m_addImageWidget, SIGNAL(cancel()), this, SLOT(hideHoverAddImagesWidget()));
        connect(m_addImageWidget, SIGNAL(askAddSingleImage(QString)), m_controler, SLOT(addSingleImage(QString)));
        connect(m_addImageWidget, SIGNAL(askAddProject(blProjectControler*)), this, SLOT(addProject(blProjectControler*)));
        m_addImageWidgetCreated = true;
    }
}

void blProjectViewTab::createSplitLabelsWidget(){

    if (!m_splitLabelsWidgetCreated){
        QStringList mainColumnsNames = m_controler->model()->mainColumnsName();
        m_splitLabelsWidget = new blProjectSplitLabelWidget(mainColumnsNames);
        connect(m_splitLabelsWidget, SIGNAL(askSubColumnNames(QString)), this, SLOT(splitLabelSubColumnsNames(QString)));
        if (mainColumnsNames.count() > 0){
            this->splitLabelSubColumnsNames(mainColumnsNames[0]);
        }
        m_hoverWidgetSplitLabel = new blHoverWidget(this);
        m_hoverWidgetSplitLabel->addWidget(m_splitLabelsWidget);
        connect(m_hoverWidgetSplitLabel, SIGNAL(askClose()), this, SLOT(hideHoverSplitLabelWidget()));
        connect(m_splitLabelsWidget, SIGNAL(cancel()), this, SLOT(hideHoverSplitLabelWidget()));
        connect(m_splitLabelsWidget, SIGNAL(askSplitLabels(QString, QString, QString, QString)), this, SLOT(splitLabels(QString, QString, QString, QString)));
        m_splitLabelsWidgetCreated = true;
    }
}

void blProjectViewTab::createAddRemoveSubColumnWidget(){

    if (!m_addRemoveSubColumnWidgetCreated){
        m_addRemoveSubColumnWidget = new blProjectAddRemoveSubColumnWidget(this);
        m_hoverWidgetAddRemoveSubColumn = new blHoverWidget(this);
        m_hoverWidgetAddRemoveSubColumn->addWidget(m_addRemoveSubColumnWidget);
        connect(m_hoverWidgetAddRemoveSubColumn, SIGNAL(askClose()), this, SLOT(hideHoverAddRemoveSubColumnWidget()));
        connect(m_addRemoveSubColumnWidget, SIGNAL(cancel()), this, SLOT(hideHoverAddRemoveSubColumnWidget()));
        connect(m_addRemoveSubColumnWidget, SIGNAL(askAddRemoveSubColumn(QString,QString,bool)), m_controler, SLOT(addRemoveSubColumn(QString,QString,bool)));
        m_addRemoveSubColumnWidgetCreated = true;
    }
}

void blProjectViewTab::splitLabels(QString colName, QString subColName, QString separator, QString newLabelsTiles){

    blProjectLabelSplitter splitter;
    splitter.setColumnName(colName);
    splitter.setSubColumnName(subColName);
    splitter.setSeparator(separator);
    splitter.setNewSubColumnsNames(newLabelsTiles);
    splitter.run(m_controler);
    this->hideHoverSplitLabelWidget();
}

void blProjectViewTab::splitLabelSubColumnsNames(QString mainColumnName){

    m_splitLabelsWidget->setSubColumnList(m_controler->model()->columnsName(mainColumnName));
}

void blProjectViewTab::addSelectorWidget(blProjectViewColumnSelector* selectorWidget){
    m_toolBar->addWidget(selectorWidget);
}

void blProjectViewTab::editLabels(){
    createSplitLabelsWidget();
    m_hoverWidgetSplitLabel->setVisible(true);
}

void blProjectViewTab::addImages(){
    createAddImagesWidget();
    m_hoverWidgetAddImage->setVisible(true);
}

void blProjectViewTab::addRemoveColumns(QString mainColumnName){
    createAddRemoveSubColumnWidget();
    m_addRemoveSubColumnWidget->setMainColumnName(mainColumnName);
    m_addRemoveSubColumnWidget->setSubColumnsNames(m_controler->model()->columnsName(mainColumnName));
    m_hoverWidgetAddRemoveSubColumn->setVisible(true);
}

void blProjectViewTab::hideHoverAddImagesWidget(){
    m_hoverWidgetAddImage->setVisible(false);
}

void blProjectViewTab::hideHoverSplitLabelWidget(){
    m_hoverWidgetSplitLabel->setVisible(false);
}

void blProjectViewTab::hideHoverAddRemoveSubColumnWidget(){
    m_hoverWidgetAddRemoveSubColumn->setVisible(false);
}

void blProjectViewTab::displayAddDataError(QString message){
    QMessageBox::critical(this, tr("Add data error"), message);
}

void blProjectViewTab::addProject(blProjectControler* controler){
    m_controler->addProject(controler);
}

void blProjectViewTab::saveMessageBox(){

    int answer = QMessageBox::question(this, tr("Close project"), tr("Save changes before closing ?"), QMessageBox ::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes){
        m_controler->saveProject();
    }

    emit askCloseProject();
    emit askCloseProject(m_controler->projectName());
}
