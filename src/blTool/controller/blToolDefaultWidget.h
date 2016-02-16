#ifndef BLTOOLDEFAULTWIDGET_H
#define BLTOOLDEFAULTWIDGET_H

#include <QtWidgets>
#include "../view/blToolExecGui.h"
#include "../view/blToolHistoryBar.h"
#include "blToolCore/model/blToolExec.h"
#include "../model/blToolHistoryBrowser.h"
#include "blToolCore/model/blToolExecViewer.h"
#include "../view/blToolDocWidget.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolDefaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolDefaultWidget(blToolInfo *toolInfo, QString historyUrl, QString viewersDir, QString binariesDir, QWidget *parent = 0);

signals:

public slots:
    void openHistory(QString historyFile);

private slots:
    void closeTab(int index);
    void showViewerExecError(QString message);

private:
    QWidget* createExecArea();
    QWidget* createCentralArea();
    QWidget* createHistoryArea();

private:
    // models
    blToolExecGui *m_execWidget;
    blToolInfo *m_toolInfo;
    blToolExec *m_toolExec;
    blToolExecViewer *m_toolExecViewer;

private:
    // views
    blToolHistoryBrowser* m_history;
    blToolHistoryBar *m_historyBar;
    QTabWidget *m_centralWidget;
    blToolDocWidget *m_docWidget;

private:
    // settings
    QString m_historyDir;
    QString m_viewersDir;
    QString m_binariesDir;
};

#endif // BLTOOLDEFAULTWIDGET_H
