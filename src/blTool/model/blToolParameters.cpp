#include "blToolParameters.h"
#include <iostream>

// //////////////////////////////////// //
//         blToolParameters             //
// //////////////////////////////////// //
blToolParameters::blToolParameters()
{

}

unsigned int blToolParameters::count(){
    return m_parameters.count();
}

blToolParameter blToolParameters::at(int index){
    return m_parameters.at(index);
}

void blToolParameters::add(blToolParameter parameter){
    m_parameters.append(parameter);
}

void blToolParameters::addCondition(blToolParameterCondition condition){
    m_conditions.append(condition);
}

QList<blToolParameterCondition> blToolParameters::conditions(){
    return m_conditions;
}

void blToolParameters::print(){

    std::cout << "Parameters : " << std::endl;
    for(int i = 0 ; i < m_parameters.count() ; ++i){
        blToolParameter param = m_parameters.at(i);
        std::cout << "\t -label:" << QString(param.label()).toStdString() << " name: "
                  << param.name().toStdString() << " type: "
                  << param.type().toStdString() << " value: "
                  << param.value().toStdString() << std::endl ;
    }
    std::cout << "Parameters conditional : " << std::endl;
    for(int i = 0 ; i < m_conditions.count() ; ++i){
        blToolParameterCondition cond = m_conditions.at(i);
        std::cout << "\t -condition: " << cond.conditionName().toStdString() << " condition value: "
                  << cond.conditionValue().toStdString() << " conditional: "
                  << cond.conditionalName().toStdString() << std::endl ;
    }
}

// ////////////////////////////////////////// //
//           blToolParameter                  //
// ////////////////////////////////////////// //
blToolParameter::blToolParameter(){

}

// setters
void blToolParameter::setName(QString name){
    m_name = name;
}

void blToolParameter::setType(QString type){
    m_type = type;
}

void blToolParameter::setLabel(QString label){
    m_label = label;
}

void blToolParameter::setValue(QString value){
    m_value = value;
}

void blToolParameter::setHelp(QString help){
    m_help = help;
}

void blToolParameter::setAdvanced(bool adv){
    m_advanced = adv;
}

// getters
QString blToolParameter::name(){
    return m_name;
}

QString blToolParameter::type(){
    return m_type;
}

QString blToolParameter::label(){
    return m_label;
}

QString blToolParameter::value(){
    return m_value;
}

QString blToolParameter::help(){
    return m_help;
}

bool blToolParameter::advanced(){
    return m_advanced;
}

// ////////////////////////////////////////// //
//        blToolParameterCondition            //
// ////////////////////////////////////////// //
blToolParameterCondition::blToolParameterCondition(){

}

// setters
void blToolParameterCondition::setConditionName(QString name){
    m_conditionName = name;
}

void blToolParameterCondition::setConditionValue(QString value){
    m_conditionValue = value;
}

void blToolParameterCondition::setConditionalName(QString name){
    m_conditionalName = name;
}

// getters
QString blToolParameterCondition::conditionName(){
    return m_conditionName;
}

QString blToolParameterCondition::conditionValue(){
    return m_conditionValue;
}

QString blToolParameterCondition::conditionalName(){
    return m_conditionalName;
}
