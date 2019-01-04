#ifndef blProjectInfoForm_H
#define blProjectInfoForm_H

#include <QtWidgets>
#include "../model/blProjectTypes.h"
#include "../model/blProjectInfo.h"
#include "blWidgets/blTwoSideWidget.h"

class blProjectInfoForm : public QWidget
{
    Q_OBJECT
public:
    explicit blProjectInfoForm(blProjectTypes &projectTypes, QWidget *parent = 0);

signals:
    void askEditProject(blProjectInfo* info);

public slots:
    void setData(blProjectInfo* info);

private slots:
    void emitEditedProject();
    void showHelp();

private:
    void buildWidget(blProjectTypes &projectTypes);

public:
    void editView();

private:
    int m_projectId;
    QLineEdit *m_nameEdit;
    QTextEdit *m_descriptionEdit;
    QComboBox *m_typeEdit;
    QPushButton *m_saveButton;

    blTwoSideWidget* m_twoSideWidget;

};

#endif // blProjectInfoForm_H
