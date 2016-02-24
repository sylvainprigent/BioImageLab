#include "blSubColumnInfo.h"

blSubColumnInfo::blSubColumnInfo(){
    m_id = 0;
    m_id_main_col = 0;
}

blSubColumnInfo::blSubColumnInfo(int id, QString name, int id_main_col, QString datatype){
    m_id = id;
    m_name = name;
    m_id_main_col = id_main_col;
    m_datatype = datatype;
}

int blSubColumnInfo::id(){
    return m_id;
}

QString blSubColumnInfo::name(){
    return m_name;
}

int blSubColumnInfo::id_main_col(){
    return m_id_main_col;
}

QString blSubColumnInfo::datatype(){
    return m_datatype;
}

void blSubColumnInfo::setId(int id){
    m_id = id;
}

void blSubColumnInfo::setName(QString name){
    m_name = name;
}

void blSubColumnInfo::set_id_main_col(int id){
    m_id_main_col = id;
}

void blSubColumnInfo::setDatatype(QString datatype){
    m_datatype = datatype;
}
