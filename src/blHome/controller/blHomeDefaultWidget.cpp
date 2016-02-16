#include "blHomeDefaultWidget.h"

#include "../view/blHomeWidget.h"
#include "../view/blHomeSettingsGroupView.h"

blHomeDefaultWidget::blHomeDefaultWidget(QString iconsDir, QWidget *parent) : QWidget(parent)
{

    m_iconsDir = iconsDir;
    this->setObjectName("blHomeWidget");

    // global layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    // bar
    m_bar = new blHomeWidgetBar(this);
    m_bar->setFixedWidth(44);
    m_centralWidget = new blSlidingStackedWidget(this);

    layout->addWidget(m_bar);
    layout->addWidget(m_centralWidget);

    this->addHomeButton();
    m_settingIndex = -1;

    // connections
    connect(m_bar, SIGNAL(open(int)), this, SLOT(showTab(int)));
    connect(m_bar, SIGNAL(close(int)), this, SLOT(closeTab(int)));

}

void blHomeDefaultWidget::addHomeButton(){

    QString buttonIcon = m_iconsDir + QDir::separator() + "home.png";
    qDebug() << "icon = " << buttonIcon;
    m_bar->addButton(buttonIcon, "Home", 0, false);
    blHomeWidget *home = new blHomeWidget(this);
    home->addSection("Applications");
    blHomeTileInfo infoSettings("blSettings", "Settings", "settings", m_iconsDir + QDir::separator() + "settings.png");
    home->addTile("Applications", infoSettings);
    m_centralWidget->addWidget(home);
    m_bar->setButtonChecked(0, false);

    connect(home, SIGNAL(action(blHomeTileInfo)), this, SLOT(openApp(blHomeTileInfo)));
}

void blHomeDefaultWidget::showTab(int id){
    m_centralWidget->slideInIdx(id);
    m_bar->setButtonChecked(id);
}

void blHomeDefaultWidget::closeTab(int id){

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

void blHomeDefaultWidget::openApp(blHomeTileInfo info){

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

void blHomeDefaultWidget::setSettingsUrl(QString url){
    m_settingsUrl = url;
}

void blHomeDefaultWidget::setIconsDir(QString url){
    m_iconsDir = url;
}

blHomeSettingsGroupView * blHomeDefaultWidget::loadSettings(){

    QFile file(m_settingsUrl);
    blSettingsGroups groups;
    if (!file.exists()){

        // finder:
        groups.add("Example1", "directory", "/my/dir/");
        groups.add("Example1", "name", "my name");
        groups.add("Example1", "parameter", "value");

        // Tools:
        groups.add("Example2", "directory 2", "/my/dir/");
        groups.add("Example2", "name 2", "my name");
        groups.add("Example2", "parameter 2", "value");
    }
    else{
        groups.load(m_settingsUrl);
    }
    blHomeSettingsGroupView *view = new blHomeSettingsGroupView(groups, this);
    connect(view, SIGNAL(save(blSettingsGroups)), this, SLOT(saveSettings(blSettingsGroups)));
    return view;
}

void blHomeDefaultWidget::saveSettings(blSettingsGroups settings){
    settings.print();
    settings.save(m_settingsUrl);
    QMessageBox::information(this, tr("Save settings"), "Settings have been saved !");
}
