/// \file blProjectWidget.cpp
/// \brief blProjectWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectWidget.h"
#include "blProject/view/blProjectNewFormWidget.h"
#include "blProject/model/blProjectAccess.h"
#include "blProject/view/blProjectControler.h"
#include "blProject/view/blProjectViewTab.h"

#include <blCore/blException.h>
#include <blCore/blDir.h>

#include <QVBoxLayout>

blProjectWidget::blProjectWidget(QString viewerDir, QString binariesDir, QWidget *parent)
    : QWidget(parent)
{
    m_viewerDir = viewerDir;
    m_binariesDir = binariesDir;
    createTab();

    connect(m_projectBrowserWidget, SIGNAL(askNewProject()), this, SLOT(openNewProjectForm()));
    connect(m_tab,SIGNAL(tabCloseRequested(int)),this,SLOT(removeProcessingTab(int)));
}

blProjectWidget::~blProjectWidget()
{
    
}

void blProjectWidget::setProjectsRootPath(QString projectsRootPath){
    m_projectsRootPath = projectsRootPath;
}


// public slots
void blProjectWidget::openProject(blProjectInfo* info){
    blProjectModel *model = new blProjectModel;
    blProjectView *view = new blProjectView;
    blProjectControler* controler = new blProjectControler(model, view, m_viewerDir, m_binariesDir);
    controler->loadProject(info->url());

    openProject(controler);
}

void blProjectWidget::openNewProjectForm(){

    blProjectNewFormWidget *newProjectForm = new blProjectNewFormWidget(m_viewerDir, m_binariesDir, this);
    m_tab->addTab(newProjectForm, tr("New Project"));
    m_tab->setCurrentWidget(newProjectForm);

    connect(newProjectForm, SIGNAL(askCancel()), this, SLOT(deleteCurentTab()));
    connect(newProjectForm, SIGNAL(askCreateProject(blProjectControler*,blProjectNewFormWidget*)), this, SLOT(createProject(blProjectControler*,blProjectNewFormWidget*)));
}

// internal methods
void blProjectWidget::createTab(){

    // 1- create tab
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    m_tab = new QTabWidget;
    m_tab->setTabsClosable(true);
    layout->addWidget(m_tab);
    this->setLayout(layout);

    // 2- add blProjectBrowserWidget tab
    m_projectBrowserWidget = new blProjectBrowserWidget();
    m_tab->addTab(m_projectBrowserWidget, tr("Projects"));
    QTabBar *tabBar = m_tab->findChild<QTabBar *>();
    tabBar->tabButton(0, QTabBar::RightSide)->resize(0, 0);

    connect(m_projectBrowserWidget, SIGNAL(askOpenProject(blProjectInfo*)), this, SLOT(openProject(blProjectInfo*)));
    connect(m_projectBrowserWidget, SIGNAL(askDeleteProject(blProjectInfo*)), this, SLOT(deleteProject(blProjectInfo*)));
}

void blProjectWidget::deleteCurentTab(){
    m_tab->currentWidget()->deleteLater ();
    m_tab->removeTab( m_tab->currentIndex() );
}

void blProjectWidget::removeProcessingTab(int index){
    QWidget* widget = m_tab->widget(index);

    blProjectViewTab *wp = qobject_cast<blProjectViewTab*>(widget);
    if (wp){
        m_tab->setCurrentIndex(index);
        wp->saveMessageBox();
    }
    else{
        widget->deleteLater();
        m_tab->removeTab(index);
    }

}

void blProjectWidget::createProject(blProjectControler* controler, blProjectNewFormWidget* form){

    // 0- Test if the project exists
    blProjectAccess *access = blProjectAccess::instance();
    qDebug() << "project name to create = " << controler->projectName();
    blProjectInfo *foundedProject = access->database()->findProjectByName(controler->projectName());
    //access->database()->viewTable();
    if (foundedProject != NULL){
        QMessageBox::critical(this, tr("Create project error"), tr("A project with the same name already exists"));
        delete foundedProject;
        return;
    }

    // 1- Remove the form tab
    deleteCurentTab();

    // 2- save the project
    QString projectURL = m_projectsRootPath + QDir::separator() + controler->projectName();
    controler->saveProject(projectURL);

    // 3- Copy the data
    blProjectModelColumn column = controler->model()->mainColumn("Data").column("Images");
    controler->columnUpdateDataType("Data", "Images", blProjectModelColumn::IMAGE_URL);
    QMap<unsigned int, QString> map = column.data();
    QMapIterator<unsigned int, QString> it(map);
    unsigned int idx = -1;
    while (it.hasNext()) {
        it.next();
        idx++;

        QString path = it.value();
        QFileInfo fileInfo(path);
        QString filename(fileInfo.fileName());

        QString newPath = projectURL + QDir::separator() + "Data" + QDir::separator() + filename;

        if (!QFile::copy(path, newPath)){
            QMessageBox::critical(this, tr("Copy Error"), tr("Unage to copy image \n") + newPath +"\n from \n"+ path);
            return;
        }

        controler->columnUpdateData("Data", "Images", idx, newPath, true);
    }

    // 4- Update the project files
    controler->saveProject(projectURL);

    // 5- add the project to the project database
    blProjectAccess *projectBase = blProjectAccess::instance();
    blProjectInfo *projectInfo = new blProjectInfo;
    projectInfo->setName(controler->projectName());
    projectInfo->setUrl(projectURL);
    QDateTime now = QDateTime::currentDateTime();
    QString dateStr = now.toString("dd.MM.yyyy hh:mm:ss");
    projectInfo->setCreatedDate(dateStr);
    projectInfo->setLastModifiedDate(dateStr);
    projectBase->database()->addProject(projectInfo);

    // 5- view the project in a tab
    openProject(controler);
}

void blProjectWidget::openProject(blProjectControler* controler){

    blProjectViewTab *widget = new blProjectViewTab(controler, this);
    widget->addSelectorWidget(controler->view()->selectorWidget());
    m_tab->addTab(widget, controler->model()->projectName());
    m_tab->setCurrentWidget(widget);

    m_openedProjectList.append(controler->model()->projectName());

    connect(widget, SIGNAL(askCloseProject(QString)), this, SLOT(deleteCurentTabProject(QString)));
    connect(controler->view(), SIGNAL(askOpenCompo(QString)), this, SIGNAL(askOpenWorkflow(QString)));
}

void blProjectWidget::deleteCurentTabProject(QString projectName){

    for (int i = 0 ; i < m_openedProjectList.size() ; ++i){
        if (m_openedProjectList[i] == projectName){
            m_openedProjectList.removeAt(i);
            break;
        }
    }
    deleteCurentTab();
}

void blProjectWidget::deleteProject(blProjectInfo* info){

    QString projectName = info->name();
    bool opened = false;
    for (int i = 0 ; i < m_openedProjectList.size() ; ++i){
        if (m_openedProjectList[i] == projectName){
            opened = true;
            break;
        }
    }
    if (opened){
        QMessageBox::critical(this, tr("Delete project"), tr("Cannot delete an open project"));
        return;
    }

    qDebug() << "id of the project to delete = " << info->id();

    // remove form the database
    blProjectAccess *access = blProjectAccess::instance();

    bool success = access->database()->removeProject(info->id());

    if (success){
        // remove the folder
        QString projectUrl = info->url();
        if (blDir::deleteFolder(projectUrl)){
            m_projectBrowserWidget->rowDeletedFeedBack(true, "Project successfully removed");
        }
        else{
            m_projectBrowserWidget->rowDeletedFeedBack(false, "Cannot remove all the project files");
        }
    }
    else{
        m_projectBrowserWidget->rowDeletedFeedBack(false, "Cannot remove the project from the database");
    }
}
