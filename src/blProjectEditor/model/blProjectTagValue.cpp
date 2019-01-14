/// \file blProjectTagValue.cpp
/// \brief blProjectTagValue
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectTagValue.h"
#include <QDebug>

blProjectTagValue::blProjectTagValue(){
    m_id = 0;
    m_idTag = 0;
    m_idData = 0;
    m_value = "";
}

blProjectTagValue::~blProjectTagValue(){

}

void blProjectTagValue::setId(unsigned int id){
    m_id = id;
}

void blProjectTagValue::setIdTag(unsigned int id){
    m_idTag = id;
}

void blProjectTagValue::setIdData(unsigned int id){
    m_idData = id;
}

void blProjectTagValue::setValue(QString value){
    m_value = value;
}

unsigned int blProjectTagValue::getId(){
    return m_id;
}

unsigned int blProjectTagValue::getIdTag(){
    return m_idTag;
}

unsigned int blProjectTagValue::getIdData(){
    return m_idData;
}

QString blProjectTagValue::getValue(){
    return m_value;
}

void blProjectTagValue::print(){
    qDebug() << "tag value:";
    qDebug() << "id = " << m_id;
    qDebug() << "id tag = " << m_idTag;
    qDebug() << "id data = " << m_idData;
    qDebug() << "value = " << m_value;
}
