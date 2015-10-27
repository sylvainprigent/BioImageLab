#pragma once

#include <QtWidgets>
#include "blHomeExport"

#include "../model/blHomeSettingsGroups.h"
#include "blHomeSettingsView.h"

/// \class blHomeWidgetBar
/// \brief Define a generic home bar widget
class BLHOME_EXPORT blHomeSettingsGroupView : public QWidget
{
    Q_OBJECT
public:
    blHomeSettingsGroupView(blHomeSettingsGroups settings, QWidget *parent = 0);

signals:
    void save(blHomeSettingsGroups);

private slots:
    void emitSave();

private:
    blHomeSettingsGroups m_settings;
    QList<blHomeSettingsView*> m_settingWidgets;
};
