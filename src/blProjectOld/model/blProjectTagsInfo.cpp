/// \file blProjectTagsInfo.cpp
/// \brief blProjectTagsInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectTagsInfo.h"
#include <QDebug>

blProjectTagsInfo::blProjectTagsInfo(){
    m_id = 0;
    m_typeId = 1;
}

blProjectTagsInfo::~blProjectTagsInfo(){

}


// setters
void blProjectTagsInfo::setId(unsigned int id){
    m_id = id;
}

void blProjectTagsInfo::setName(QString name){
    m_name = name;
}

void blProjectTagsInfo::setUrl(QString url){
    m_url = url;
}

void blProjectTagsInfo::setCreatedDate(QString createdDate){
    m_createdDate = createdDate;
}

void blProjectTagsInfo::setLastModifiedDate(QString lastModifiedDate){
    m_lastModifiedDate = lastModifiedDate;
}

void blProjectTagsInfo::setDescription(QString description){
    m_description = description;
}

void blProjectTagsInfo::setTypeId(int typeId){
    m_typeId = typeId;
}

// getters
unsigned int blProjectTagsInfo::id(){
    return m_id;
}

QString blProjectTagsInfo::name(){
    return m_name;
}

QString blProjectTagsInfo::url(){
    return m_url;
}

QString blProjectTagsInfo::createdDate(){
    return m_createdDate;
}

QString blProjectTagsInfo::lastModifiedDate(){
    return m_lastModifiedDate;
}

QString blProjectTagsInfo::description(){
    return m_description;
}

int blProjectTagsInfo::typeId(){
    return m_typeId;
}

void blProjectTagsInfo::print(){

    qDebug() << "project info:";
    qDebug() << "id = " << m_id;
    qDebug() << "name = " << m_name;
    qDebug() << "description = " << m_description;
    qDebug() << "typeId = " << m_typeId;
    qDebug() << "url = " << m_url;
    qDebug() << "createdDate = " << m_createdDate;
    qDebug() << "lastModifiedDate = " << m_lastModifiedDate;

}
