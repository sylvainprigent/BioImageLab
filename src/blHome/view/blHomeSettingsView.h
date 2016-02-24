#pragma once

#include <QtWidgets>
#include "blHomeExport.h"

#include "blCore/blSettings.h"

/// \class blHomeWidgetBar
/// \brief Define a generic home bar widget
class BLHOME_EXPORT blHomeSettingsView : public QWidget
{
    Q_OBJECT
public:
    blHomeSettingsView(blSettings settings, QWidget *parent = 0);

signals:

public:
    void setTitle(QString title);
    QString title();
    blSettings settings();
    void setTitleVisible(bool value);

private:
    QGridLayout *m_layout;
    blSettings m_settings;
    QLabel *m_titleLabel;
};

// ////////////////////////////////////////
//          blHomeSettingsWidget
// ////////////////////////////////////////
class BLHOME_EXPORT blHomeSettingsWidget : public QWidget{

    Q_OBJECT
public:
    blHomeSettingsWidget(QString key, QString value, QString type, QWidget *parent = 0);

public:
    QString key();
    virtual QString value() = 0;
    QString type();

protected:
    QString m_key;
    QString m_value;
    QString m_type;
};

// ////////////////////////////////////////
//      blHomeSettingsWidgetLineEdit
// ////////////////////////////////////////
class BLHOME_EXPORT blHomeSettingsWidgetLineEdit : public blHomeSettingsWidget{

    Q_OBJECT
public:
    blHomeSettingsWidgetLineEdit(QString key, QString value, QString type, QWidget *parent = 0);

public:
    QString value();

private:
    QLineEdit *m_lineEdit;
};


