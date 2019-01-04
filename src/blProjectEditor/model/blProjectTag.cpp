/// \file blProjectTag.cpp
/// \brief blProjectTag
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectTag.h"
#include <QDebug>

blProjectTag::blProjectTag(){
    m_id = 0;
    m_name = "";
}

blProjectTag::~blProjectTag(){

}

void blProjectTag::setId(unsigned int id){
    m_id = id;
}

void blProjectTag::setName(QString name){
    m_name = name;
}

void blProjectTag::print(){
    qDebug() << "tag info:";
    qDebug() << "id = " << m_id;
    qDebug() << "name = " << m_name;
}
