#ifndef BLTOOLSTANDARDOUTPUTVIEWER_H
#define BLTOOLSTANDARDOUTPUTVIEWER_H

#include <QtWidgets>
#include "blToolExport.h"

class BLTOOL_EXPORT blToolStandardOutputViewer : public QWidget
{
    Q_OBJECT
public:
    blToolStandardOutputViewer(QWidget* parent = 0);

public slots:
    void updateOutput(QString data);
    void updateError(QString data);

private:
    QTextEdit *m_textEdit;
};

#endif // BLTOOLSTANDARDOUTPUTVIEWER_H
