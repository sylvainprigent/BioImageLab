/// \file blProjectNewFormWidget.cpp
/// \brief blProjectNewFormWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectNewFormWidget.h"

#include "blWidgets/blClickableIcon.h"
#include "blProject/model/blProjectFolderFilter.h"
#include "blProject/model/blProjectFolderLabelExtractor.h"

blProjectNewFormWidget::blProjectNewFormWidget(QString viewerDir, QString binariesDir, QWidget *parent, bool useDescription)
    : QWidget(parent)
{
    m_viewerDir = viewerDir;
    m_binariesDir = binariesDir;
    m_useDescription = useDescription;
    twoSideWidget = new blTwoSideWidget;

    if (m_useDescription){
        // 1- description widget
        QWidget *descriptionWidget = new QWidget;
        QHBoxLayout *descriptionLayout = new QHBoxLayout;
        descriptionWidget->setLayout(descriptionLayout);
        QPushButton *descriptionHelp = new QPushButton();
        descriptionHelp->setObjectName("blProjectHelpButton");
        descriptionHelp->setFixedSize(32,32);
        m_description = new blProjectNewFormWidgetDescription();
        descriptionLayout->addWidget(m_description);
        descriptionLayout->addWidget(descriptionHelp, 0, Qt::AlignTop);
        twoSideWidget->addLeftWidget(descriptionWidget);
        descriptionWidget->setFixedWidth(700);
        connect(descriptionHelp, SIGNAL(clicked()), this, SLOT(showDescriptionHelp()));
        connect(m_description, SIGNAL(askCreateEmptyProject()), this, SLOT(emptyProjectClicked()));
    }

    // 2- import folder
    QWidget *importFolderWidget = new QWidget;
    QHBoxLayout *importFolderLayout = new QHBoxLayout;
    importFolderWidget->setLayout(importFolderLayout);
    QPushButton *importFolderHelp = new QPushButton();
    importFolderHelp->setObjectName("blProjectHelpButton");
    importFolderHelp->setFixedSize(32,32);
    m_importFolder = new blProjectNewFormWidgetImport;
    importFolderLayout->addWidget(m_importFolder);
    importFolderLayout->addWidget(importFolderHelp, 0, Qt::AlignTop);
    twoSideWidget->addLeftWidget(importFolderWidget);
    importFolderWidget->setFixedWidth(700);
    connect(importFolderHelp, SIGNAL(clicked()), this, SLOT(showImportFolderHelp()));

    // 2.1- Filters
    QWidget *filterWidget = new QWidget;
    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterWidget->setLayout(filterLayout);
    QPushButton *filterHelp = new QPushButton();
    filterHelp->setObjectName("blProjectHelpButton");
    filterHelp->setFixedSize(32,32);
    m_filter = new blProjectNewFormWidgetFilter;
    filterLayout->addWidget(m_filter);
    filterLayout->addWidget(filterHelp, 0, Qt::AlignTop);
    twoSideWidget->addLeftWidget(filterWidget);
    filterWidget->setFixedWidth(700);
    connect(filterHelp, SIGNAL(clicked()), this, SLOT(showFilterHelp()));
    connect(m_filter, SIGNAL(askViewFiltering()), this, SLOT(showFilteringView()));

    // 2.2- labels
    QWidget *labelingWidget = new QWidget;
    QHBoxLayout *labelingLayout = new QHBoxLayout;
    labelingWidget->setLayout(labelingLayout);
    QPushButton *labelingHelp = new QPushButton();
    labelingHelp->setObjectName("blProjectHelpButton");
    labelingHelp->setFixedSize(32,32);
    m_labeling = new blProjectNewFormWidgetLabel;
    labelingLayout->addWidget(m_labeling);
    labelingLayout->addWidget(labelingHelp, 0, Qt::AlignTop);
    twoSideWidget->addLeftWidget(labelingWidget);
    labelingWidget->setFixedWidth(700);
    connect(labelingHelp, SIGNAL(clicked()), this, SLOT(showLabelingHelp()));
    connect(m_labeling, SIGNAL(askView()), this, SLOT(showLabelView()));

    // 3- Validate
    QWidget *validateWidget = new QWidget;
    QHBoxLayout *validateLayout = new QHBoxLayout;
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setObjectName("btnDefault");
    QPushButton *validateButton = new QPushButton(tr("Validate"));
    validateButton->setObjectName("btnPrimary");
    validateLayout->addWidget(cancelButton, 1, Qt::AlignRight);
    validateLayout->addWidget(validateButton, 0, Qt::AlignRight);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(validateButton, SIGNAL(clicked()), this, SLOT(validateClicked()));
    validateWidget->setLayout(validateLayout);
    twoSideWidget->addLeftWidget(validateWidget);
    validateWidget->setFixedWidth(700);


    twoSideWidget->setFixedLeftWidth(700);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    QScrollArea *scrollCentral = new QScrollArea;
    scrollCentral->setWidgetResizable(true);
    scrollCentral->setWidget(twoSideWidget);
    totalLayout->addWidget(scrollCentral);
    this->setLayout(totalLayout);

}

blProjectNewFormWidget::~blProjectNewFormWidget()
{

}

// slots
void blProjectNewFormWidget::showDescriptionHelp(){

    QLabel *helpWidget = new QLabel("this is the description help");
    helpWidget->setMinimumHeight(100);
    twoSideWidget->setRightWidget(0,helpWidget,10);
}

void blProjectNewFormWidget::showImportFolderHelp(){
    QLabel *helpWidget = new QLabel("this is the import folder help");
    helpWidget->setMinimumHeight(100);

    int pos;
    if (m_useDescription){pos = 1;}
    else{pos=0;}
    twoSideWidget->setRightWidget(pos,helpWidget,10);
}

void blProjectNewFormWidget::showFilterHelp(){
    QLabel *helpWidget = new QLabel("this is the filter help");
    helpWidget->setMinimumHeight(400);
    int pos;
    if (m_useDescription){pos = 2;}
    else{pos=1;}
    twoSideWidget->setRightWidget(pos,helpWidget,10);
}

void blProjectNewFormWidget::showLabelingHelp(){
    QLabel *helpWidget = new QLabel("this is the labeling help");
    helpWidget->setMinimumHeight(400);
    int pos;
    if (m_useDescription){pos = 3;}
    else{pos=2;}
    twoSideWidget->setRightWidget(pos,helpWidget,10);
}

void blProjectNewFormWidget::showFilteringView(bool show){

    // 1- get the folder info
    QString folderPath = m_importFolder->getPath();
    bool isRecursive = m_importFolder->isRecursive();

    // 2- get the filters info
    QList<QStringList> filtersInfos = m_filter->getFiltersInfo();

    // 3- run Filter
    blProjectFolderFilter filter(folderPath,isRecursive, filtersInfos);
    m_imagesPaths = filter.run();

    // 4- view list
    if (show){
        blProjectControler *tableControler = createDataTable();
        blProjectView *table = tableControler->view();
        table->setMinimumHeight(500);

        int pos;
        if (m_useDescription){pos = 2;}
        else{pos=1;}
        twoSideWidget->setRightWidget(pos,table,10);
    }
}

blProjectControler *blProjectNewFormWidget::createDataTable(){

    blProjectModel *model = new blProjectModel;
    blProjectView *view = new blProjectView;
    blProjectControler * controler = new blProjectControler(model, view, m_viewerDir, m_binariesDir);

    //controler->view()->setToolBarVisible(false);
    controler->addMainColumn("Data");
    controler->addColumn("Data", "Images", true, blProjectModelColumn::STRING);
    for (int i = 0 ; i < m_imagesPaths.size() ; ++i){
        controler->columnAddData("Data", "Images", i, m_imagesPaths[i]);
    }
    return controler;
}

blProjectControler *blProjectNewFormWidget::createLabelTable(){

    // 1- get the images paths
    if (m_imagesPaths.isEmpty()){
        showFilteringView(false);
    }

    // 2- get label regExp
    QStringList filters = m_labeling->filtersList();

    // 3- create table
    blProjectControler *controler = createDataTable();
    controler->addMainColumn("Labels");

    // 3- apply selection
    blProjectFolderLabelExtractor filter(m_imagesPaths, m_importFolder->getPath());

    for (int f = 0 ; f < filters.count() ; ++f){
        // 3.2- apply filter
        //qDebug() << "apply filter" << f;
        QList<QStringList> labels = filter.run(filters[f]);
        //qDebug() << "apply filter done size" << labels.size();

        // 3.3- fill table column
        if (labels.size() > 0){
            // 3.3.1- Create columns
            for (int i = 0 ; i < labels[0].count() ; ++i){
                controler->addColumn("Labels", "label " + filters[f] + " "+ QString::number(i), true, "string");

                // 3.3.2- fill columns
                for (int j = 0 ; j < labels.count() ; ++j){
                    controler->columnAddData("Labels", "label " + filters[f] + " "+ QString::number(i), j, labels[j][i]);
                }
            }
        }
    }
    return controler;
}

void blProjectNewFormWidget::showLabelView(){

    blProjectControler * tableControler = createLabelTable();

    // 4- add view list
    blProjectView* table = tableControler->view();
    table->setMinimumHeight(500);

    int pos;
    if (m_useDescription){pos = 3;}
    else{pos=2;}
    twoSideWidget->setRightWidget(pos,table,100);
}

void blProjectNewFormWidget::validateClicked(){

    blProjectControler * controler = createLabelTable();
    if (m_useDescription){
        controler->setProjectName(m_description->getName());
    }
    emit askCreateProject(controler, this);
    emit askCreateProject(controler);
}

void blProjectNewFormWidget::emptyProjectClicked(){
    emit askEmptyProject(this);
}

void blProjectNewFormWidget::cancelClicked(){
    emit askCancel(this);
    emit askCancel();
}

QString blProjectNewFormWidget::name(){
    return m_description->getName();
}

QString blProjectNewFormWidget::objective(){
    return m_description->getDescription();
}
