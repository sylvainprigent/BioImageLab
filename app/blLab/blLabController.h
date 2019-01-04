/// \file blLabController.h
/// \brief blLabController
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include <QtWidgets>
#include <blHome>
#include <blProjectCore>

class blLabController : public QWidget
{
    Q_OBJECT
public:
    explicit blLabController(QString settingsUrl, QString iconsDir, QWidget *parent = 0);

signals:

public:
    void setSettingsUrl(QString url);
    void setIconsDir(QString url);

public slots:

private slots:
    void showTab(int id);
    void closeTab(int id);
    void openApp(blHomeTileInfo info);
    void saveSettings(blSettingsGroups *settings);
    void openTool(QString xmlUrl);
    void newProject();
    void openProject(blProjectInfo* projectInfo);
    void openNewProject(blProjectInfo* projectInfo);

private:
    void initialize(QString settingsUrl);
    void addHomeButton();
    blHomeSettingsGroupView * loadSettings();

private:
    blHomeWidgetBar *m_bar ;
    blSlidingStackedWidget *m_centralWidget;

private:
    int m_settingIndex;
    QString m_settingsUrl;
    QString m_iconsDir;
    int m_projectsIndex;
    int m_newProjectIndex;
};
