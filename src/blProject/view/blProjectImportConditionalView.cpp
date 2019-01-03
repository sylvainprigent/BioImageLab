/// \file blProjectViewTab.cpp
/// \brief blProjectViewTab
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectImportConditionalView.h"

blProjectImportConditionalView::blProjectImportConditionalView(QWidget* parent) :
    QWidget(parent)
{

    m_twoSideWidget = new blTwoSideWidget;

    m_twoSideWidget->addLeftWidget(createTagsWidget());
    m_twoSideWidget->addLeftWidget(createImportWidget());
    m_twoSideWidget->addLeftWidget(new QWidget(this));

    //m_twoSideWidget->setFixedLeftWidth(900);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    QScrollArea *scrollCentral = new QScrollArea;
    scrollCentral->setWidgetResizable(true);
    scrollCentral->setWidget(m_twoSideWidget);
    totalLayout->addWidget(scrollCentral);
    this->setLayout(totalLayout);

    showTagsHelp();
}

QWidget* blProjectImportConditionalView::createTagsWidget(){

    QWidget *w = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    w->setLayout(layout);

    QLabel *tagTitle = new QLabel(tr("Conditions"), this);
    tagTitle->setObjectName("blLabelFormHeader1");
    layout->addWidget(tagTitle);

    QPushButton *helpButton = new QPushButton("?", this);
    helpButton->setObjectName("btnDefault");
    connect(helpButton, SIGNAL(released()), this, SLOT(showTagsHelp()));
    layout->addWidget(helpButton,0, Qt::AlignRight);
    helpButton->setMaximumWidth(32);

    QWidget *tagW = new QWidget(this);
    QHBoxLayout *tagLayout = new QHBoxLayout;
    tagLayout->setContentsMargins(0,0,0,0);
    tagW->setLayout(tagLayout);

    QLabel *tagLabel = new QLabel("Add a condition", this);
    tagLayout->addWidget(tagLabel, 0, Qt::AlignTop);

    m_tagSelector = new blTagManagerWidget(this);
    connect(m_tagSelector, SIGNAL(tagAdded()), this, SLOT(updateComboList()));
    tagLayout->addWidget(m_tagSelector, 0, Qt::AlignTop);

    layout->addWidget(tagW);

    w->setFixedWidth(400);
    return w;

}

QWidget* blProjectImportConditionalView::createImportWidget(){

    QWidget *w = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    w->setLayout(layout);

    QLabel *importTitle = new QLabel(tr("Import"), this);
    importTitle->setObjectName("blLabelFormHeader1");
    layout->addWidget(importTitle);


    QPushButton *helpButton = new QPushButton("?", this);
    helpButton->setObjectName("btnDefault");
    connect(helpButton, SIGNAL(released()), this, SLOT(showImportHelp()));
    layout->addWidget(helpButton,0, Qt::AlignRight);
    helpButton->setMaximumWidth(32);

    QWidget *importWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setContentsMargins(0,0,0,0);
    importWidget->setLayout(gridLayout);
    layout->addWidget(importWidget);

    QLabel *conditionLabel = new QLabel(tr("Condition"), this);
    m_conditionSelector = new QComboBox(this);
    gridLayout->addWidget(conditionLabel, 0, 0, 1, 1);
    gridLayout->addWidget(m_conditionSelector, 0, 1, 1, 1);

    QLabel *browse = new QLabel(tr("Browse"), this);
    QPushButton *browseButton = new QPushButton("...", this);
    browseButton->setObjectName("btnDefault");
    browseButton->setMaximumWidth(100);
    connect(browseButton, SIGNAL(released()), this, SLOT(browse()));
    gridLayout->addWidget(browse, 1, 0, 1, 1);
    gridLayout->addWidget(browseButton, 1, 1, 1, 2);

    QLabel *selectedFile = new QLabel(tr("Selected files"), this);
    m_tableWidget = new QTableWidget(this);
    m_tableWidget->horizontalHeader()->setVisible(false);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->setColumnCount(1);
    m_tableWidget->setRowCount(5);
    gridLayout->addWidget(selectedFile, 2, 0, 1, 1, Qt::AlignTop);
    gridLayout->addWidget(m_tableWidget, 2, 1, 1, 2);

    QPushButton *validateButton = new QPushButton(tr("Import"), this);
    connect(validateButton, SIGNAL(released()), this, SLOT(emitAskImport()));
    validateButton->setObjectName("btnPrimary");
    validateButton->setMaximumWidth(100);
    gridLayout->addWidget(validateButton, 3, 2, 1, 1);

    w->setFixedWidth(400);
    return w;
}

void blProjectImportConditionalView::browse(){
    m_files = QFileDialog::getOpenFileNames(this, tr("Select files"), QString(), "Data (*.*)");


    m_tableWidget->clear();
    m_tableWidget->setRowCount(m_files.count());
    for(int i = 0 ; i < m_files.count() ; i++){
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(m_files[i]));
    }
}

void blProjectImportConditionalView::updateComboList(){
    m_conditionSelector->clear();
    QList<blTagInfo> tagsInfo = m_tagSelector->getTagsInfo().all();
    for (int i = 0; i < tagsInfo.count(); ++i){
        m_conditionSelector->addItem(tagsInfo[i].name(), tagsInfo[i].id());
    }
}

void blProjectImportConditionalView::showTagsHelp(){
    QLabel *helpWidget = new QLabel("Type and add the conditions names");
    helpWidget->setMinimumHeight(150);
    m_twoSideWidget->setRightWidget(0,helpWidget,100);
}

void blProjectImportConditionalView::showImportHelp(){
    QLabel *helpWidget = new QLabel("For each condition, select the condition names, select corresponding images, and clic import");
    helpWidget->setMinimumHeight(150);
    m_twoSideWidget->setRightWidget(1,helpWidget,100);
}

void blProjectImportConditionalView::emitAskImport(){
    blImportDataInfo *importInfo = new blImportDataInfo;

    // data
    QList<blDataInfo> dataInfos;
    for (int i = 0 ; i < m_files.count() ; i++){
        // file
        blDataInfo dataInfo;
        dataInfo.setid(0);
        dataInfo.setline_id(i);
        dataInfo.seturl(m_files.at(i));
        dataInfo.setmain_col_name("Data");
        dataInfo.setid_sub_column_name("Images");
        dataInfos.append(dataInfo);

        // tag
        blDataInfo dataInfoTag;
        dataInfoTag.setid(0);
        dataInfoTag.setline_id(i);
        dataInfoTag.seturl(QString::number(qvariant_cast<int>(m_conditionSelector->currentData())));
        dataInfoTag.setmain_col_name("Data");
        dataInfoTag.setid_sub_column_name("Condition");
        dataInfos.append(dataInfoTag);

    }
    importInfo->setData(dataInfos);

    // main column
    blMainColumnInfo mainColumnInfo(0, "Data", "");
    importInfo->setMainColumnInfo(mainColumnInfo);

    // sub columns
    QList<blSubColumnInfo> subColumns;
    blSubColumnInfo sub1(0, "Images", 0, "image"); subColumns.append(sub1);
    blSubColumnInfo sub2(0, "Condition", 0, "tag"); subColumns.append(sub2);
    importInfo->setSubColumnsInfos(subColumns);

    // tags info
    blTagsInfo tagsInfo;
    QList<blTagInfo> tagsI = m_tagSelector->getTagsInfo().all();
    for (int i = 0 ; i < tagsI.count() ; i++){
        blTagInfo ta = tagsI[i];
        ta.setSubColName("Condition");
        tagsInfo.add(ta);
    }

    importInfo->setTags(tagsInfo);

    emit askImport(importInfo);
}

void blProjectImportConditionalView::load(blProjectModel* model){

    model->index()->viewTable("blp_tags");
    qDebug() << "blProjectImportConditionalView load ";
    QList<blTagInfo> tags = model->index()->tags();
    qDebug() << "import tag count = " << tags.count();

    m_tagSelector->setTags(tags);
    this->updateComboList();
}
