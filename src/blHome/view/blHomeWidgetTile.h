#pragma once

#include <QtWidgets>
#include "../model/blHomeTileInfo.h"

#include "blHomeExport"

/// \class blHomeWidgetTile
/// \brief Define a tile for the home tiling menu
class BLHOME_EXPORT blHomeWidgetTile : public QWidget
{
    Q_OBJECT
public:
    blHomeWidgetTile(QWidget *parent = 0);
    blHomeWidgetTile(blHomeTileInfo info, QWidget *parent=0);

signals:
    void clicked();
    void clicked(blHomeTileInfo info);

public slots:
    void setText(QString txt);
    void setIcon(QString icon);

private slots:
    void emitClicked();

private:
    QLabel *m_label;
    QPushButton *m_button;
    blHomeTileInfo m_info;

private:
    void buildButton();
};
