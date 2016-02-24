/// \file blProjectBrowserWidgetList.cpp
/// \brief blProjectBrowserWidgetList
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectBrowserWidgetList.h"

#include <blWidgets/blClickableIcon.h>
#include "blWidgets/blButtonId.h"
#include <QtWidgets>

blProjectBrowserWidgetList::blProjectBrowserWidgetList(QList<blProjectInfo *> &projects, QWidget *parent, bool useEmptyWidget) :
    QWidget(parent)
{
    m_projects = projects;
    createTable();

    emptyListWidget();
    m_emptyListWidget->setVisible(false);

    if (projects.isEmpty() && useEmptyWidget){

        QVBoxLayout *initLayout = new QVBoxLayout;
        m_table->setLayout(initLayout);
        initLayout->addWidget(m_emptyListWidget, 1, Qt::AlignCenter);
        m_emptyListWidget->setVisible(true);
    }
    else{
        setProjects(projects);
    }
    m_rowTodelete = -1;
}

// public slots
void blProjectBrowserWidgetList::setProjects(QList<blProjectInfo*> &projects){
    m_projects = projects;
    freeProjectTable();
    m_emptyListWidget->setVisible(false);
    addProjects(projects);
}

void blProjectBrowserWidgetList::addProjects(QList<blProjectInfo*> &projects){

    int idx;
    for (int i = 0 ; i < projects.size() ; ++i){
        if (m_table->rowCount() == 0){idx = 0;}
        else{idx = m_table->rowCount();}
        m_table->insertRow(idx);

        blButtonId *item1 = new blButtonId("", this);
        item1->setFixedSize(30,30);
        item1->setId(idx);
        connect(item1, SIGNAL(clicked(int)), this, SLOT(openProject(int)));
        item1->setObjectName("blProjectDatabaseButton");
        m_table->setCellWidget(idx, 0, item1);


        QTableWidgetItem *item2 = new QTableWidgetItem(projects[i]->name());
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        m_table->setItem(idx,1, item2 );

        QTableWidgetItem *item3 = new QTableWidgetItem(projects[i]->description());
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        m_table->setItem(idx,2, item3 );

        QTableWidgetItem *item4 = new QTableWidgetItem(projects[i]->typeId());
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        m_table->setItem(idx,3, item4 );

        QTableWidgetItem *item5 = new QTableWidgetItem(projects[i]->createdDate());
        item5->setFlags(item5->flags() ^ Qt::ItemIsEditable);
        m_table->setItem(idx,4, item5);

        QTableWidgetItem *item6 = new QTableWidgetItem(projects[i]->lastModifiedDate());
        item6->setFlags(item6->flags() ^ Qt::ItemIsEditable);
        m_table->setItem(idx,5, item6);

        blButtonId *item7 = new blButtonId("", this);
        item7->setId(idx);
        connect(item7, SIGNAL(clicked(int)), this, SLOT(deleteProject(int)));
        item7->setFixedSize(30,30);
        item7->setObjectName("blProjectTrashButton");
        m_table->setCellWidget(idx, 6, item7);
    }
}

// internal method
void blProjectBrowserWidgetList::createTable(){
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    m_table = new QTableWidget(0,7,this);
    m_table->verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setStretchLastSection(true);
    //m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    QStringList headerLabels;
    headerLabels.append("");
    headerLabels.append(tr("Name"));
    headerLabels.append(tr("Description"));
    headerLabels.append(tr("Type"));
    headerLabels.append(tr("Created in"));
    headerLabels.append(tr("Last modified"));
    headerLabels.append(tr(""));

    m_table->setHorizontalHeaderLabels(headerLabels);

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setIcon(*(new QIcon("theme/folder.png")));
    m_table->setHorizontalHeaderItem(0,item);
    m_table->setColumnWidth(0, 32);
    m_table->setColumnWidth(6, 32);

    connect(m_table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(emitCellDoubleClicked(int, int)));
    connect(m_table, SIGNAL(cellClicked(int,int)), this, SLOT(emitCellClicked(int, int)));

    layout->addWidget(m_table);
}

QWidget* blProjectBrowserWidgetList::emptyListWidget(){

    m_emptyListWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    m_emptyListWidget->setLayout(layout);


    QLabel *emptyWidget = new QLabel;
    emptyWidget->setText(QString("<i> You have not yet created any project. </i> <br> <i> ")+
                         QString(" click the icon below to create a new project</i>"));

    layout->addWidget(emptyWidget, 0, Qt::AlignHCenter |Qt::AlignBottom);

    //blClickableIcon *newProjectButton = new blClickableIcon("theme/newproject.png", tr("New"), 64,64,2);
    QPushButton* newProjectButton = new QPushButton(this);
    newProjectButton->setFixedSize(64,64);
    newProjectButton->setObjectName("blProjectNewProjectButton");
    connect(newProjectButton, SIGNAL(clicked()), this, SIGNAL(askNewProject()));
    layout->addWidget(newProjectButton, 0, Qt::AlignHCenter |Qt::AlignBottom);

    m_emptyListWidget->setFixedHeight(300);
    m_emptyListWidget->setFixedWidth(700);
    emptyWidget->setStyleSheet("QLabel{qproperty-alignment: AlignCenter;}");
    m_emptyListWidget->setStyleSheet(".QWidget{border: 1px dashed black;}");
    return m_emptyListWidget;
}

void blProjectBrowserWidgetList::emitCellDoubleClicked(int r, int){
    this->openProject(r);
}

void blProjectBrowserWidgetList::openProject(int r){
    if (r < m_projects.size()){
        emit askOpenProject(m_projects.at(r));
    }
}

void blProjectBrowserWidgetList::deleteProject(int r){
    if (r < m_projects.size()){
        int answer = QMessageBox::question(this, tr("Delete project"),
                                           "Do you want to remove the project " + m_projects.at(r)->name() + "?",
                                           QMessageBox ::Yes | QMessageBox::No);

        if (answer == QMessageBox::Yes){
            m_rowTodelete = r;
            emit askDeleteProject(m_projects.at(r));
        }
    }
}

void blProjectBrowserWidgetList::emitCellClicked(int r, int c){
    if (c == 4){
        this->deleteProject(r);
    }
}

void blProjectBrowserWidgetList::freeProjectTable(){
    while (m_table->rowCount() > 0)
    {
        m_table->removeRow(0);
    }
}

void blProjectBrowserWidgetList::rowDeletedFeedBack(bool success, QString message){
    if (success){
        blProjectInfo* info = m_projects.at(m_rowTodelete);
        m_projects.removeAt(m_rowTodelete);
        delete info;
        m_table->removeRow(m_rowTodelete);
    }
    else{
        QMessageBox::critical(this, tr("Delete project"), message);
    }
}
