#ifndef BLTOOLPARAMETERS_H
#define BLTOOLPARAMETERS_H

#include <QString>
#include <QList>

#include "blToolExport.h"

class blToolParameter;
class blToolParameterCondition;

///
/// \brief The blToolParameters class
///
class BLTOOL_EXPORT blToolParameters
{
public:
    blToolParameters();

public:
    // parameters
    unsigned int count();
    blToolParameter at(int index);
    void add(blToolParameter parameter);

    // conditions
    void addCondition(blToolParameterCondition condition);
    QList<blToolParameterCondition> conditions();

    // print
    void print();

private:
    QList<blToolParameter> m_parameters;
    QList<blToolParameterCondition> m_conditions;
};

///
/// \brief The blToolParameter class
///
class blToolParameter{

public:
    blToolParameter();

public:
    // setters
    void setName(QString name);
    void setType(QString type);
    void setLabel(QString label);
    void setValue(QString value);
    void setHelp(QString help);
    void setAdvanced(bool adv);

public:
    // getters
    QString name();
    QString type();
    QString label();
    QString value();
    QString help();
    bool advanced();

private:
    QString m_name;
    QString m_type;
    QString m_label;
    QString m_value;
    QString m_help;
    bool m_advanced;

};

///
/// \brief The blToolParameter class
///
class blToolParameterCondition{

public:
    blToolParameterCondition();

public:
    // setters
    void setConditionName(QString name);
    void setConditionValue(QString value);
    void setConditionalName(QString name);

public:
    // getters
    QString conditionName();
    QString conditionValue();
    QString conditionalName();

private:
    QString m_conditionName;
    QString m_conditionValue;
    QString m_conditionalName;

};

#endif // BLTOOLPARAMETERS_H
