#pragma once

#include <QtWidgets>
#include "blCoreExport"
#include "blSettings.h"

/// \class blHomeTileInfo
/// \brief Class containg the infos to create a tile
class BLCORE_EXPORT blSettingsGroups
{
public:
    blSettingsGroups();

public:
    // setters / getters
    void add(QString group, QString key, QString value);
    void add(QString group, blSettings settings);
    QString value(QString group, QString key, bool createIfNotExist = false);

    int groupsCount();
    QString groupTitleAt(int i);
    blSettings groupAt(int i);

public:
    void load(QString fileUrl);
    void save(QString fileUrl);
    void print();

public:
    friend QDataStream & operator <<(QDataStream &s, const blSettingsGroups &c);
    friend QDataStream & operator >>(QDataStream& stream, blSettingsGroups& c);

protected:
    int groupIdx(QString group);

protected:
    QList<blSettings> m_settings;
    QStringList m_groups;
};
