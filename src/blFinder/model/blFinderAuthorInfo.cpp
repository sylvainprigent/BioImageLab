#include "blFinderAuthorInfo.h"

blFinderAuthorInfo::blFinderAuthorInfo(){
    m_id = 0;
    m_name = "";
    m_firstname = "";
}

void blFinderAuthorInfo::setID(int id){
    m_id = id;
}

void blFinderAuthorInfo::setName(QString name){
    m_name = name;
}

void blFinderAuthorInfo::setFirstname(QString firstname){
    m_firstname = firstname;
}


int blFinderAuthorInfo::id(){
    return m_id;
}

QString blFinderAuthorInfo::name(){
    return m_name;
}

QString blFinderAuthorInfo::firstname(){
    return m_firstname;
}

