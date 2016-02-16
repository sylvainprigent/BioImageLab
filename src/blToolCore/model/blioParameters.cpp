#include "blioParameters.h"
#include <iostream>
#include <QDataStream>

blioParameters::blioParameters()
{

}

void blioParameters::add(QString key, QString value){
    m_keys.append(key);
    m_values.append(value);
}

unsigned int blioParameters::count(){
    return m_keys.count();
}

QString blioParameters::valueAt(unsigned int index){
    return m_values.at(index);
}

QString blioParameters::valueAt(QString id){
    for(int i = 0 ; i < m_keys.count() ; ++i){
        if (m_keys[i] == id){
            return m_values[i];
        }
    }
    return "";
}

QString blioParameters::keyAt(unsigned int index){
    return m_keys.at(index);
}

void blioParameters::print(){

    for(int i = 0 ; i < m_keys.count() ; ++i){
        std::cout << m_keys[i].toStdString() << " = " << m_values[i].toStdString() << std::endl;
    }
}

QDataStream & operator <<(QDataStream &s, const blioParameters &c)
{
    s << c.m_keys;
    s << c.m_values;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blioParameters& c){

    stream>>c.m_keys;
    stream>>c.m_values;
    return stream;
}
