#include "blFinderOriginInfo.h"

blFinderOriginInfo::blFinderOriginInfo(){
    m_id = 0;
    m_name = "";
}

void blFinderOriginInfo::setID(int id){
    m_id = id;
}

void blFinderOriginInfo::setName(QString name){
    m_name = name;
}

int blFinderOriginInfo::id(){
    return m_id;
}

QString blFinderOriginInfo::name(){
    return m_name;
}
