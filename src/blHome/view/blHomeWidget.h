#pragma once

#include <QtWidgets>
#include "../../blWidgets/blHideableWidget.h"
#include "../model/blHomeTileInfo.h"

#include "blHomeExport"

/// \class blHomeWidget
/// \brief Define a generic home tiling widget
class BLHOME_EXPORT blHomeWidget : public QWidget
{
    Q_OBJECT
public:
    blHomeWidget(QWidget *parent = 0);

signals:
    void action(blHomeTileInfo action);

public:
    void addSection(QString name);
    void addTile(QString section, blHomeTileInfo info);

private:
    QStringList m_sectionsNames;
    QList<blHideableWidget*> m_sectionsWidgets;

private:
    QVBoxLayout *m_layout;
};
