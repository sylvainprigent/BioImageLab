#include "blFinderCategoryInfo.h"

blFinderCategoryInfo::blFinderCategoryInfo(){
    m_id = 0;
    m_name = "";
}

void blFinderCategoryInfo::setID(int id){
    m_id = id;
}

void blFinderCategoryInfo::setName(QString name){
    m_name = name;
}

int blFinderCategoryInfo::id(){
    return m_id;
}

QString blFinderCategoryInfo::name(){
    return m_name;
}
