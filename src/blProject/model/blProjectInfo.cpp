/// \file blProjectInfo.cpp
/// \brief blProjectInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectInfo.h"

blProjectInfo::blProjectInfo(){
    m_id = 0;
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
