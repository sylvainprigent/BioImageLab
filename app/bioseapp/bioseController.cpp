#include "bioseController.h"
#include "blProjectnew/controller/blProjectBrowserController.h"
#include "blProjectnew/controller/blProjectController.h"
#include "blCore/blSettingsAccess.h"

#include <blFinder>
#include <blToolCore>
#include <blTool>

bioseController::bioseController(QString iconsDir, QWidget *parent) : QWidget(parent)
{

    m_iconsDir = iconsDir;
    this->setObjectName("blHomeWidget");

    // global layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);

    // bar
    m_bar = new blHomeWidgetBar(this);
    m_bar->setFixedWidth(44);
    m_centralWidget = new blSlidingStackedWidget(this);

    layout->addWidget(m_bar);
    layout->addWidget(m_centralWidget);

    this->addHomeButton();
    m_settingIndex = -1;
    m_projectsIndex = -1;

    // connections
    connect(m_bar, SIGNAL(open(int)), this, SLOT(showTab(int)));
    connect(m_bar, SIGNAL(close(int)), this, SLOT(closeTab(int)));

}

void bioseController::addHomeButton(){

    QString buttonIcon = m_iconsDir + QDir::separator() + "home.png";
    m_bar->addButton(buttonIcon, "Home", 0, false);

    // widget home
    blHomeWidget *home = new blHomeWidget(this);

    // tools tiles
    home->addSection("Applications");
    blHomeTileInfo infoSettings("blSettings", "Settings", "settings", m_iconsDir + QDir::separator() + "settings.png");
    home->addTile("Applications", infoSettings);
    blHomeTileInfo infoProject("blProjects", "Projects", "projects", m_iconsDir + QDir::separator() + "project.png");
    home->addTile("Applications", infoProject);

    // add to central area
    m_centralWidget->addWidget(home);
    m_bar->setButtonChecked(0, false);

    connect(home, SIGNAL(action(blHomeTileInfo)), this, SLOT(openApp(blHomeTileInfo)));
}

void bioseController::showTab(int id){
    m_centralWidget->slideInIdx(id);
    m_bar->setButtonChecked(id);
}

void bioseController::closeTab(int id){

    if (m_centralWidget->currentIndex() == id){
        m_bar->setButtonChecked(id-1, false);
        m_centralWidget->setCurrentIndex(id-1);
    }
    if (m_settingIndex == id){
        m_settingIndex = -1;
    }
    if (m_projectsIndex == id){
        m_projectsIndex = -1;
    }
    m_bar->removeButton(id);
    delete m_centralWidget->widget(id);
}

void bioseController::openApp(blHomeTileInfo info){

    if (info.name() == "Settings"){
        if (m_settingIndex > 0){
            m_bar->setButtonChecked(m_settingIndex, false);
            m_centralWidget->slideInIdx(m_settingIndex);
            return;
        }
        else{
            m_settingIndex = m_centralWidget->count();
            blHomeSettingsGroupView * settingsWidget = this->loadSettings();
            m_centralWidget->addWidget(settingsWidget);
            m_bar->addButton(info.iconeUrl(), info.name(), m_centralWidget->count()-1, true);
        }
    }
    else if (info.name() == "Projects"){
        if (m_projectsIndex > 0){
            m_bar->setButtonChecked(m_projectsIndex, false);
            m_centralWidget->slideInIdx(m_projectsIndex);
            return;
        }
        else{
            m_projectsIndex = m_centralWidget->count();
            blProjectBrowserController *projectsBrowser = new blProjectBrowserController(this);
            connect(projectsBrowser, SIGNAL(askNewProject()), this, SLOT(newProject()));
            connect(projectsBrowser, SIGNAL(askOpenProject(blProjectInfo*)), this, SLOT(openProject(blProjectInfo*)));
            m_centralWidget->addWidget(projectsBrowser);
            m_bar->addButton(info.iconeUrl(), info.name(), m_centralWidget->count()-1, true);
        }
    }
    else{
        // add widget
        QLabel *test = new QLabel("test add app " + QString::number(m_centralWidget->count()), this);
        m_centralWidget->addWidget(test);
        m_bar->addButton(info.iconeUrl(), "Test", m_centralWidget->count()-1, true);
    }

    // show tab
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}

void bioseController::setIconsDir(QString url){
    m_iconsDir = url;
}

blHomeSettingsGroupView * bioseController::loadSettings(){

    blHomeSettingsGroupView *view = new blHomeSettingsGroupView(blSettingsAccess::instance()->settings(), this);
    connect(view, SIGNAL(save(blSettingsGroups*)), this, SLOT(saveSettings(blSettingsGroups*)));
    return view;
}

void bioseController::saveSettings(blSettingsGroups *settings){

    // save settings
    blSettingsAccess::instance()->save();
    // update stylesheet
    QString styleFile = blSettingsAccess::instance()->settings()->value("Home", "stylesheet");
    qApp->setStyleSheet("file:///" + styleFile);
    // message
    QMessageBox::information(this, tr("Save settings"), "Settings have been saved !");
}

void bioseController::newProject(){

    blProjectController *projectController = new blProjectController(this);
    m_centralWidget->addWidget(projectController);
    m_bar->addButton(m_iconsDir + QDir::separator() + "project.png", "Opened Project", m_centralWidget->count()-1, true);
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}

void bioseController::openProject(blProjectInfo* projectInfo){
    blProjectController *projectController = new blProjectController(this);
    projectController->openProject(projectInfo);

    m_centralWidget->addWidget(projectController);
    m_bar->addButton(m_iconsDir + QDir::separator() + "project.png", "Opened Project", m_centralWidget->count()-1, true);
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}
