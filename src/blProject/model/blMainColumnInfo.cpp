#include "blMainColumnInfo.h"

blMainColumnInfo::blMainColumnInfo(){
    m_id = 0;
}

blMainColumnInfo::blMainColumnInfo(int id, QString name, QString origin_url){
    m_id = id;
    m_name = name;
    m_origin_url = origin_url;
}

int blMainColumnInfo::id(){
    return m_id;
}

QString blMainColumnInfo::name(){
    return m_name;
}

QString blMainColumnInfo::origin_url(){
    return m_origin_url;
}

void blMainColumnInfo::setId(int id){
    m_id = id;
}

void blMainColumnInfo::setName(QString name){
    m_name = name;
}

void blMainColumnInfo::setOriginUrl(QString url){
    m_origin_url = url;
}
