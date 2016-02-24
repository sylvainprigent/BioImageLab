#pragma once

#include <QtWidgets>
#include "blHomeExport.h"

#include "blCore/blSettingsGroups.h"
#include "blHomeSettingsView.h"

/// \class blHomeWidgetBar
/// \brief Define a generic home bar widget
class BLHOME_EXPORT blHomeSettingsGroupView : public QWidget
{
    Q_OBJECT
public:
    blHomeSettingsGroupView(blSettingsGroups *settings, QWidget *parent = 0);

signals:
    void save(blSettingsGroups*);

private slots:
    void emitSave();

private:
    blSettingsGroups *m_settings;
    QList<blHomeSettingsView*> m_settingWidgets;
};
