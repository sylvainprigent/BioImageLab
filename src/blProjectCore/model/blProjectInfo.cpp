/// \file blProjectInfo.cpp
/// \brief blProjectInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectInfo.h"
#include <QDebug>

blProjectInfo::blProjectInfo(){
    m_id = 0;
    m_typeId = 1;
}

blProjectInfo::~blProjectInfo(){

}


// setters
void blProjectInfo::setId(unsigned int id){
    m_id = id;
}

void blProjectInfo::setName(QString name){
    m_name = name;
}

void blProjectInfo::setUrl(QString url){
    m_url = url;
}

void blProjectInfo::setCreatedDate(QString createdDate){
    m_createdDate = createdDate;
}

void blProjectInfo::setLastModifiedDate(QString lastModifiedDate){
    m_lastModifiedDate = lastModifiedDate;
}

void blProjectInfo::setDescription(QString description){
    m_description = description;
}

void blProjectInfo::setTypeId(int typeId){
    m_typeId = typeId;
}

// getters
unsigned int blProjectInfo::id(){
    return m_id;
}

QString blProjectInfo::name(){
    return m_name;
}

QString blProjectInfo::url(){
    return m_url;
}

QString blProjectInfo::createdDate(){
    return m_createdDate;
}

QString blProjectInfo::lastModifiedDate(){
    return m_lastModifiedDate;
}

QString blProjectInfo::description(){
    return m_description;
}

int blProjectInfo::typeId(){
    return m_typeId;
}

void blProjectInfo::print(){

    qDebug() << "project info:";
    qDebug() << "id = " << m_id;
    qDebug() << "name = " << m_name;
    qDebug() << "description = " << m_description;
    qDebug() << "typeId = " << m_typeId;
    qDebug() << "url = " << m_url;
    qDebug() << "createdDate = " << m_createdDate;
    qDebug() << "lastModifiedDate = " << m_lastModifiedDate;

}
