#include "blProjectController.h"
#include "../model/blProjectAccess.h"

blProjectController::blProjectController(QWidget *parent) :QWidget(parent)
{

    // initialize from database
    loadInformationFromDatabase();

    // build gui
    this->setStyleSheet(".QWidget{background-color: #ffffff;}");
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    layout->addWidget(this->createToolBar());
    layout->addWidget(this->createCentralArea());
}

void blProjectController::loadInformationFromDatabase(){
    m_availableprojectTypes.add(blProjectType(1, "single conditional data"));
}

QWidget* blProjectController::createToolBar(){

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    //layout->setContentsMargins(0,0,0,0);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);

    layout->addWidget(new QWidget(this), 1);
    // informations
    m_infoButton = new QPushButton(tr("Informations"));
    m_infoButton->setCheckable(true);
    connect(m_infoButton, SIGNAL(clicked()), this, SLOT(showInfo()));
    m_infoButton->setObjectName("btnDefaultLeft");
    layout->addWidget(m_infoButton);

    // import
    m_importButton = new QPushButton(tr("Import"));
    m_importButton->setCheckable(true);
    connect(m_importButton, SIGNAL(clicked()), this, SLOT(showImport()));
    m_importButton->setObjectName("btnDefaultCentral");
    layout->addWidget(m_importButton);

    // Data
    m_dataButton = new QPushButton(tr("Data"));
    m_dataButton->setCheckable(true);
    connect(m_dataButton, SIGNAL(clicked()), this, SLOT(showData()));
    m_dataButton->setObjectName("btnDefaultCentral");
    layout->addWidget(m_dataButton);

    // process
    m_processButton = new QPushButton(tr("Process"));
    m_processButton->setCheckable(true);
    connect(m_processButton, SIGNAL(clicked()), this, SLOT(showProcess()));
    m_processButton->setObjectName("btnDefaultCentral");
    layout->addWidget(m_processButton);

    // export
    m_exportButton = new QPushButton(tr("Export"));
    m_exportButton->setCheckable(true);
    connect(m_exportButton, SIGNAL(clicked()), this, SLOT(showExport()));
    m_exportButton->setObjectName("btnDefaultRight");
    layout->addWidget(m_exportButton);

    layout->addWidget(new QWidget(this), 1);

    return widget;
}

QWidget * blProjectController::createCentralArea(){

    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);

    // project info
    // view
    m_informationForm = new blProjectInfoForm(m_availableprojectTypes, this);
    m_informationForm->editView();
    connect(m_informationForm, SIGNAL(askEditProject(blProjectInfo*)), this, SLOT(editProjectInfo(blProjectInfo*)));
    layout->addWidget(m_informationForm);
    // model
    m_projectModel = new blProjectModel();

    // data import
    // view
    m_importForm = new blProjectImportConditionalView(this);
    m_importForm->setVisible(false);
    connect(m_importForm, SIGNAL(askImport(blImportDataInfo*)), this, SLOT(importData(blImportDataInfo*)));
    layout->addWidget(m_importForm);

    // data view
    m_dataView = new blProjectDataView(this);
    m_dataView->setVisible(false);
    layout->addWidget(m_dataView);

    return widget;
}

// openProject
void blProjectController::openProject(blProjectInfo *info){

    qDebug() << "---------------- oprn project URL = " << info->url();
    info->print();
    // initialize model
    m_projectModel->setProjectInfo(info);

    // set info form
    m_informationForm->setData(info);
    if (info->id() > 0){
        this->enableToolBarButtons(true);
    }
    else{
        this->enableToolBarButtons(false);
    }

    // set import widget
    m_importForm->load(m_projectModel);
    m_dataView->load(m_projectModel);

}

void blProjectController::enableToolBarButtons(bool enabled){

    m_importButton->setEnabled(enabled);
    m_dataButton->setEnabled(enabled);
    m_processButton->setEnabled(enabled);
    m_exportButton->setEnabled(enabled);
}

// view slots
void blProjectController::showInfo(){
    m_infoButton->setChecked(true);
    m_importButton->setChecked(false);
    m_dataButton->setChecked(false);
    m_processButton->setChecked(false);
    m_exportButton->setChecked(false);

    m_informationForm->setVisible(true);
    m_importForm->setVisible(false);
    m_dataView->setVisible(false);
}
void blProjectController::showImport(){
    m_infoButton->setChecked(false);
    m_importButton->setChecked(true);
    m_dataButton->setChecked(false);
    m_processButton->setChecked(false);
    m_exportButton->setChecked(false);

    m_informationForm->setVisible(false);
    m_importForm->setVisible(true);
    m_dataView->setVisible(false);
}

void blProjectController::showData(){
    m_infoButton->setChecked(false);
    m_importButton->setChecked(false);
    m_dataButton->setChecked(true);
    m_processButton->setChecked(false);
    m_exportButton->setChecked(false);

    m_informationForm->setVisible(false);
    m_importForm->setVisible(false);
    m_dataView->setVisible(true);
}

void blProjectController::showProcess(){

}

void blProjectController::showExport(){

}

// model slots
void blProjectController::editProjectInfo(blProjectInfo* info){

    m_projectInfo = info;
    int idBeforeEdit = info->id();

    QString message = m_projectModel->createProject(info);

    if (message != "success"){
        QMessageBox::critical(this, tr("Error"), message);
    }

    if (idBeforeEdit == 0 && message == "success"){
        this->showImport();
    }
}

void blProjectController::importData(blImportDataInfo *importDataInfo){
    m_projectModel->importData(m_projectInfo, importDataInfo);
    m_projectModel->setProjectInfo(m_projectInfo);
    m_dataView->fillTable(m_projectModel);
    this->showData();
}
