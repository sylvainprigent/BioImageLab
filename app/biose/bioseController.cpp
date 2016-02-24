#include "bioseController.h"

#include <blFinder>
#include <blToolCore>
#include <blTool>

bioseController::bioseController(QString settingsUrl, QString iconsDir, QWidget *parent) : QWidget(parent)
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


void bioseController::setHubZeroUrl(QString hubZeroUrl){
    m_hubZeroUrl = hubZeroUrl;
}

void bioseController::addHomeButton(){

    QString buttonIcon = m_iconsDir + QDir::separator() + "home.png";
    m_bar->addButton(buttonIcon, "Home", 0, false);
    blHomeWidget *home = new blHomeWidget(this);
    home->addSection("Applications");
    blHomeTileInfo infoSettings("blSettings", "Settings", "settings", m_iconsDir + QDir::separator() + "settings.png");
    home->addTile("Applications", infoSettings);
    blHomeTileInfo infoHubZero("blHubZero", "Community", "Bio Imaging Community", m_iconsDir + QDir::separator() + "people.png");
    home->addTile("Applications", infoHubZero);
    blHomeTileInfo infoFinder("blFinder", "Finder", "finder", m_iconsDir + QDir::separator() + "search_neg.png");
    home->addTile("Applications", infoFinder);
    blHomeTileInfo infoFinderAdmin("blFinderAdmin", "Finder admin", "finderAdmin", m_iconsDir + QDir::separator() + "search_neg.png");
    home->addTile("Applications", infoFinderAdmin);
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
    else if (info.name() == "Community"){
        if (m_communityIndex > 0){
            m_bar->setButtonChecked(m_communityIndex, false);
            m_centralWidget->slideInIdx(m_communityIndex);
            return;
        }
        else{
            m_communityIndex = m_centralWidget->count();
            blWebBrowser* webBrowser = new blWebBrowser(this);
            webBrowser->setHomePage(m_hubZeroUrl, true);
            m_centralWidget->addWidget(webBrowser);
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

void bioseController::openTool(QString xmlUrl){

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
    //qDebug() << "bioseController, historyUrl = " << historyUrl;

    blToolDefaultWidget *tool = new blToolDefaultWidget(toolInfo, historyUrl, viewersUrl, binariesUrl, this);
    m_centralWidget->addWidget(tool);
    m_bar->addButton( m_iconsDir + QDir::separator() + "tool.png", "Tool", m_centralWidget->count()-1, true);
    // show tab
    m_centralWidget->slideInIdx(m_centralWidget->count()-1);
    m_bar->setButtonChecked(m_centralWidget->count()-1, false);
}

void bioseController::setSettingsUrl(QString url){
    m_settingsUrl = url;
}

void bioseController::setIconsDir(QString url){
    m_iconsDir = url;
}

blHomeSettingsGroupView * bioseController::loadSettings(){

    QFile file(m_settingsUrl);
    blSettingsGroups *groups = new blSettingsGroups;
    if (!file.exists()){

        // home:
        groups->add("Home", "stylesheet", "");

        // finder:
        groups->add("Finder", "Database URL", "");
        groups->add("Finder", "Tool shed", ""); // "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\tools\\"
        groups->add("Finder", "Finder directory", ""); // "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\"

        // Tools:
        groups->add("Tools", "History directory", ""); //"C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\history\\"
        groups->add("Tools", "Viewers directory", ""); // "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\viewers\\"

    }
    else{
        groups->load(m_settingsUrl);
    }
    blHomeSettingsGroupView *view = new blHomeSettingsGroupView(groups, this);
    connect(view, SIGNAL(save(blSettingsGroups*)), this, SLOT(saveSettings(blSettingsGroups*)));
    return view;
}

void bioseController::saveSettings(blSettingsGroups *settings){

    // save settings
    settings->save(m_settingsUrl);
    // update stylesheet
    QString styleFile = settings->value("Home", "stylesheet");
    qApp->setStyleSheet("file:///" + styleFile);
    // message
    QMessageBox::information(this, tr("Save settings"), "Settings have been saved !");
}
