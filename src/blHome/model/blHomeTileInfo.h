#pragma once

#include <QtWidgets>
#include "blHomeExport"

/// \class blHomeTileInfo
/// \brief Class containg the infos to create a tile
class BLHOME_EXPORT blHomeTileInfo
{
public:
    blHomeTileInfo();
    blHomeTileInfo(QString action, QString name, QString tooltip, QString iconeUrl);

public:
    // setters
    void setAction(QString action);
    void setName(QString name);
    void setTooltip(QString tooltip);
    void setIconeUrl(QString url);

    // getters
    QString action();
    QString name();
    QString tooltip();
    QString iconeUrl();

protected:
    QString m_action;
    QString m_name;
    QString m_tooltip;
    QString m_iconeUrl;
};
