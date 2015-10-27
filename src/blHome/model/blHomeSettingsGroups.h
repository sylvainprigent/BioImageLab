#pragma once

#include <QtWidgets>
#include "blHomeExport"
#include "blHomeSettings.h"

/// \class blHomeTileInfo
/// \brief Class containg the infos to create a tile
class BLHOME_EXPORT blHomeSettingsGroups
{
public:
    blHomeSettingsGroups();

public:
    // setters / getters
    void add(QString group, QString key, QString value);
    void add(QString group, blHomeSettings settings);
    QString value(QString group, QString key);

    int groupsCount();
    QString groupTitleAt(int i);
    blHomeSettings groupAt(int i);

public:
    void load(QString fileUrl);
    void save(QString fileUrl);
    void print();

public:
    friend QDataStream & operator <<(QDataStream &s, const blHomeSettingsGroups &c);
    friend QDataStream & operator >>(QDataStream& stream, blHomeSettingsGroups& c);

protected:
    int groupIdx(QString group);

protected:
    QList<blHomeSettings> m_settings;
    QStringList m_groups;
};
