#include "blFinderSectionsLinkInfo.h"

blFinderSectionsLinkInfo::blFinderSectionsLinkInfo(){
    m_parentID = 0;
    m_childID = 0;
}

// setters
void blFinderSectionsLinkInfo::setParentID(int id){
    m_parentID = id;
}

void blFinderSectionsLinkInfo::setParentName(QString name){
    m_parentName = name;
}

void blFinderSectionsLinkInfo::setChildID(int id){
    m_childID = id;
}

void blFinderSectionsLinkInfo::setChildName(QString name){
    m_childName = name;
}

// getters
int blFinderSectionsLinkInfo::parentID(){
    return m_parentID;
}

QString blFinderSectionsLinkInfo::parentName(){
    return m_parentName;
}

int blFinderSectionsLinkInfo::childID(){
    return m_childID;
}

QString blFinderSectionsLinkInfo::childName(){
    return m_childName;
}
