#ifndef blProjectController_H
#define blProjectController_H

#include "blProjectnewExport.h"

#include <QtWidgets>
#include "../view/blProjectInfoForm.h"
#include "../model/blProjectModel.h"
#include "../view/blProjectImportConditionalView.h"
#include "../view/blProjectDataView.h"

class BLPROJECTNEW_EXPORT blProjectController : public QWidget
{
    Q_OBJECT
public:
    blProjectController(QWidget* parent = 0);

public:
    void openProject(blProjectInfo* info);

private slots:
    void showInfo();
    void showImport();
    void showData();
    void showProcess();
    void showExport();

private:
    void loadInformationFromDatabase();
    void enableToolBarButtons(bool enabled);

private:
    QWidget* createCentralArea();
    QWidget* createToolBar();

private:
    blProjectTypes m_availableprojectTypes;

private:
    // views
    blProjectInfoForm *m_informationForm;
    blProjectImportConditionalView *m_importForm;
    blProjectDataView *m_dataView;

private:
    //models
    blProjectInfo *m_projectInfo;
    blProjectModel *m_projectModel;

private slots:
    // model slots
    void editProjectInfo(blProjectInfo* info);
    void importData(blImportDataInfo *importDataInfo);

private:
    QPushButton *m_infoButton;
    QPushButton *m_importButton;
    QPushButton *m_dataButton;
    QPushButton *m_processButton;
    QPushButton *m_exportButton;
};

#endif // blProjectController_H
