#pragma once

#include <QtWidgets>
#include "blHomeExport.h"
#include "../../blWidgets/blSlidingStackedWidget.h"
#include "../view/blHomeWidgetBar.h"
#include "../model/blHomeTileInfo.h"
#include "../view/blHomeSettingsGroupView.h"

class BLHOME_EXPORT blHomeDefaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blHomeDefaultWidget(QString iconsDir, QWidget *parent = 0);

signals:

public:
    void setSettingsUrl(QString url);
    void setIconsDir(QString url);

public slots:

private slots:
    void showTab(int id);
    void closeTab(int id);
    void openApp(blHomeTileInfo info);
    void saveSettings(blSettingsGroups settings);

private:
    void addHomeButton();
    blHomeSettingsGroupView * loadSettings();

private:
    blHomeWidgetBar *m_bar ;
    blSlidingStackedWidget *m_centralWidget;

private:
    int m_settingIndex;
    QString m_settingsUrl;
    QString m_iconsDir;
};
