#pragma once

#include <QtWidgets>
#include <blHome>

class bioseController : public QWidget
{
    Q_OBJECT
public:
    explicit bioseController(QString settingsUrl, QString iconsDir, QWidget *parent = 0);

signals:

public:
    void setSettingsUrl(QString url);
    void setIconsDir(QString url);
    void setHubZeroUrl(QString hubZeroUrl);

public slots:

private slots:
    void showTab(int id);
    void closeTab(int id);
    void openApp(blHomeTileInfo info);
    void saveSettings(blSettingsGroups settings);
    void openTool(QString xmlUrl);

private:
    void initialize(QString settingsUrl);
    void addHomeButton();
    blHomeSettingsGroupView * loadSettings();

private:
    blHomeWidgetBar *m_bar ;
    blSlidingStackedWidget *m_centralWidget;

private:
    int m_settingIndex;
    int m_communityIndex;
    QString m_settingsUrl;
    QString m_iconsDir;
    QString m_hubZeroUrl;
};
