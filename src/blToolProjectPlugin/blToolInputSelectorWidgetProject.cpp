#include "blToolInputSelectorWidgetProject.h"

#include "blTool/view/blToolInputWidget.h"
#include "blProject/model/blProjectDatabase.h"
#include "blCore/blSettingsAccess.h"
#include "blToolInputWidgetProject.h"
#include "blProject/model/blProjectModel.h"
#include "blProject/model/blProjectAccess.h"

blToolInputSelectorWidgetProject::blToolInputSelectorWidgetProject(blToolIO toolIO,QWidget *parent)
    :blToolInputSelectorWidgetInterface(toolIO, parent){

    QGridLayout *dirLayout = new QGridLayout;
    dirLayout->setContentsMargins(0,7,0,0);
    this->setLayout(dirLayout);

    // project info widgets
    m_projectSelector = new QComboBox(this);
    this->getProjectsList();
    QLabel* titleProject = new QLabel(tr("Project"), this);
    dirLayout->addWidget(titleProject, 0, 0, 1, 1);
    dirLayout->addWidget(m_projectSelector, 0, 1, 1, 1);
    connect(m_projectSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(setProjectNameToSelectors(QString)));

    m_outputColumnName = new QLineEdit(this);
    QLabel *titleColumn = new QLabel(tr("Output column"), this);
    dirLayout->addWidget(titleColumn,1, 0, 1, 1);
    dirLayout->addWidget(m_outputColumnName, 1, 1, 1, 1);
    connect(m_outputColumnName, SIGNAL(textChanged(QString)), this, SLOT(changeColumnOutputDir(QString)));

    // tool input widget
    for(unsigned int i = 0 ; i < toolIO.inputsCount() ; ++i){

        QLabel *title = new QLabel(toolIO.inputNameAt(i), this);
        blToolInputWidgetProject *browser = new blToolInputWidgetProject(this);
        m_selectors.append(browser);
        browser->setDatatype(toolIO.inputTypeAt(i));
        browser->setKey(toolIO.inputNameAt(i));
        browser->setHelpButtonVisible(false);
        dirLayout->addWidget(title, i+2, 0);
        dirLayout->addWidget(browser, i+2, 1);
    }
}

void blToolInputSelectorWidgetProject::getProjectsList(){

    blSettingsAccess* settingsAccess = blSettingsAccess::instance();
    QString projectsUrl = settingsAccess->settings()->value("Project", "Projects directory", false);

    blProjectDatabase database(projectsUrl + "projectDatabase.db");
    QList<blProjectInfo*> projects = database.allProjects();
    for(int i = 0 ; i < projects.count() ; ++i){
        m_projectSelector->addItem(projects[i]->name());
    }
}

blioDataInfo *blToolInputSelectorWidgetProject::getData(){
    blioDataInfo * io = new blioDataInfo;

    QLayout *layout = this->layout();

    // get the inputs data
    QStringList datatypes;
    QStringList keys;
    QList< QList<QStringList> > values;
    for (int i = 0; i < layout->count(); ++i) {
        QWidget *w = layout->itemAt(i)->widget();
        blToolInputWidgetProject* wt = qobject_cast<blToolInputWidgetProject*>(w);
        if(wt != NULL){
            datatypes.append(wt->datatype());
            keys.append(wt->key());
            values.append(wt->getData());
        }
    }

    // fill the io object
    if (values.count() > 0){
        // Check that all the inputs have the same number of files
        unsigned int dataCount = values[0].count();
        for(int i = 0 ; i < datatypes.count() ; ++i){
            if (values[i].count() != dataCount){
                emit error(tr("The input folders does not have the same number of files !"));
                return io;
            }
        }
        // add ios
        for(unsigned int f = 0 ; f < dataCount ; ++f ){
            blioDataList dataList;
            for (int i = 0 ; i < values.count() ; i++){
                QStringList metaInfo; metaInfo.append(values[i][f][0]);
                dataList.add(datatypes[i], keys[i], values[i][f][0]);
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

void blToolInputSelectorWidgetProject::setProjectNameToSelectors(QString projectName){

    // get the project info
    blSettingsAccess* settingsAccess = blSettingsAccess::instance();
    QString projectsDir = settingsAccess->settings()->value("Project", "Projects directory", false);

    blProjectAccess* projectAccess = blProjectAccess::instance();
    projectAccess->setDatabaseFile(projectsDir + "projectDatabase.db");
    projectAccess->load();

    blProjectInfo* projectInfo = projectAccess->database()->findProjectByName(projectName);

    m_projectModel = new blProjectModel(this);
    m_projectModel->setProjectUrl(projectInfo->url());
    m_projectModel->load();

    for(int i = 0 ; i < m_selectors.count() ; ++i){
        m_selectors[i]->setProject(m_projectModel);
    }

    emit changeOutputDir(projectInfo->url() + QDir::separator() + m_outputColumnName->text() );
}

void blToolInputSelectorWidgetProject::changeColumnOutputDir(QString){
    this->setProjectNameToSelectors(m_projectSelector->currentText());
}

void blToolInputSelectorWidgetProject::saveOutputMetaData(int processId, QString outputDir, blioDataInfo* inputs, blioDataInfo* outputs, blioParameters* params, blToolInfo* toolinfo){
    /// \todo implement this function
}

void blToolInputSelectorWidgetProject::progressFinished(int, QString){
    // nothing to do
}
