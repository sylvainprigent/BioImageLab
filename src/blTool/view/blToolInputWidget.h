#ifndef BLTOOLINPUTWIDGET_H
#define BLTOOLINPUTWIDGET_H

#include <QtWidgets>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolInputWidget(QWidget *parent = 0);

signals:
    void help(QString help);

private slots:
    void emitHelp();

public:
    // setters/getters
    QString datatype();
    QString key();
    QString value();
    QString help();
    bool isAdvanced();
    void setDatatype(QString datatype);
    void setKey(QString key);
    void setValue(QString value);
    void setHelp(QString help);
    void setAdvanced(bool adv);

    void setHelpButtonVisible(bool visible);

protected:
    QString m_dataType;
    QString m_key;
    QString m_value;
    QString m_help;
    bool m_advanced;

protected:
    // gui
    QHBoxLayout *m_layout;
    QPushButton *m_helpButton;
};

// ///////////////////////////////////////////////// //
//                blToolInputValue
// ///////////////////////////////////////////////// //
class BLTOOL_EXPORT blToolInputValue : public blToolInputWidget{

    Q_OBJECT
public:
     blToolInputValue(QWidget *parent = 0);

public:
     void setValue(QString value);

private slots:
     void updateValue(QString value);

private:
    QLineEdit  *m_valueEdit;
};

// ///////////////////////////////////////////////// //
//                blToolInputSelect
// ///////////////////////////////////////////////// //
class BLTOOL_EXPORT blToolInputSelect : public blToolInputWidget{

    Q_OBJECT
public:
     blToolInputSelect(QWidget *parent = 0);

signals:
     void valueChanged(QString, QString);

public slots:
     void setContent(QString content);
     void setContent(QStringList content);

private slots:
     void updateValue(QString value);
     void emitValueChanged(QString value);

private:
    QComboBox  *m_conbobox;
};


// ///////////////////////////////////////////////// //
//                blToolInputBrowser
// ///////////////////////////////////////////////// //
class BLTOOL_EXPORT blToolInputBrowser : public blToolInputWidget{

    Q_OBJECT
public:
     blToolInputBrowser(QWidget *parent = 0, bool isDir = false);

private slots:
     void browse();
     void updateValue(QString value);

private:
    QLineEdit *m_pathEdit;
    bool m_isDir;
};

#endif // BLTOOLINPUTWIDGET_H
