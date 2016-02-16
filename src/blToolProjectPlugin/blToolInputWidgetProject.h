#ifndef BLTOOLINPUTWIDGETPROJECT_H
#define BLTOOLINPUTWIDGETPROJECT_H

#include <QtWidgets>
#include "blToolProjectPluginExport.h"
#include "blTool/view/blToolInputWidget.h"
#include "blProject/model/blProjectModel.h"
#include "blToolCore/model/blioDataInfo.h"

class BLTOOLPROJECTPLUGIN_EXPORT blToolInputWidgetProject : public blToolInputWidget
{

    Q_OBJECT
public:
     blToolInputWidgetProject(QWidget *parent = 0);

public slots:
     void setProject(blProjectModel* projectModel);
     QList<QStringList> getData();

private slots:
     void browse();
     void hideBrowser();
     void changeSubColumns(QString mainColumnName);
     void seeSelection();

private:
     void createBrowserWidget();

private:
     blProjectModel* m_projectModel;

private:
     QWidget *m_browser;
     QComboBox *m_columnBox;
     QComboBox *m_subColumnBox;
     QTableWidget *m_tableWidget;
};

#endif // BLTOOLINPUTWIDGETPROJECT_H
