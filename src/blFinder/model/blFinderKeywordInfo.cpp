#include "blFinderKeywordInfo.h"

blFinderKeywordInfo::blFinderKeywordInfo(){
    m_id = 0;
    m_categoryID = 0;
}

void blFinderKeywordInfo::setID(int id){
    m_id = id;
}

void blFinderKeywordInfo::setName(QString name){
    m_name = name;
}

int blFinderKeywordInfo::id(){
    return m_id;
}

QString blFinderKeywordInfo::name(){
    return m_name;
}

void blFinderKeywordInfo::setCategoryID(int id){
    m_categoryID = id;
}

void blFinderKeywordInfo::setCategoryName(QString name){
    m_categoryName = name;
}

int blFinderKeywordInfo::categoryID(){
    return m_categoryID;
}

QString blFinderKeywordInfo::categoryName(){
    return m_categoryName;
}

