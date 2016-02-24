/// \file blTagsInfo.cpp
/// \brief blTagsInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) blimbio 2014

#include "blTagsInfo.h"

// //////////////////////////////////////// //
//              blTaginfo
// //////////////////////////////////////// //
blTagInfo::blTagInfo(){

}

void blTagInfo::setId(int id){
    m_id = id;
}

void blTagInfo::setName(QString name){
    m_name = name;
}

void blTagInfo::setSubColId(int subColId){
    m_subColId = subColId;
}

void blTagInfo::setSubColName(QString subColName){
    m_subColName = subColName;
}


int blTagInfo::id(){
    return m_id;
}

QString blTagInfo::name(){
    return m_name;
}

int blTagInfo::subColId(){
    return m_subColId;
}

QString blTagInfo::subColName(){
    return m_subColName;
}




// //////////////////////////////////////// //
//              blTagsInfo
// //////////////////////////////////////// //
blTagsInfo::blTagsInfo(){

}
void blTagsInfo::set(int id, blTagInfo tagInfo){
    bool found = false;
    for(int i = 0 ; i < m_tagsInfo.count() ; i++){
        if (m_tagsInfo[i].id() == id){
            m_tagsInfo[i] = tagInfo;
            found = true;
        }
    }

    if (!found){
        m_tagsInfo.append(tagInfo);
    }

}

void blTagsInfo::add(blTagInfo tagInfo){
    m_tagsInfo.append(tagInfo);
}

blTagInfo blTagsInfo::get(int id){
    for(int i = 0 ; i < m_tagsInfo.count() ; i++){
        if (m_tagsInfo[i].id() == id){
            return m_tagsInfo[i];

        }
    }
}

QList<blTagInfo> blTagsInfo::all(){
    return m_tagsInfo;
}
