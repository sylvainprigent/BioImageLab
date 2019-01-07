/// \file blProjectData.cpp
/// \brief blProjectData
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectData.h"
#include <QDebug>

blProjectData::blProjectData(){
    m_id = 0;
    m_url = "";
}

blProjectData::~blProjectData(){

}

void blProjectData::setId(unsigned int id){
    m_id = id;
}

void blProjectData::setUrl(QString url){
    m_url = url;
}

unsigned int blProjectData::id(){
    return m_id;
}

QString blProjectData::url(){
    return m_url;
}

void blProjectData::print(){
    qDebug() << "data info:";
    qDebug() << "id = " << m_id;
    qDebug() << "url = " << m_url;
}
