#include "blLabController.h"

#include <blFinder>
#include <blToolCore>
#include <blTool>
#include <blCore>

#include "blProject/controller/blProjectBrowserController.h"
#include "blProject/controller/blProjectController.h"

blLabController::blLabController(QString settingsUrl, QString iconsDir, QWidget *parent) : QWidget(parent)
{

    m_iconsDir = iconsDir;
    m_settingsUrl = settingsUrl;
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
    m_communityIndex = -1;

    // connections
    connect(m_bar, SIGNAL(open(int)), this, SLOT(showTab(int)));
    connect(m_bar, SIGNAL(close(int)), this, SLOT(closeTab(int)));

}

void blLabController::addHomeButton(){

    QString buttonIcon = m_iconsDir + QDir::separator() + "home.png";
    m_bar->addButton(buttonIcon, "Home", 0, false);
    blHomeWidget *home = new blHomeWidget(this);
    home->addSection("Applications");
    blHomeTileInfo infoHubZero("blProject", "Projects", "Project for image batch processing", m_iconsDir + QDir::separator() + "project.png");
    home->addTile("Applications", infoHubZero);
    blHomeTileInfo infoFinder("blFinder", "Finder", "finder", m_iconsDir + QDir::separator() + "search_neg.png");
    home->addTile("Applications", infoFinder);
    blHomeTileInfo infoFinderAdmin("blFinderAdmin", "Finder admin", "finderAdmin", m_iconsDir + QDir::separator() + "search_neg.png");
    home->addTile("Applications", infoFinderAdmin);
    blHomeTileInfo infoSettings("blSettings", "Settings", "settings", m_iconsDir + QDir::separator() + "settings.png");
    home->addTile("Applications", infoSettings);
    m_centralWidget->addWidget(home);
    m_bar->setButtonChecked(0, false);

    connect(home, SIGNAL(action(blHomeTileInfo)), this, SLOT(openApp(blHomeTileInfo)));
}

void blLabController::showTab(int id){
    m_centralWidget->slideInIdx(id);
    m_bar->setButtonChecked(id);
}

void blLabController::closeTab(int id){

    if (m_centralWidget->currentIndex() == id){
        m_bar->setButtonChecked(id-1, false);
        m_centralWidget->setCurrentIndex(id-1);
    }
    if (m_settingIndex == id){
        m_settingIndex = -1;
    }
    m_bar->removeButton(id);
    delete m_centralWidget->widget(id);
}

void blLabController::openApp(blHomeTileInfo info){

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
    else if (info.name() == "Finder"){

        // initialize the database
        blFinderAccess *database = blFinderAccess::instance();
        blSettingsGroups settings;
        settings.load(m_settingsUrl);
        database->setDatabaseFile(settings.value("Finder", "Database URL"));
        database->load();

        // finder
        blFinderDefaultWidget *finder = new blFinderDefaultWidget(this);

        finder->setToolShedDir(settings.value("Finder", "Tool shed"));
        finder->setFinderDir(settings.value("Finder", "Finder directory"));
        finder->finder();
        m_centralWidget->addWidget(finder);
        m_bar->addButton(info.iconeUrl(), info.name(), m_centralWidget->count()-1, true);

        connect(finder, SIGNAL(openTool(QString)), this, SLOT(openTool(QString)));

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
    else if (info.name() == "Finder admin"){

        // initialize the database
        blFinderAccess *database = blFinderAccess::instance();
        blSettingsGroups settings;
        settings.load(m_settingsUrl);
        database->setDatabaseFile(settings.value("Finder", "Database URL"));
        database->load();

        blFinderAdminDefaultWidget *finderAdmin = new blFinderAdminDefaultWidget(this);
        m_centralWidget->addWidget(finderAdmin);
        m_bar->addButton(info.iconeUrl(), info.name(), m_centralWidget->count()-1, true);

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

void blLabController::openTool(QString xmlUrl){

    //qDebug() << "open tool" << xmlUrl;

    blToolParser pars;
    blToolInfo* toolInfo = pars.getToolInfo(xmlUrl);
    //toolInfo->print();

    blSettingsGroups settings;
    settings.load(m_settingsUrl);
    QString historyUrl = settings.value("Tools", "History directory");
    QString viewersUrl = settings.value("Tools", "Viewers directory");
    QString binariesUrl = settings.value("Tools", "Binaries directory", true);
    settings.save(m_settingsUrl);
    //qDebug() << "blLabController, historyUrl = " << historyUrl;

    blToolDefaultWidget *tool = new blToolDefaultWidget(toolInfo, historyUrl, viewersUrl, binariesUrl, this);
    m_centralWidget->addWidget(tool);
    m_bar->addButton( m_iconsDir + QDir::separator() + "tool.png", "Tool", m_centralWidget->count()-1, true);
    // show tab
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}

void blLabController::setSettingsUrl(QString url){
    m_settingsUrl = url;
}

void blLabController::setIconsDir(QString url){
    m_iconsDir = url;
}

blHomeSettingsGroupView * blLabController::loadSettings(){

    blSettingsGroups *groups = blSettingsAccess::instance()->settings();

    blHomeSettingsGroupView *view = new blHomeSettingsGroupView(groups, this);
    connect(view, SIGNAL(save(blSettingsGroups*)), this, SLOT(saveSettings(blSettingsGroups*)));
    return view;
}

void blLabController::saveSettings(blSettingsGroups *settings){

    // save settings
    settings->save(m_settingsUrl);
    // update stylesheet
    QString styleFile = settings->value("Home", "stylesheet");
    qApp->setStyleSheet("file:///" + styleFile);
    // message
    QMessageBox::information(this, tr("Save settings"), "Settings have been saved !");
}

void blLabController::newProject(){

    blProjectController *projectController = new blProjectController(this);
    m_centralWidget->addWidget(projectController);
    m_bar->addButton(m_iconsDir + QDir::separator() + "project.png", "Opened Project", m_centralWidget->count()-1, true);
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}

void blLabController::openProject(blProjectInfo* projectInfo){
    blProjectController *projectController = new blProjectController(this);
    projectController->openProject(projectInfo);

    m_centralWidget->addWidget(projectController);
    m_bar->addButton(m_iconsDir + QDir::separator() + "project.png", "Opened Project", m_centralWidget->count()-1, true);
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}
