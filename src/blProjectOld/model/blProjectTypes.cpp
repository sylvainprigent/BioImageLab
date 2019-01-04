#include "blProjectTypes.h"

// ////////////////////////////////////////////////// //
//              blProjectType
// ///////////////////////////////////////////////// //
blProjectType::blProjectType(){

}

blProjectType::blProjectType(int id, QString name){

    m_id = id;
    m_name = name;
}


int blProjectType::id(){
    return m_id;
}

QString blProjectType::name(){
    return m_name;
}

void blProjectType::setId(int id){
    m_id = id;
}

void blProjectType::setName(QString name){
    m_name = name;
}


// ////////////////////////////////////////////////// //
//              blProjectTypes
// ///////////////////////////////////////////////// //
blProjectTypes::blProjectTypes(){

}

int blProjectTypes::count(){
    return m_projectsTypes.count();
}

blProjectType blProjectTypes::at(int i){
    return m_projectsTypes.at(i);
}

void blProjectTypes::add(blProjectType projectType){
    m_projectsTypes.append(projectType);
}

