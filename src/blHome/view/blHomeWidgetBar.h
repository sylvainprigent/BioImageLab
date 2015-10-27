#pragma once

#include <QtWidgets>
#include "blHomeExport"

/// \class blHomeWidgetBar
/// \brief Define a generic home bar widget
class BLHOME_EXPORT blHomeWidgetBar : public QWidget
{
    Q_OBJECT
public:
    blHomeWidgetBar(QWidget *parent = 0);

signals:
    void open(int);
    void close(int);

public slots:
    void addButton(QString icon, QString toolTip, int id, bool closable = true);
    void removeButton(int id);
    void setButtonChecked(int id, bool clicked = true);

private:
    QVBoxLayout *m_layout;
};
