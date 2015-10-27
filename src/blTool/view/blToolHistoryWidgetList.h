#ifndef BLTOOLHISTORYWIDGETLIST_H
#define BLTOOLHISTORYWIDGETLIST_H

#include <QtWidgets>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolHistoryWidgetList : public QWidget
{
    Q_OBJECT
public:
    blToolHistoryWidgetList(QString datatype, QString text, QString desc, QWidget *parent);

signals:
    void clicked(QString dataType, QString dataUrl, QString desc);

private slots:
    void emitClicked();

private:
    QString m_text;
    QString m_description;
    QString m_datatype;

};

#endif // BLTOOLHISTORYWIDGETLIST_H
