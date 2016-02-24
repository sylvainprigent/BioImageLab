#ifndef BLTOOLPARAMETERSELECTORWIDGET_H
#define BLTOOLPARAMETERSELECTORWIDGET_H

#include <QtWidgets>
#include "blToolCore/model/blToolParameters.h"
#include "blToolCore/model/blioParameters.h"
#include "blToolInputWidget.h"
#include "blToolExport.h"

class BLTOOL_EXPORT blToolParameterSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit blToolParameterSelectorWidget(blToolParameters parameters, QWidget *parent = 0);

signals:
    void help(QString);

public slots:
    blioParameters *getData();

private slots:
    void showHideConditional(QString conditionName, QString conditionValue);
    void showHideAdvanced(int adv);

private:
    void initializeConditions();

private:
    QGridLayout *m_layout;

private:
    QMap<QString, blToolInputWidget*> m_widgets;
    QMap<QString, QLabel*> m_labels;
    QList<blToolParameterCondition> m_parametersConditional;
    bool m_advancedMode;
};

#endif // BLTOOLPARAMETERSELECTORWIDGET_H
