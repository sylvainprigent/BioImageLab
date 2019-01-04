/// \file blDataInfo.cpp
/// \brief blDataInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) blimbio 2014

#include "blDataInfo.h"

blDataInfo::blDataInfo(){

}


void blDataInfo::setid(int value){
    m_id = value;
}

void blDataInfo::setline_id(int value){
    m_line_id = value;
}

void blDataInfo::seturl(QString value){
    m_url = value;
}

void blDataInfo::setthumbnail(QString value){
    m_thumbnail = value;
}

void blDataInfo::setid_main_col(int value){
    m_id_main_col = value;
}

void blDataInfo::setid_sub_column(int value){
    m_id_sub_column = value;
}

void blDataInfo::setmain_col_name(QString value){
    m_main_col_name = value;
}

void blDataInfo::setid_sub_column_name(QString value){
    m_id_sub_column_name = value;
}


int blDataInfo::id(){
    return m_id;
}

int blDataInfo::line_id(){
    return m_line_id;
}

QString blDataInfo::url(){
    return m_url;
}

QString blDataInfo::thumbnail(){
    return m_thumbnail;
}

int blDataInfo::id_main_col(){
    return m_id_main_col;
}

int blDataInfo::id_sub_column(){
    return m_id_sub_column;
}

QString blDataInfo::main_col_name(){
    return m_main_col_name;
}

QString blDataInfo::id_sub_column_name(){
    return m_id_sub_column_name;
}
