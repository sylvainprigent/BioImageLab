#include "blToolParameterSelectorWidget.h"
#include "blToolInputWidget.h"

blToolParameterSelectorWidget::blToolParameterSelectorWidget(blToolParameters parameters, QWidget *parent) : QWidget(parent)
{
    m_layout = new QGridLayout;
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout);

    QCheckBox *advancedToggleButton = new QCheckBox(tr("Advanced"), this);
    connect(advancedToggleButton, SIGNAL(stateChanged(int)), this, SLOT(showHideAdvanced(int)));
    m_advancedMode = false;
    m_layout->addWidget(advancedToggleButton, 0, 0);

    m_parametersConditional = parameters.conditions();

    for(unsigned int i = 0 ; i < parameters.count() ; ++i){

        blToolParameter parameter = parameters.at(i);
        QLabel *title = new QLabel(parameter.label(), this);
        m_labels[parameter.name()] = title;

        if (parameter.type() == "integer" || parameter.type() == "number"){
            blToolInputValue *valueEdit = new blToolInputValue(this);
            valueEdit->setKey(parameter.name());
            valueEdit->setHelp(parameter.help());
            valueEdit->setValue(parameter.value());
            valueEdit->setAdvanced(parameter.advanced());
            m_widgets[parameter.name()] = valueEdit;
            connect(valueEdit, SIGNAL(help(QString)), this, SIGNAL(help(QString)));
            m_layout->addWidget(title, i+1, 0);
            m_layout->addWidget(valueEdit, i+1, 1);
        }
        else if (parameter.type() == "select"){

            //qDebug() << "add select widget";
            blToolInputSelect *w = new blToolInputSelect(this);
            w->setKey(parameter.name());
            w->setHelp(parameter.help());
            w->setContent(parameter.value());
            w->setAdvanced(parameter.advanced());
            m_widgets[parameter.name()] = w;
            connect(w, SIGNAL(help(QString)), this, SIGNAL(help(QString)));
            connect(w, SIGNAL(valueChanged(QString, QString)), this, SLOT(showHideConditional(QString,QString)));
            m_layout->addWidget(title, i+1, 0);
            m_layout->addWidget(w, i+1, 1);
            //qDebug() << "add select widget done";
        }
        else if (parameter.type() == "file" ){
            blToolInputBrowser *w = new blToolInputBrowser(this, false);
            w->setKey(parameter.name());
            w->setHelp(parameter.help());
            w->setAdvanced(parameter.advanced());
            m_widgets[parameter.name()] = w;
            connect(w, SIGNAL(help(QString)), this, SIGNAL(help(QString)));
            m_layout->addWidget(title, i+1, 0);
            m_layout->addWidget(w, i+1, 1);
        }
    }

    //qDebug() << "initialize conditions";
    this->initializeConditions();
    //qDebug() << "initialize conditions done";
}

void blToolParameterSelectorWidget::showHideAdvanced(int adv){

    if (adv > 0){
        m_advancedMode = true;
    }
    else{
        m_advancedMode = false;
    }

    QMapIterator<QString, blToolInputWidget*> widgetMap(m_widgets);
    QMapIterator<QString, QLabel*> labelMap(m_labels);
    while (widgetMap.hasNext()) {
        widgetMap.next();
        labelMap.next();

        blToolInputWidget* w = widgetMap.value();
        QLabel *label = labelMap.value();
        if (w->isAdvanced() && m_advancedMode){
            w->setVisible(true);
            label->setVisible(true);
        }
        else if(w->isAdvanced() && !m_advancedMode){
            w->setVisible(false);
            label->setVisible(false);
        }
    }

    for(int i = 0 ; i < m_parametersConditional.count() ; ++i){
        blToolParameterCondition cond = m_parametersConditional.at(i);

        // get condition widget
        if(m_widgets[cond.conditionName()]->value() == cond.conditionValue()){
            if (m_widgets[cond.conditionalName()]->isAdvanced()){
                if (m_advancedMode){
                    m_widgets[cond.conditionalName()]->setVisible(true);
                    m_labels[cond.conditionalName()]->setVisible(true);
                }
                else{
                    m_widgets[cond.conditionalName()]->setVisible(false);
                    m_labels[cond.conditionalName()]->setVisible(false);
                }
            }
            else{
                m_widgets[cond.conditionalName()]->setVisible(true);
                m_labels[cond.conditionalName()]->setVisible(true);
            }
        }
        else{
            m_widgets[cond.conditionalName()]->setVisible(false);
            m_labels[cond.conditionalName()]->setVisible(false);
        }
    }
}

blioParameters *blToolParameterSelectorWidget::getData(){

    blioParameters* params = new blioParameters;
    for (int i = 0; i < m_layout->count(); ++i) {
        QWidget *w = m_layout->itemAt(i)->widget();
        blToolInputWidget* wt = qobject_cast<blToolInputWidget*>(w);
        if(wt != NULL){
            //if (wt->isVisible()){
                params->add(wt->key(), wt->value());
            //}
            //qDebug() << "add parameter: key="<< wt->key() << ", value=" << wt->value();
        }
    }
    return params;
}

void blToolParameterSelectorWidget::initializeConditions(){

    //qDebug() << "widgets = " << m_widgets;

    for(int i = 0 ; i < m_parametersConditional.count() ; ++i){
        blToolParameterCondition cond = m_parametersConditional.at(i);
        //qDebug() << "cond at " << i << " = " << cond.conditionalName();
        // get condition widget
        if(m_widgets[cond.conditionName()]->value() == cond.conditionValue()){
            if (m_widgets[cond.conditionalName()]->isAdvanced()){
                if (m_advancedMode){
                    m_widgets[cond.conditionalName()]->setVisible(true);
                    m_labels[cond.conditionalName()]->setVisible(true);
                }
                else{
                    m_widgets[cond.conditionalName()]->setVisible(false);
                    m_labels[cond.conditionalName()]->setVisible(false);
                }
            }
            else{
                m_widgets[cond.conditionalName()]->setVisible(true);
                m_labels[cond.conditionalName()]->setVisible(true);
            }
        }
        else{
            m_widgets[cond.conditionalName()]->setVisible(false);
            m_labels[cond.conditionalName()]->setVisible(false);
        }
    }
}

void blToolParameterSelectorWidget::showHideConditional(QString conditionName, QString conditionValue){
    for(int i = 0 ; i < m_parametersConditional.count() ; ++i){
        blToolParameterCondition cond = m_parametersConditional.at(i);
        if (cond.conditionName() == conditionName){
            if (cond.conditionValue() == conditionValue){
                // show conditional
                if (m_widgets[cond.conditionalName()]->isAdvanced()){
                    if (m_advancedMode){
                        m_widgets[cond.conditionalName()]->setVisible(true);
                        m_labels[cond.conditionalName()]->setVisible(true);
                    }
                    else{
                        m_widgets[cond.conditionalName()]->setVisible(false);
                        m_labels[cond.conditionalName()]->setVisible(false);
                    }
                }
                else{
                    m_widgets[cond.conditionalName()]->setVisible(true);
                    m_labels[cond.conditionalName()]->setVisible(true);
                }
            }
            else{
                // hide conditional
                m_widgets[cond.conditionalName()]->setVisible(false);
                m_labels[cond.conditionalName()]->setVisible(false);
            }
        }
    }
}
