#pragma once

#include <QtWidgets>
#include <blHome>
#include <blProjectnew>

class bioseController : public QWidget
{
    Q_OBJECT
public:
    explicit bioseController(QString iconsDir, QWidget *parent = 0);

signals:

public:
    void setIconsDir(QString url);

public slots:

private slots:
    void showTab(int id);
    void closeTab(int id);
    void openApp(blHomeTileInfo info);
    void saveSettings(blSettingsGroups *settings);
    void newProject();
    void openProject(blProjectInfo* projectInfo);

private:
    void initialize(QString settingsUrl);
    void addHomeButton();
    blHomeSettingsGroupView * loadSettings();

private:
    blHomeWidgetBar *m_bar ;
    blSlidingStackedWidget *m_centralWidget;

private:
    int m_settingIndex;
    int m_projectsIndex;
    QString m_iconsDir;

};
