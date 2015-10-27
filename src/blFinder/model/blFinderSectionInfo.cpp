#include "blFinderSectionInfo.h"

blFinderSectionInfo::blFinderSectionInfo(){
    m_id = 0;
    m_displayOrder = 0;
}

// setters
void blFinderSectionInfo::setID(int id){
    m_id = id;
}

void blFinderSectionInfo::setName(QString name){
    m_name = name;
}

void blFinderSectionInfo::setDescription(QString desc){
    m_description = desc;
}

void blFinderSectionInfo::setImageUrl(QString url){
    m_imageUrl = url;
}

void blFinderSectionInfo::setChildrenTitle(QString title){
    m_childrenTitle = title;
}

void blFinderSectionInfo::setDisplayOrder(int order){
    m_displayOrder = order;
}

// getters
int blFinderSectionInfo::id(){
    return m_id;
}

QString blFinderSectionInfo::name(){
    return m_name;
}

QString blFinderSectionInfo::description(){
    return m_description;
}

QString blFinderSectionInfo::imageUrl(){
    return m_imageUrl;
}

QString blFinderSectionInfo::childrenTitle(){
    return m_childrenTitle;
}

int blFinderSectionInfo::displayOrder(){
    return m_displayOrder;
}
