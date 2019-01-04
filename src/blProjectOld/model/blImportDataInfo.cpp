/// \file blImportDataInfo.cpp
/// \brief blImportDataInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2016

#include "blImportDataInfo.h"
#include <QDebug>

blImportDataInfo::blImportDataInfo(){

}

blImportDataInfo::~blImportDataInfo(){

}

void blImportDataInfo::setTags(blTagsInfo tags){
    m_tags = tags;
}

void blImportDataInfo::setData(QList<blDataInfo> data){
    m_data = data;
}

void blImportDataInfo::setMainColumnInfo(blMainColumnInfo mainColumnInfo){
    m_mainColumnInfo = mainColumnInfo;
}

void blImportDataInfo::setSubColumnsInfos(QList<blSubColumnInfo> subColumnsInfos){
    m_subColumnsInfos = subColumnsInfos;
}


blTagsInfo blImportDataInfo::tags(){
    return m_tags;
}

QList<blDataInfo> blImportDataInfo::data(){
    return m_data;
}

blMainColumnInfo blImportDataInfo::mainColumnInfo(){
    return m_mainColumnInfo;
}

QList<blSubColumnInfo> blImportDataInfo::subColumnsInfos(){
    return m_subColumnsInfos;
}
