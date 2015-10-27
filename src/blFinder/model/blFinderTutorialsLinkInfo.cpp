#include "blFinderTutorialsLinkInfo.h"

blFinderTutorialsLinkInfo::blFinderTutorialsLinkInfo(){
    m_categoryID = 0;
    m_tutorialID = 0;
}

// setters
void blFinderTutorialsLinkInfo::setCategoryID(int id){
    m_categoryID = id;
}

void blFinderTutorialsLinkInfo::setCategoryName(QString name){
    m_categoryName = name;
}

void blFinderTutorialsLinkInfo::setTutorialID(int id){
    m_tutorialID = id;
}

void blFinderTutorialsLinkInfo::setTutorialName(QString name){
    m_tutorialName = name;
}

// getters
int blFinderTutorialsLinkInfo::categoryID(){
    return m_categoryID;
}

QString blFinderTutorialsLinkInfo::categoryName(){
    return m_categoryName;
}

int blFinderTutorialsLinkInfo::tutorialID(){
    return m_tutorialID;
}

QString blFinderTutorialsLinkInfo::tutorialName(){
    return m_tutorialName;
}
